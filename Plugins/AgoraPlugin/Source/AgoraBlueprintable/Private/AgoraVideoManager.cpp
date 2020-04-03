// Copyright (c) 2019 Agora.io. All rights reserved.


#include "AgoraVideoManager.h"
#include "AgoraBlueprintable.h"
#include "Agora.h"

namespace agora
{
namespace blueprints
{
TUniquePtr<AgoraVideoManager> AgoraVideoManager::Create( UIAgora* agora )
{
   if( !agora )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraVideoManager::Create - UIAgora is nullptr" ) );
      return nullptr;
   }

   if( !agora->rtcEngine )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraVideoManager::Create - rtcEngine is nullptr" ) );
      return nullptr;
   }

   agora->EnableVideo();

   TUniquePtr<AgoraVideoManager> manager = MakeUnique<AgoraVideoManager>();

   manager->m_videoDeviceManager.queryInterface( agora->rtcEngine.Get()->m_rtcEngine, agora::AGORA_IID_VIDEO_DEVICE_MANAGER );
   if( !manager->m_videoDeviceManager )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraVideoManager::Create - failed to get video device manager" ) );
      return nullptr;
   }

   manager->m_recordingDevices = manager->m_videoDeviceManager->enumerateVideoDevices();
   if( !manager->m_recordingDevices )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraVideoManager::Create - failed to get recodring devices" ) );
   }

   return manager;
}

TArray<FMediaDevice> AgoraVideoManager::getRecordingDevices()
{
   TArray<FMediaDevice> Devices;
   if( !m_recordingDevices )
      return Devices;

   FMediaDevice Device;

   int NumDevices = m_recordingDevices->getCount();

   for( int Index = 0; Index < NumDevices; ++Index )
   {
      Device.Index = Index;
      int nRet = getRecordingDevice( Index, Device.DeviceName, Device.DeviceID );

      if( nRet < 0 )
         continue;

      Devices.Add( Device );
   }

   return Devices;
}

int AgoraVideoManager::getRecordingDevice( int Index, FString & DeviceName, FString & DeviceID )
{
   if( !m_recordingDevices )
      return -1;

   char Name[agora::rtc::MAX_DEVICE_ID_LENGTH];
   char Id[agora::rtc::MAX_DEVICE_ID_LENGTH];
   int nRet = m_recordingDevices->getDevice( Index, Name, Id );

   DeviceName = FString( ANSI_TO_TCHAR( Name ) );
   DeviceID = FString( ANSI_TO_TCHAR( Id ) );

   return nRet;
}

int AgoraVideoManager::setCurrentRecordingDevice( const FString& DeviceID )
{
   if( !m_videoDeviceManager )
      return -1;

   return m_videoDeviceManager->setDevice( TCHAR_TO_ANSI( *DeviceID ) );
}

int AgoraVideoManager::getCurrentRecordingDevice( int& Index, FString& DeviceName, FString& DeviceID )
{
   if( !m_recordingDevices || !m_videoDeviceManager )
      return -1;

   char cDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH];
   int ret = m_videoDeviceManager->getDevice( cDeviceId );

   if( ret < 0 )
      return -1;

   int NumDevices = m_recordingDevices->getCount();
   FString deviceName, deviceID;

   for( int i = 0; i < NumDevices; ++i )
   {
      getRecordingDevice( i, deviceName, deviceID );

      if( deviceID.Equals( FString( ANSI_TO_TCHAR( cDeviceId ) ) ) )
      {
         Index = i;
         DeviceName = deviceName;
         DeviceID = deviceID;
         return 0;
      }
   }
   return -1;
}

int AgoraVideoManager::getRecordingDeviceCount()
{
   if( !m_recordingDevices )
      return -1;

   return m_recordingDevices->getCount();
}

int AgoraVideoManager::enumerateRecordingDevices()
{
   if( !m_videoDeviceManager )
      return -1;
   if( m_recordingDevices )
      m_recordingDevices->release();

   m_recordingDevices = m_videoDeviceManager->enumerateVideoDevices();
   if( !m_recordingDevices )
      return -1;
   return 0;
}

AgoraVideoManager::~AgoraVideoManager()
{
   if( m_recordingDevices )
      m_recordingDevices->release();
   m_recordingDevices = nullptr;
   /*if( m_videoDeviceManager )
      m_videoDeviceManager->release();
   m_videoDeviceManager.reset( nullptr );*/
}
}
}