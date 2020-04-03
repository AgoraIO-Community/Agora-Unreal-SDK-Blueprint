//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/AgoraBase.h>
#include <Agora/IAgoraRtcEngine.h>
#include <Agora/IAgoraMediaEngine.h>
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
}
}
}

namespace agora
{
namespace media
{
namespace ue4
{

/**
 * Wrapper around agora::media::IMediaEngine
 */
class AGORAPLUGIN_API AgoraMediaEngine
{
public:
	AgoraMediaEngine() = default;

	AgoraMediaEngine(const AgoraMediaEngine& other) = delete;
	AgoraMediaEngine(AgoraMediaEngine&& other) noexcept = delete;
	AgoraMediaEngine& operator=(const AgoraMediaEngine& other) = delete;
	AgoraMediaEngine& operator=(AgoraMediaEngine&& other) noexcept = delete;

	~AgoraMediaEngine() = default;

   /**
   * @brief          Creates the MediaEngine object
   * @param          RtcEngine
   *                 Pointer to the RtcEngine object.
   * @return
   *                 -  Success: Returns a pointer to the AudioDeviceManager object
   *                 -  Failure: Returns nullptr.
   */
	static AgoraMediaEngine* Create(agora::rtc::ue4::AgoraRtcEngine* RtcEngine);
public:

   /** 
   * @brief          Registers an audio frame observer object.
   * @brief          This method is used to register an audio frame observer object (register a callback).
   *                 This method is required to register callbacks when the engine is required to provide an \ref IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame"
   *                 or \ref IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback.
   * @param          observer 
   *                 Audio frame observer object instance. If NULL is passed in, the registration is canceled.
   * @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	int registerAudioFrameObserver(agora::media::IAudioFrameObserver* observer);

   /** 
   * @brief          Registers a video frame observer object.
   * @brief          You need to implement the IVideoFrameObserver class in this method, and register the following callbacks according to your scenarios:
   *                 - \ref IVideoFrameObserver::onCaptureVideoFrame "onCaptureVideoFrame": Occurs each time the SDK receives a video frame captured by the local camera.
   *                 - \ref IVideoFrameObserver::onRenderVideoFrame "onRenderVideoFrame": Occurs each time the SDK receives a video frame sent by the remote user.
   *                 - \ref IVideoFrameObserver::getVideoFormatPreference "getVideoFormatPreference": Occurs each time the SDK receives a video frame and prompts you to set the video format. YUV420 is the default video format. 
   * @brief          If you want to receive other video formats, register this callback in the IVideoFrameObserver class. 
   *                 - \ref IVideoFrameObserver::getRotationApplied "getRotationApplied": Occurs each time the SDK receives a video frame and prompts you whether or not to rotate the captured video according to the rotation member in the VideoFrame class. 
   *                 This callback applies to RGBA video data only.
   *                 - \ref IVideoFrameObserver::getMirrorApplied "getMirrorApplied": Occurs each time the SDK receives a video frame and prompts you whether or not to mirror the captured video. This callback applies to RGBA video data only.
   *                 After you successfully register the video frame observer, the SDK triggers the registered callbacks each time a video frame is received.
   *
   * @param          observer 
   *                 Video frame observer object instance. If NULL is passed in, the registration is canceled.
   * @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	int registerVideoFrameObserver(agora::media::IVideoFrameObserver* observer);

   /** 
   * @brief          Pushes the external audio frame.
   * @param          frame 
   *                 Pointer to the audio frame: \ref IAudioFrameObserver::AudioFrame "AudioFrame".
   *  @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	int pushAudioFrame(agora::media::IAudioFrameObserver::AudioFrame* frame);

   /** 
   * @brief          Pulls the remote audio data.
   * @brief          Before calling this method, call the 
   *                 \ref agora::rtc::IRtcEngine::setExternalAudioSink 
   *                 "setExternalAudioSink(enabled: true)" method to enable and set the 
   *                 external audio sink.
   * @brief          After a successful method call, the app pulls the decoded and mixed 
   *                 audio data for playback.
   * @note
   *                 - Once you call the \ref agora::media::IMediaEngine::pullAudioFrame 
   *                 "pullAudioFrame" method successfully, the app will not retrieve any audio 
   *                 data from the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame
   *                 "onPlaybackAudioFrame" callback.
   *                 - The difference between the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame 
   *                 "onPlaybackAudioFrame" callback and the 
   *                 \ref agora::media::IMediaEngine::pullAudioFrame "pullAudioFrame" method is as follows:
   *                  - `onPlaybackAudioFrame`: The SDK sends the audio data to the app once 
   *                 every 10 ms. Any delay in processing the audio frames may result in audio 
   *                 jitter.
   *                  - `pullAudioFrame`: The app pulls the remote audio data. After setting the 
   *                 audio data parameters, the SDK adjusts the frame buffer and avoids 
   *                 problems caused by jitter in the external audio playback.
   * 
   * @param          frame 
   *                 Pointers to the audio frame. 
   *                 See: \ref IAudioFrameObserver::AudioFrame "AudioFrame".
   * 
   * @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	int pullAudioFrame(agora::media::IAudioFrameObserver::AudioFrame* frame);

   /** 
   * @brief         Configures the external video source.
   * @param         enable 
   *                Sets whether to use the external video source:
   *                - true: Use the external video source.
   *                - false: (Default) Do not use the external video source.
   * @param         useTexture 
   *                Sets whether to use texture as an input:
   *                - true: Use texture as an input.
   *                - false: (Default) Do not use texture as an input.
   * @return
                    - 0: Success.
                    - < 0: Failure.
   */
	int setExternalVideoSource(bool enable, bool useTexture);

   /** 
   * @brief         Pushes the video frame using the \ref ExternalVideoFrame "ExternalVideoFrame" and passes the video frame to the Agora SDK.
   * @param         frame 
   *                Video frame to be pushed. See \ref ExternalVideoFrame "ExternalVideoFrame".
   * @note          In the Communication profile, this method does not support video frames in the Texture format.
   * @return
   *                - 0: Success.
   *                - < 0: Failure.
   */
	int pushVideoFrame(agora::media::ExternalVideoFrame* frame);

private:
	bool queryInterface(agora::rtc::ue4::AgoraRtcEngine* AgoraEngine);

   /**
   * @brief         Releases all MediaEngine resources.
   */
	void release();

private:
	agora::util::AutoPtr<agora::media::IMediaEngine> m_mediaEngine;
};

}
}
}
