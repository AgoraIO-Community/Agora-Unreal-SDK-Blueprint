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
 * Wrapper around agora::rtc::IAudioDeviceCollection
 */
class AGORAPLUGIN_API AudioDeviceCollection
{

public:
	AudioDeviceCollection() = delete;
	AudioDeviceCollection(agora::rtc::IAudioDeviceCollection* collection);
	AudioDeviceCollection(const AudioDeviceCollection& other);
	AudioDeviceCollection(AudioDeviceCollection&& other) noexcept;
	AudioDeviceCollection& operator=(const AudioDeviceCollection& other);
	AudioDeviceCollection& operator=(AudioDeviceCollection&& other) noexcept;
	~AudioDeviceCollection();

public:

   /**
   * @brief           Retrieves the total number of audio playback or audio recording devices.
   * @note            You must first call the \ref IAudioDeviceManager::enumeratePlaybackDevices "enumeratePlaybackDevices"
   *                  or \ref IAudioDeviceManager::enumerateRecordingDevices "enumerateRecordingDevices" method before calling this method to return the number of  audio playback or audio recording devices.
   * @return          Number of audio playback or audio recording devices.
   */
	int getCount();

   /**
   * @brief           Retrieves a specified piece of information about an indexed audio device.
   * @param           index
   *                  The specified index that must be less than the return value of \ref IAudioDeviceCollection::getCount "getCount".
   * @param           deviceName
   *                  Pointer to the audio device name.
   * @param           deviceId
   *                  Pointer to the audio device ID.
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

   /**
   * @brief           Sets the volume of the application.
   * @param           volume
   *                  Application volume. The value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int setApplicationVolume(int volume);

   /**
   * @brief           Retrieves the volume of the application.
   * @param           volume
   *                  Pointer to the application volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int getApplicationVolume(int& volume);

   /**
   * @brief           Mutes the application.
   * @param           mute
   *                  Sets whether to mute/unmute the application:
   *                  - true: Mute the application.
   *                  - false: Unmute the application.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int setApplicationMute(bool mute);

   /**
   * @brief           Gets the mute state of the application.
   * @param           mute
   *                  Pointer to whether the application is muted/unmuted.
   *                  - true: The application is muted.
   *                  - false: The application is not muted.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int isApplicationMute(bool& mute);

private:
   /**
   * @brief          Releases all AudioDeviceCollection resources.
   */
	void release();

private:
	agora::rtc::IAudioDeviceCollection* m_audioDeviceCollection = nullptr;
};


/**
 * Wrapper around agora::rtc::IAudioDeviceManager
 */
class AGORAPLUGIN_API AgoraAudioDeviceManager
{
public:
	AgoraAudioDeviceManager() = default;

	AgoraAudioDeviceManager(const AgoraAudioDeviceManager& other) = delete;
	AgoraAudioDeviceManager(AgoraAudioDeviceManager&& other) noexcept = delete;
	AgoraAudioDeviceManager& operator=(const AgoraAudioDeviceManager& other) = delete;
	AgoraAudioDeviceManager& operator=(AgoraAudioDeviceManager&& other) noexcept = delete;

	~AgoraAudioDeviceManager() = default;

   /**
   * @brief          Creates the AudioDeviceManager object
   * @param          RtcEngine
   *                 Pointer to the RtcEngine object.
   * @return
   *                 -  Success: Returns a pointer to the AudioDeviceManager object
   *                 -  Failure: Returns nullptr.
   */
	static AgoraAudioDeviceManager* Create(AgoraRtcEngine* RtcEngine);
public:

   /**
   * @brief          Enumerates the audio playback devices.
   * @brief          This method returns a pointer to \ref AudioDeviceCollection object that includes all audio playback devices in the system. 
   *                 With the \ref AudioDeviceCollection object, the application can enumerate the audio playback devices.
   * @note           The application must call the release method to \ref release the returned object after using it.
   * @return
   *                 -  Success: Returns an AudioDeviceCollection object that includes all audio playback devices in the system. 
   *                    For wireless Bluetooth headset devices with master and slave headsets, the master headset is the playback device.
   *                 -  Failure: Returns nullptr.
   */
	AudioDeviceCollection* enumeratePlaybackDevices();

   /**
   * @brief          Enumerates the audio recording devices.
   * @brief          This method returns a pointer to \ref AudioDeviceCollection object that includes all audio recording devices in the system. 
   *                 With the \ref AudioDeviceCollection object, the application can enumerate the audio recording devices.
   * @note           The application needs to call the \ref release method to release the returned object after using it.
   * @return
   *                 -  Success: Returns an AudioDeviceCollection object that includes all audio recording devices in the system. 
   *                    For wireless Bluetooth headset devices with master and slave headsets, the master headset is the playback device.
   *                 -  Failure: Returns nullptr.
   */
	AudioDeviceCollection* enumerateRecordingDevices();

   /**
   * @brief          Sets the audio playback device using the device ID.
   * @note           Plugging or unplugging the audio device does not change the device ID.
   * @param          deviceId 
   *                 Device ID of the audio playback device, retrieved by calling the \ref enumeratePlaybackDevices method.
   * @return
   *                 -  0: Success. 
   *                 -  < 0: Failure.
   */
	int setPlaybackDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /**
   * @brief          Sets the audio recording device using the device ID.
   * @note           Plugging or unplugging the audio device does not change the device ID.
   * @param          deviceId 
   *                 Device ID of the audio recording device, retrieved by calling the \ref enumerateRecordingDevices method.
   * @return
   *                 -  0: Success. 
   *                 -  < 0: Failure.
   */
	int setRecordingDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /**
   * @brief          Starts the audio playback device test.
   * @brief          This method tests if the playback device works properly. 
   *                 In the test, the SDK plays an audio file specified by the user. If the user can hear the audio, the playback device works properly.
   * @param          testAudioFilePath 
   *                 Pointer to the path of the audio file for the audio playback device test in UTF-8:
   *                 - Supported file formats: wav, mp3, m4a, and aac.
   *                 - Supported file sample rates: 8000, 16000, 32000, 44100, and 48000 Hz.
   * @return
   *                 -  0: Success, and you can hear the sound of the specified audio file.
   *                 -  < 0: Failure.
   */
	int startPlaybackDeviceTest(const char* testAudioFilePath);

   /**
   * @brief          Stops the audio playback device test.
   * @brief          This method stops testing the audio playback device. 
   *                 You must call this method to stop the test after calling the startPlaybackDeviceTest method.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int stopPlaybackDeviceTest();

   /**
   * @brief          Sets the volume of the audio playback device.
   * @param          volume
   *                 Sets the volume of the audio playback device. The value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setPlaybackDeviceVolume(int volume);

   /**
   * @brief          Retrieves the volume of the audio playback device.
   * @param          volume
   *                 Pointer to the audio playback device volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getPlaybackDeviceVolume(int* volume);

   /**
   * @brief          Sets the volume of the microphone.
   * @param          volume
   *                 Sets the volume of the microphone. The value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setRecordingDeviceVolume(int volume);

   /**
   * @brief          Retrieves the volume of the microphone.
   * @param          volume
   *                 Pointer to the microphone volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getRecordingDeviceVolume(int* volume);

   /**
   * @brief          Mutes the audio playback device.
   * @param          mute
   *                 Sets whether to mute/unmute the audio playback device:
   *                 -  true: Mutes.
   *                 -  false: Unmutes.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setPlaybackDeviceMute(bool mute);

   /**
   * @brief          Retrieves the mute status of the audio playback device.
   * @param          mute
   *                 Pointer to whether the audio playback device is muted/unmuted.
   *                 -  true: Muted.
   *                 -  false: Unmuted.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getPlaybackDeviceMute(bool *mute);

   /**
   * @brief          Mutes/Unmutes the microphone.
   * @param          mute
   *                 Sets whether to mute/unmute the microphone:
   *                 -  true: Mutes.
   *                 -  false: Unmutes.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setRecordingDeviceMute(bool mute);

   /**
   * @brief          Retrieves the microphone's mute status.
   * @param          mute
   *                 Pointer to whether the audio playback device is muted/unmuted.
   *                 -  true: Muted.
   *                 -  false: Unmuted.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getRecordingDeviceMute(bool* mute);

   /**
   * @brief          Starts the microphone test.
   * @brief          This method tests whether the microphone works properly.           
   *                 Once the test starts, the SDK uses the \ref onAudioVolumeIndication callback to notify the application with the volume information.
   * @param          indicationInterval
   *                 Interval period (ms) of the \ref onAudioVolumeIndication callback cycle.
   *
   *                 -  true: Muted.
   *                 -  false: Unmuted.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int startRecordingDeviceTest(int indicationInterval);

   /**
   * @brief          Stops the microphone test.
   * @brief          This method stops the microphone test.           
   *                 You must call this method to stop the test after calling the \ref startRecordingDeviceTest method.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int stopRecordingDeviceTest();

   /**
   * @brief          Retrieves the audio playback device associated with the device ID.
   * @param          deviceId
   *                 Pointer to the ID of the audio playback device.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getPlaybackDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /**
   * @brief          Retrieves the audio playback device information associated with the device ID and device name.
   * @param          deviceId
   *                 Pointer to the ID of the audio playback device.
   * @param          deviceName
   *                 Pointer to the device name of the audio playback device.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getPlaybackDeviceInfo(
		char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH],
		char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /**
   * @brief          Retrieves the audio recording device associated with the device ID.
   * @param          deviceId
   *                 Pointer to the device ID of the audio recording device.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getRecordingDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /**
   * @brief          Retrieves the audio recording device information associated with the device ID and device name.
   * @param          deviceId
   *                 Pointer to the device ID of the recording audio device.
   * @param          deviceName
   *                 Pointer to the device name of the recording audio device.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getRecordingDeviceInfo(
		char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH],
		char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /**
   * @brief          Starts the audio device loopback test.
   * @brief          This method tests whether the local audio devices are working properly. 
   *                 After calling this method, the microphone captures the local audio and plays it through the speaker. 
   *                 The \ref onAudioVolumeIndication callback returns the local audio volume information at the set interval.
   * @note           This method tests the local audio devices and does not report the network conditions.
   * @param          indicationInterval
   *                 The time interval (ms) at which the \ref onAudioVolumeIndication callback returns.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int startAudioDeviceLoopbackTest(int indicationInterval);

   /**
   * @brief          Stops the audio device loopback test.
   * @note           Ensure that you call this method to stop the loopback test after calling the \ref startAudioDeviceLoopbackTest method.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int stopAudioDeviceLoopbackTest();

private:
	bool queryInterface(AgoraRtcEngine* engine);

   /**
   * @brief Releases all AudioDeviceManager resources.
   */
	void release();

private:
	agora::util::AutoPtr<agora::rtc::IAudioDeviceManager> m_audioDeviceManager;
};

}
}
}