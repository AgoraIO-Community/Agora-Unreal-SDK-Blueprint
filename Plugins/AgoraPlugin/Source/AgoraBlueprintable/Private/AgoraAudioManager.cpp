// Copyright (c) 2019 Agora.io. All rights reserved.


#include "AgoraAudioManager.h"
#include "Agora.h"
#include "AgoraRtcEngine.h"
#include "AgoraBlueprintable.h"

namespace agora
{
namespace blueprints
{
TUniquePtr<AgoraAudioManager> AgoraAudioManager::Create( UIAgora* agora )
{
   if( !agora )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraAudioManager::Create - UIAgora is nullptr" ) );
      return nullptr;
   }

   if( !agora->rtcEngine )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraAudioManager::Create - rtcEngine is nullptr" ) );
      return nullptr;
   }

   agora->EnableAudio();

   TUniquePtr<AgoraAudioManager> manager = MakeUnique<AgoraAudioManager>();
   
   manager->m_audioDeviceManager.queryInterface( agora->rtcEngine.Get()->m_rtcEngine, agora::AGORA_IID_AUDIO_DEVICE_MANAGER );
   if( !manager->m_audioDeviceManager )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraAudioManager::Create - failed to get audio device manager" ) );
      return nullptr;
   }

   manager->m_playbackDevices = manager->m_audioDeviceManager->enumeratePlaybackDevices();
   if( !manager->m_playbackDevices )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraAudioManager::Create - failed to get playback devices" ) );
   }

   manager->m_recordingDevices = manager->m_audioDeviceManager->enumerateRecordingDevices();
   if( !manager->m_recordingDevices )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "AgoraAudioManager::Create - failed to get recodring devices" ) );
   }
   return manager;
}

TArray<FMediaDevice> AgoraAudioManager::getDevices( agora::rtc::IAudioDeviceCollection* devices )
{
   TArray<FMediaDevice> Devices;
   if( !devices )
      return Devices;

   FMediaDevice Device;

   int NumDevices = devices->getCount();

   for( int Index = 0; Index < NumDevices; ++Index )
   {
      Device.Index = Index;
      int nRet = getDevice( devices, Device );
      if( nRet != 0 )
         continue;

      Devices.Add( Device );
   }

   return Devices;
}

TArray<FMediaDevice> AgoraAudioManager::getRecordingDevices()
{
   return getDevices( m_recordingDevices );
}

TArray<FMediaDevice> AgoraAudioManager::getPlaybackDevices()
{
   return getDevices( m_playbackDevices );
}

int AgoraAudioManager::getDevice( agora::rtc::IAudioDeviceCollection* devices, FMediaDevice& device )
{
   if( !devices )
      return -1;

   char Name[agora::rtc::MAX_DEVICE_ID_LENGTH];
   char Id[agora::rtc::MAX_DEVICE_ID_LENGTH];
   int nRet = devices->getDevice( device.Index, Name, Id );

   device.DeviceName = FString( ANSI_TO_TCHAR( Name ) );
   device.DeviceID = FString( ANSI_TO_TCHAR( Id ) );

   return nRet;
}

int AgoraAudioManager::setCurrentRecordingDevice( const FString& DeviceID )
{
   if( !m_recordingDevices )
      return -1;

   return m_audioDeviceManager->setRecordingDevice( TCHAR_TO_ANSI( *DeviceID ) );
}

int AgoraAudioManager::setCurrentPlaybackDevice( const FString & DeviceID )
{
   if( !m_playbackDevices )
      return -1;
   return m_audioDeviceManager->setPlaybackDevice( TCHAR_TO_ANSI( *DeviceID ) );
}

int AgoraAudioManager::getCurrentRecordingDevice( int& Index, FString& DeviceName, FString& DeviceID )
{
   if( !m_recordingDevices || !m_audioDeviceManager )
      return -1;

   char cDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH];
   int ret = m_audioDeviceManager->getRecordingDevice( cDeviceId );

   if( ret < 0 )
      return -1;

   int NumDevices = m_recordingDevices->getCount();

   FMediaDevice device;

   for( int i = 0; i < NumDevices; ++i )
   {
      device.Index = i;

      getDevice( m_recordingDevices, device );

      if( device.DeviceID.Equals( FString( ANSI_TO_TCHAR( cDeviceId ) ) ) )
      {
         Index = i;
         DeviceName = device.DeviceName;
         DeviceID = device.DeviceID;
         return 0;
      }
   }
   return -1;
}

int AgoraAudioManager::getCurrentPlaybackDevice( int& Index, FString& DeviceName, FString& DeviceID )
{
   if( !m_playbackDevices || !m_audioDeviceManager )
      return -1;

   char cDeviceId[agora::rtc::MAX_DEVICE_ID_LENGTH];
   int ret = m_audioDeviceManager->getPlaybackDevice( cDeviceId );

   if( ret < 0 )
      return -1;

   int NumDevices = m_playbackDevices->getCount();

   FMediaDevice device;

   for( int i = 0; i < NumDevices; ++i )
   {
      device.Index = i;

      getDevice( m_playbackDevices, device );

      if( device.DeviceID.Equals( FString( ANSI_TO_TCHAR( cDeviceId ) ) ) )
      {
         Index = i;
         DeviceName = device.DeviceName;
         DeviceID = device.DeviceID;
         return 0;
      }
   }
   return -1;
}

int AgoraAudioManager::getRecordingDeviceCount()
{
   if( !m_recordingDevices )
      return -1;
   return m_recordingDevices->getCount();
}

int AgoraAudioManager::getPlaybackDeviceCount()
{
   if( !m_playbackDevices )
      return -1;
   return m_playbackDevices->getCount();
}

int AgoraAudioManager::enumerateRecordingDevices()
{
   if( !m_audioDeviceManager )
      return -1;
   if( m_recordingDevices )
      m_recordingDevices->release();

   m_recordingDevices = m_audioDeviceManager->enumerateRecordingDevices();
   if( !m_recordingDevices )
      return -1;
   return 0;
}

int AgoraAudioManager::enumeratePlaybackDevices()
{
   if( !m_audioDeviceManager )
      return -1;
   if( m_playbackDevices )
      m_playbackDevices->release();

   m_playbackDevices = m_audioDeviceManager->enumeratePlaybackDevices();
   if( !m_playbackDevices )
      return -1;
   return 0;
}

int AgoraAudioManager::isApplicationMuted( bool & Muted )
{
   if( m_playbackDevices )
      return m_playbackDevices->isApplicationMute( Muted );
   if( m_recordingDevices )
      return m_recordingDevices->isApplicationMute( Muted );
   return -1;
}

int AgoraAudioManager::setApplicationMuted( bool Muted )
{
   if( m_playbackDevices )
      return m_playbackDevices->setApplicationMute( Muted );
   if( m_recordingDevices )
      return m_recordingDevices->setApplicationMute( Muted );
   return -1;
}

int AgoraAudioManager::setApplicationVolume( int Volume )
{
   if( m_playbackDevices )
      return m_playbackDevices->setApplicationVolume( Volume );
   if( m_recordingDevices )
      return m_recordingDevices->setApplicationVolume( Volume );
   return -1;
}

int AgoraAudioManager::getApplicationVolume( int & Volume )
{
   if( m_playbackDevices )
      return m_playbackDevices->getApplicationVolume( Volume );
   if( m_recordingDevices )
      return m_recordingDevices->getApplicationVolume( Volume );
   return -1;
}

int AgoraAudioManager::isRecordingDeviceMuted( bool & Muted )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->getRecordingDeviceMute( &Muted );
}

int AgoraAudioManager::isPlaybackDeviceMuted( bool & Muted )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->getPlaybackDeviceMute( &Muted );
}

int AgoraAudioManager::setRecordingDeviceMuted( bool Muted )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->setRecordingDeviceMute( Muted );
}

int AgoraAudioManager::setPlaybackDeviceMuted( bool Muted )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->setPlaybackDeviceMute( Muted );
}

int AgoraAudioManager::getRecordingDeviceVolume( int & Volume )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->getRecordingDeviceVolume( &Volume );
}

int AgoraAudioManager::getPlaybackDeviceVolume( int & Volume )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->getPlaybackDeviceVolume( &Volume );
}

int AgoraAudioManager::setRecordingDeviceVolume( int Volume )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->setRecordingDeviceVolume( Volume );
}

int AgoraAudioManager::setPlaybackDeviceVolume( int Volume )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->setPlaybackDeviceVolume( Volume );
}

int AgoraAudioManager::startRecordingDeviceTest( int indicationInterval )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->startRecordingDeviceTest( indicationInterval );
}

int AgoraAudioManager::stopRecordingDeviceTest()
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->stopRecordingDeviceTest();
}

int AgoraAudioManager::startPlaybackDeviceTest( const FString& testAudioFilePath )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->startPlaybackDeviceTest( TCHAR_TO_ANSI( *testAudioFilePath ) );
}

int AgoraAudioManager::stopPlaybackDeviceTest()
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->stopPlaybackDeviceTest();
}

int AgoraAudioManager::startAudioDeviceLoopbackTest( int indicationInterval )
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->startAudioDeviceLoopbackTest( indicationInterval );
}

int AgoraAudioManager::stopAudioDeviceLoopbackTest()
{
   if( !m_audioDeviceManager )
      return -1;
   return m_audioDeviceManager->stopAudioDeviceLoopbackTest();
}


AgoraAudioManager::~AgoraAudioManager()
{
   if( m_recordingDevices )
      m_recordingDevices->release();
   m_recordingDevices = nullptr;
   if( m_playbackDevices )
      m_playbackDevices->release();
   m_playbackDevices = nullptr;
   //todo: makes crash
   /*
   if( m_audioDeviceManager )
      m_audioDeviceManager->release();
   m_audioDeviceManager.reset(nullptr);
   */
}
}
}