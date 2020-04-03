#include "VideoFrameObserver.h"
#include "Agora.h"

#include "AgoraBlueprintable.h"

#include <memory>
#include <algorithm>
#include <utility>

namespace agora
{
namespace blueprints
{
VideoFrameObserver::VideoFrameObserver( UAgora* agora )
   : m_agora( agora )
{
}

TArray<int64> VideoFrameObserver::getUsersIds()
{
   const std::lock_guard<std::mutex> lock( remoteFrameMutex );
   TArray<int64> iDs;
   std::for_each( remoteUsersFrames.begin(), remoteUsersFrames.end(),
                  [&iDs]( const auto& param )
   {
      iDs.Add( param.first );
   } );
   return iDs;
}

void VideoFrameObserver::removeUserFrameBuffer( int64 userId )
{
   const std::lock_guard<std::mutex> lock( remoteFrameMutex );
   remoteUsersFrames.erase( userId );
}

void VideoFrameObserver::clearFrameBuffers()
{
   const std::lock_guard<std::mutex> lock( remoteFrameMutex );
   remoteUsersFrames.clear();
}

bool VideoFrameObserver::onCaptureVideoFrame( VideoFrame& videoFrame )
{
   const std::lock_guard<std::mutex> lock( localFrameMutex );

   if( !localFrame.texture ||
       localFrame.texture->GetSizeX() != videoFrame.width ||
       localFrame.texture->GetSizeY() != videoFrame.height )
   {
      localFrame.region.reset( new FUpdateTextureRegion2D( 0, 0, 0, 0, videoFrame.width, videoFrame.height ) );
      localFrame.texture = UTexture2D::CreateTransient( videoFrame.width, videoFrame.height, PF_R8G8B8A8 );
      localFrame.texture->UpdateResource();
   }

   localFrame.texture->UpdateTextureRegions( 0, 1, localFrame.region.get(), videoFrame.yStride, ( uint32 ) argbPixSize, static_cast< uint8_t* >( videoFrame.yBuffer ) );

   localFrame.fresh = true;

   return true;
}

bool VideoFrameObserver::onRenderVideoFrame( unsigned int userId, VideoFrame& videoFrame )
{
   const std::lock_guard<std::mutex> lock( remoteFrameMutex );

   if( !remoteUsersFrames[userId].texture ||
       remoteUsersFrames[userId].texture->GetSizeX() != videoFrame.width ||
       remoteUsersFrames[userId].texture->GetSizeY() != videoFrame.height )
   {
      remoteUsersFrames[userId].region.reset( new FUpdateTextureRegion2D( 0, 0, 0, 0, videoFrame.width, videoFrame.height ) );
      remoteUsersFrames[userId].texture = UTexture2D::CreateTransient( videoFrame.width, videoFrame.height, PF_R8G8B8A8 );
      remoteUsersFrames[userId].texture->UpdateResource();
   }
   
   remoteUsersFrames[userId].texture->UpdateTextureRegions( 0, 1, remoteUsersFrames[userId].region.get(), videoFrame.yStride, ( uint32 ) argbPixSize, static_cast<uint8_t*>( videoFrame.yBuffer ) );
   remoteUsersFrames[userId].fresh = true;
   return true;
}

void VideoFrameObserver::OnTick( float DeltaTime )
{
   localFrameMutex.lock();

   if( localFrame.fresh )
   {
      if( m_agora )
         m_agora->OnLocalFrameReceivedDelegate.Broadcast( localFrame.texture );
      localFrame.fresh = false;
   }

   localFrameMutex.unlock();

   remoteFrameMutex.lock();
   std::for_each( remoteUsersFrames.begin(), remoteUsersFrames.end(),
                  [this]( auto& frame )
   {
      if( frame.second.fresh )
      {
         if( m_agora )
            m_agora->OnRemoteFrameReceivedDelegate.Broadcast( frame.first, frame.second.texture );
         frame.second.fresh = false;
      }
   } );
   remoteFrameMutex.unlock();
}
}
}