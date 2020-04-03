//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include <memory>

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/IAgoraRtcEngine.h>
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

namespace agora
{
namespace rtc
{
namespace ue4
{

class AgoraRtcEngine;

/**
 * Wrapper around agora::rtc::IVideoDeviceCollection
 */
class AGORAPLUGIN_API VideoDeviceCollection
{
public:
	VideoDeviceCollection() = delete;
	VideoDeviceCollection(agora::rtc::IVideoDeviceCollection* collection);
	VideoDeviceCollection(const VideoDeviceCollection& other);
	VideoDeviceCollection(VideoDeviceCollection&& other) noexcept;
	VideoDeviceCollection& operator=(const VideoDeviceCollection& other);
	VideoDeviceCollection& operator=(VideoDeviceCollection&& other) noexcept;

	~VideoDeviceCollection();

public:
   /**
   * @brief           Retrieves the total number of the indexed video devices in the system.
   * @return          Total number of the indexed video devices
   */
	int getCount();

   /**
   * @brief           Retrieves a specified piece of information about an indexed video device.
   * @param           index
   *                  The specified index of the video device that must be less than the return value of \ref IVideoDeviceCollection::getCount "getCount".
   * @param           deviceName
   *                  Pointer to the video device name.
   * @param           deviceId
   *                  Pointer to the video device ID.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int getDevice(
		int index,
		char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH],
		char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /**
   * @brief           Specifies a device with the device ID.
   * @param           deviceId
   *                  Pointer to the device ID of the device.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

private:
   /**
   * @brief          Releases all VideoDeviceCollection resources.
   */
	void release();

private:
	agora::rtc::IVideoDeviceCollection* m_videoDeviceCollection = nullptr;
};

/**
 * Wrapper around agora::rtc::IVideoDeviceManager
 */
class AGORAPLUGIN_API AgoraVideoDeviceManager
{
public:
	AgoraVideoDeviceManager() = default;
	
	AgoraVideoDeviceManager(const AgoraVideoDeviceManager& other) = delete;
	AgoraVideoDeviceManager(AgoraVideoDeviceManager&& other) noexcept = delete;
	AgoraVideoDeviceManager& operator=(const AgoraVideoDeviceManager& other) = delete;
	AgoraVideoDeviceManager& operator=(AgoraVideoDeviceManager&& other) noexcept = delete;

	~AgoraVideoDeviceManager() = default;

	static AgoraVideoDeviceManager* Create(AgoraRtcEngine* RtcEngine);
public:

   /**
   * @brief          Enumerates the video devices.
   * @brief          This method returns an \ref VideoDeviceCollection object including all video devices in the system. 
   *                 With the \ref VideoDeviceCollection object, the application can enumerate the video devices. 
   * @note           The application must call the release method to \ref release the returned object after using it.
   * @return
   *                 -  An IVideoDeviceCollection object including all video devices in the system: Success.
   *                 -  nullptr: Failure.
   */
	VideoDeviceCollection* enumerateVideoDevices();

   /**
   * @brief          Starts the video-capture device test.
   * @brief          This method tests whether the video-capture device works properly. 
   *                 Before calling this method, ensure that you have already called the \ref enableVideo method, and the window handle (hwnd) parameter is valid.
   * @param          hwnd
   *                 The window handle used to display the screen.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int startDeviceTest(agora::rtc::view_t hwnd);

   /**
   * @brief          Stops the video-capture device test.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int stopDeviceTest();

   /**
   * @brief          Sets a device with the device ID.
   * @param          deviceId
   *                 Pointer to the video-capture device ID. Call the \ref enumerateVideoDevices method to retrieve it.
   * @note           Plugging or unplugging the device does not change the device ID.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /**
   * @brief          Retrieves the video-capture device that is in use.
   * @param          deviceId
   *                 Pointer to the video-capture device ID.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

private:
	bool queryInterface(AgoraRtcEngine* engine);

   /**
   * @brief          Releases all VideoDeviceManager resources.
   */
	void release();

private:
	agora::util::AutoPtr<agora::rtc::IVideoDeviceManager> m_videoDeviceManager;
};

}
}
}