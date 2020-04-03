#pragma once

#include <map>
#include <mutex>

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/IAgoraMediaEngine.h>
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"

class UAgora;

namespace agora
{
namespace blueprints
{
/** Video Frame Observer Interface. 

Inherit this class if you want custom \ref VideoFrameObserver implementation
*/
class AGORABLUEPRINTABLE_API IVideoFrameObserver : public agora::media::IVideoFrameObserver
{
public:
   virtual ~IVideoFrameObserver() = default;

   /** This function is called in \ref UIAgora::Tick.
   
   Agora callbacks must be synchronized with Unreal Engine thread.
   
   Use this function to synchronize agora callbacks and UE main thread.
   @param DeltaTime The amount of time between frames (seconds).
   */
   virtual void OnTick( float DeltaTime ) = 0;
};

/** Video Frame Observer.
Handles video frames received from Agora.
*/
class AGORABLUEPRINTABLE_API VideoFrameObserver : public IVideoFrameObserver
{
public:
   VideoFrameObserver( UAgora* agora );
   ~VideoFrameObserver() = default;
   /**
   Captures local video frames and stores them into \ref localFrame variable.
   */
   virtual bool onCaptureVideoFrame( VideoFrame& videoFrame ) override;
   /**
   Captures remote video frames from different users and stores them into \ref remoteUsersFrames variable.
   */
   virtual bool onRenderVideoFrame( unsigned int userId, VideoFrame& videoFrame ) override;

   virtual VIDEO_FRAME_TYPE getVideoFormatPreference() override { return FRAME_TYPE_RGBA; }

   /**
   If Agora received new frames callbacks \ref UAgora::OnLocalFrameReceivedDelegate
   "OnLocalFrameReceived" and \ref UAgora::OnRemoteFrameReceivedDelegate "OnRemoteFrameReceived" will be called here.
   */
   virtual void OnTick( float DeltaTime ) override;

   /**
   @return Array of all user's ids in current channel.
   */
   TArray<int64> getUsersIds();

   /**
   Removes frame from \ref remoteUsersFrames.

   This funcion is called when remote user leaves channel.
   @param userId User Id
   */
   void removeUserFrameBuffer( int64 userId );
   
   /** 
   Removes all frames from \ref remoteUsersFrames.

   This function is called when local user leaves channedl.
   */
   void clearFrameBuffers();

private:
   /** Auxiliary structure. */
   struct Frame
   {
      /** Frame texture. */
      UTexture2D* texture = nullptr;

      /** Frame region. Used to update frame texture. */
      std::unique_ptr<FUpdateTextureRegion2D> region = nullptr;

      /** Indicates if this frame was updated by Agora. */
      bool fresh = false;
   };

   UAgora* m_agora = nullptr;

   /** Remote frames received from Agora. */
   std::map<int64, Frame> remoteUsersFrames;

   /** Local camera frame received from Agora. */
   Frame localFrame;

   /** Synchronizing mutex*/
   std::mutex remoteFrameMutex;

   /** Synchronizing mutex*/
   std::mutex localFrameMutex;

   /** ARGB pixel size. */
   const int argbPixSize = 4;

};
}
}