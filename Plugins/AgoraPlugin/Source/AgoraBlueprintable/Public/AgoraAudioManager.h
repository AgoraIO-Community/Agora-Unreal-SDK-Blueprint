// Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MediaDevice.h"
#include "AgoraRtcEngine.h"

class UIAgora;
namespace agora
{
//todo: better name for namespace?
namespace blueprints
{
/**
Class that helps manage audio playback and audio recording devices
*/
class AGORABLUEPRINTABLE_API AgoraAudioManager
{
public:
   AgoraAudioManager() = default;
   ~AgoraAudioManager();

   /**
   Creates Agora Audio Manager

   Use this function to create Agora Audio Manager properly.
   @return 
    - Success : UniquePtr to AgoraAudioManager.
    - Failure : nullptr. Reason will be written to log, search "AgoraAudioManager::Create".
   */
   static TUniquePtr<AgoraAudioManager> Create( UIAgora* agoraEngine );

   /** @ref UIAgora::GetAudioRecordingDevices "GetAudioRecordingDevices"*/
   TArray<FMediaDevice> getRecordingDevices();

   /** @ref UIAgora::GetAudioPlaybackDevices "GetAudioPlaybackDevices"*/
   TArray<FMediaDevice> getPlaybackDevices();

   /** @ref UIAgora::SetCurrentAudioRecordingDevice "SetCurrentAudioRecordingDevice"*/
   int setCurrentRecordingDevice( const FString& DeviceID );

   /** @ref UIAgora::SetCurrentAudioPlaybackDevice "SetCurrentAudioPlaybackDevice"*/
   int setCurrentPlaybackDevice( const FString& DeviceID );

   /** @ref UIAgora::GetCurrentAudioRecordingDevice "GetCurrentAudioRecordingDevice"*/
   int getCurrentRecordingDevice( int& Index, FString& DeviceName, FString& DeviceID );

   /** @ref UIAgora::GetCurrentAudioPlaybackDevice "GetCurrentAudioPlaybackDevice"*/
   int getCurrentPlaybackDevice( int& Index, FString& DeviceName, FString& DeviceID );

   /** @ref UIAgora::GetAudioRecordingDeviceCount "GetAudioRecordingDeviceCount"*/
   int getRecordingDeviceCount();

   /** @ref UIAgora::GetAudioPlaybackDeviceCount "GetAudioPlaybackDeviceCount"*/
   int getPlaybackDeviceCount();

   /** @ref UIAgora::EnumerateAudioRecordingDevices "EnumerateAudioRecordingDevices"*/
   int enumerateRecordingDevices();

   /** @ref UIAgora::EnumerateAudioPlaybackDevices "EnumerateAudioPlaybackDevices"*/
   int enumeratePlaybackDevices();

   /** @ref UIAgora::IsApplicationMuted "IsApplicationMuted"*/
   int isApplicationMuted( bool& Muted );

   /** @ref UIAgora::SetApplicationMuted "SetApplicationMuted"*/
   int setApplicationMuted( bool Muted );

   /** @ref UIAgora::SetApplicationVolume "SetApplicationVolume"*/
   int setApplicationVolume( int Volume );

   /** @ref UIAgora::GetApplicationVolume "GetApplicationVolume"*/
   int getApplicationVolume( int& Volume );

   /** @ref UIAgora::IsAudioRecordingDeviceMuted "IsAudioRecordingDeviceMuted"*/
   int isRecordingDeviceMuted( bool& Muted );

   /** @ref UIAgora::IsAudioPlaybackDeviceMuted "IsAudioPlaybackDeviceMuted"*/
   int isPlaybackDeviceMuted( bool& Muted );

   /** @ref UIAgora::SetAudioRecordingDeviceMuted "SetAudioRecordingDeviceMuted"*/
   int setRecordingDeviceMuted( bool Muted );

   /** @ref UIAgora::SetAudioPlaybackDeviceMuted "SetAudioPlaybackDeviceMuted"*/
   int setPlaybackDeviceMuted( bool Muted );

   /** @ref UIAgora::GetAudioRecordingDeviceVolume "GetAudioRecordingDeviceVolume"*/
   int getRecordingDeviceVolume( int& Volume );

   /** @ref UIAgora::GetAudioPlaybackDeviceVolume "GetAudioPlaybackDeviceVolume"*/
   int getPlaybackDeviceVolume( int& Volume );

   /** @ref UIAgora::SetAudioRecordingDeviceVolume "SetAudioRecordingDeviceVolume"*/
   int setRecordingDeviceVolume( int Volume );

   /** @ref UIAgora::SetAudioPlaybackDeviceVolume "SetAudioPlaybackDeviceVolume"*/
   int setPlaybackDeviceVolume( int Volume );

   /** @ref UIAgora::StartAudioRecordingDeviceTest "StartAudioRecordingDeviceTest"*/
   int startRecordingDeviceTest( int indicationInterval );

   /** @ref UIAgora::StopAudioRecordingDeviceTest "StopAudioRecordingDeviceTest"*/
   int stopRecordingDeviceTest();

   /** @ref UIAgora::StartAudioPlaybackDeviceTest "StartAudioPlaybackDeviceTest"*/
   int startPlaybackDeviceTest( const FString& testAudioFilePath );

   /** @ref UIAgora::StopAudioPlaybackDeviceTest "StopAudioPlaybackDeviceTest"*/
   int stopPlaybackDeviceTest();

   /** @ref UIAgora::StartAudioDeviceLoopbackTest "StartAudioDeviceLoopbackTest"*/
   int startAudioDeviceLoopbackTest( int indicationInterval );

   /** @ref UIAgora::StopAudioDeviceLoopbackTest "StopAudioDeviceLoopbackTest"*/
   int stopAudioDeviceLoopbackTest();

private:
   /** Retrieves FMediaDevice from device collection
   @param[in] devices Native agora AudioDeviceCollection
   @param[out] device Device info
   @return
      - 0: Success.
      - < 0 : Failure.
   */
   int getDevice( agora::rtc::IAudioDeviceCollection* devices, FMediaDevice& device );
   
   /** Retrieves available devices from audio device collection
   @param[in] devices Native agora AudioDeviceCollection
   @return Set of available audio devices
   */
   TArray<FMediaDevice> getDevices( agora::rtc::IAudioDeviceCollection* devices );

private:
   /** Native agora audio device manager */
   agora::util::AutoPtr<agora::rtc::IAudioDeviceManager> m_audioDeviceManager;

   /** Collection of audio recording devices */
   agora::rtc::IAudioDeviceCollection* m_recordingDevices = nullptr;
   /** Collection of audio playback devices */
   agora::rtc::IAudioDeviceCollection* m_playbackDevices = nullptr;
};
}
}