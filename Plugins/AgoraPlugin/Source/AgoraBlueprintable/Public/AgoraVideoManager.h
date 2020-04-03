// Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "AgoraRtcEngine.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MediaDevice.h"

class UIAgora;
namespace agora
{
namespace blueprints
{
/**
Helps manage video recording devices
*/
class AGORABLUEPRINTABLE_API AgoraVideoManager
{
public:
   AgoraVideoManager() = default;
   ~AgoraVideoManager();

   /**
   Creates Agora Video Manager

   Use this function to create Agora Video Manager properly.
   @return 
    - Success : UniquePtr to AgoraVideoManager.
    - Failure : nullptr. Reason will be written to log, search "AgoraVideoManager::Create".
   */
   static TUniquePtr<AgoraVideoManager> Create( UIAgora* agora );

   /** @ref UIAgora::GetVideoRecordingDevices "GetVideoRecordingDevices" */
   TArray<FMediaDevice> getRecordingDevices();

   /** @ref UIAgora::GetVideoRecordingDevice "GetVideoRecordingDevice" */
   int getRecordingDevice( int Index, FString& DeviceName, FString& DeviceID );
   
   /** @ref UIAgora::SetCurrentVideoRecordingDevice "SetCurrentVideoRecordingDevice" */
   int setCurrentRecordingDevice( const FString& DeviceID );
   
   /** @ref UIAgora::GetCurrentVideoRecordingDevice "GetCurrentVideoRecordingDevice" */
   int getCurrentRecordingDevice( int& Index, FString& DeviceName, FString& DeviceID );
   
   /** @ref UIAgora::GetVideoRecordingDeviceCount "GetVideoRecordingDeviceCount" */
   int getRecordingDeviceCount();
   
   /** @ref UIAgora::EnumerateVideoRecordingDevices "EnumerateVideoRecordingDevices" */
   int enumerateRecordingDevices();

private:
   /** Native agora video device manager */
   agora::util::AutoPtr<agora::rtc::IVideoDeviceManager> m_videoDeviceManager;
   
   /** Collection of video recording devices */
   agora::rtc::IVideoDeviceCollection* m_recordingDevices = nullptr;
};
}
}