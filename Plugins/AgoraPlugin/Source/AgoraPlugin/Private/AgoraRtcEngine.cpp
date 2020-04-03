//  Copyright (c) 2019 Agora.io. All rights reserved.

#include "AgoraRtcEngine.h"

#include <utility>

namespace agora
{
namespace rtc
{
namespace ue4
{

AgoraRtcEngine::AgoraRtcEngine(const AgoraRtcEngine& other)
	: m_rtcEngine(other.m_rtcEngine)
{
}
AgoraRtcEngine::AgoraRtcEngine(AgoraRtcEngine&& other) noexcept
	: m_rtcEngine(std::exchange(other.m_rtcEngine, nullptr))
{
}
AgoraRtcEngine& AgoraRtcEngine::operator=(const AgoraRtcEngine& other)
{
	return *this = AgoraRtcEngine(other);
}
AgoraRtcEngine& AgoraRtcEngine::operator=(AgoraRtcEngine&& other) noexcept
{
	std::swap(m_rtcEngine, other.m_rtcEngine);
	return *this;
}

AgoraRtcEngine::AgoraRtcEngine(agora::rtc::IRtcEngine* rtcEngine)
	: m_rtcEngine(rtcEngine)
{
}

AgoraRtcEngine::~AgoraRtcEngine()
{
	release(m_sync);
}

AgoraRtcEngine* AgoraRtcEngine::createAgoraRtcEngine()
{
	agora::rtc::IRtcEngine* agoraEngine = ::createAgoraRtcEngine();
	if (!agoraEngine)
	{
		return nullptr;
	}
	return new AgoraRtcEngine(agoraEngine);
}

int AgoraRtcEngine::initialize(const agora::rtc::RtcEngineContext& rtcEngineContext)
{
	return m_rtcEngine->initialize(rtcEngineContext);
}

void AgoraRtcEngine::setSyncForRelease(bool sync)
{
	m_sync = sync;
}

void AgoraRtcEngine::release(bool sync)
{
	m_rtcEngine->release(sync);
}

int AgoraRtcEngine::setChannelProfile(agora::rtc::CHANNEL_PROFILE_TYPE profile)
{
	return m_rtcEngine->setChannelProfile(profile);
}

int AgoraRtcEngine::setClientRole(agora::rtc::CLIENT_ROLE_TYPE role)
{
	return m_rtcEngine->setClientRole(role);
}

int AgoraRtcEngine::joinChannel(const char* token, const char* channelId, const char* info, agora::rtc::uid_t uid)
{
	return m_rtcEngine->joinChannel(token, channelId, info, uid);
}

int AgoraRtcEngine::switchChannel(const char* token, const char* channelId)
{
	return m_rtcEngine->switchChannel(token, channelId);
}

int AgoraRtcEngine::leaveChannel()
{
	return m_rtcEngine->leaveChannel();
}

int AgoraRtcEngine::renewToken(const char* token)
{
	return m_rtcEngine->renewToken(token);
}

int AgoraRtcEngine::registerLocalUserAccount(const char* appId, const char* userAccount)
{
	return m_rtcEngine->registerLocalUserAccount(appId, userAccount);
}

int AgoraRtcEngine::joinChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount)
{
	return m_rtcEngine->joinChannelWithUserAccount(token, channelId, userAccount);
}

int AgoraRtcEngine::getUserInfoByUserAccount(const char* userAccount, UserInfo* userInfo)
{
	return m_rtcEngine->getUserInfoByUserAccount(userAccount, userInfo);
}

int AgoraRtcEngine::getUserInfoByUid(uid_t uid, UserInfo* userInfo)
{
	return m_rtcEngine->getUserInfoByUid(uid, userInfo);
}

int AgoraRtcEngine::startEchoTest(int intervalInSeconds)
{
	return m_rtcEngine->startEchoTest(intervalInSeconds);
}

int AgoraRtcEngine::stopEchoTest()
{
	return m_rtcEngine->stopEchoTest();
}

int AgoraRtcEngine::enableVideo()
{
	return m_rtcEngine->enableVideo();
}

int AgoraRtcEngine::disableVideo()
{
	return m_rtcEngine->disableVideo();
}

int AgoraRtcEngine::setVideoEncoderConfiguration(const VideoEncoderConfiguration& config)
{
	return m_rtcEngine->setVideoEncoderConfiguration(config);
}

int AgoraRtcEngine::setCameraCapturerConfiguration(const CameraCapturerConfiguration& config)
{
	return m_rtcEngine->setCameraCapturerConfiguration(config);
}

int AgoraRtcEngine::setupLocalVideo(const VideoCanvas& canvas)
{
	return m_rtcEngine->setupLocalVideo(canvas);
}

int AgoraRtcEngine::setupRemoteVideo(const VideoCanvas& canvas)
{
	return m_rtcEngine->setupRemoteVideo(canvas);
}

int AgoraRtcEngine::startPreview()
{
	return m_rtcEngine->startPreview();
}

int AgoraRtcEngine::setRemoteUserPriority(agora::rtc::uid_t uid, agora::rtc::PRIORITY_TYPE userPriority)
{
	return m_rtcEngine->setRemoteUserPriority(uid, userPriority);
}

int AgoraRtcEngine::stopPreview()
{
	return m_rtcEngine->stopPreview();
}

int AgoraRtcEngine::enableAudio()
{
	return m_rtcEngine->enableAudio();
}

int AgoraRtcEngine::enableLocalAudio(bool enabled)
{
	return m_rtcEngine->enableLocalAudio(enabled);
}

int AgoraRtcEngine::disableAudio()
{
	return m_rtcEngine->disableAudio();
}

int AgoraRtcEngine::setAudioProfile(agora::rtc::AUDIO_PROFILE_TYPE profile, agora::rtc::AUDIO_SCENARIO_TYPE scenario)
{
	return m_rtcEngine->setAudioProfile(profile, scenario);
}

int AgoraRtcEngine::muteLocalAudioStream(bool mute)
{
	return m_rtcEngine->muteLocalAudioStream(mute);
}

int AgoraRtcEngine::muteAllRemoteAudioStreams(bool mute)
{
	return m_rtcEngine->muteAllRemoteAudioStreams(mute);
}

int AgoraRtcEngine::setDefaultMuteAllRemoteAudioStreams(bool mute)
{
	return m_rtcEngine->setDefaultMuteAllRemoteAudioStreams(mute);
}

int AgoraRtcEngine::muteRemoteAudioStream(agora::rtc::uid_t userId, bool mute)
{
	return m_rtcEngine->muteRemoteAudioStream(userId, mute);
}

int AgoraRtcEngine::muteLocalVideoStream(bool mute)
{
	return m_rtcEngine->muteLocalVideoStream(mute);
}

int AgoraRtcEngine::enableLocalVideo(bool enabled)
{
	return m_rtcEngine->enableLocalVideo(enabled);
}

int AgoraRtcEngine::muteAllRemoteVideoStreams(bool mute)
{
	return m_rtcEngine->muteAllRemoteVideoStreams(mute);
}

int AgoraRtcEngine::setDefaultMuteAllRemoteVideoStreams(bool mute)
{
	return m_rtcEngine->setDefaultMuteAllRemoteVideoStreams(mute);
}

int AgoraRtcEngine::muteRemoteVideoStream(agora::rtc::uid_t userId, bool mute)
{
	return m_rtcEngine->muteRemoteVideoStream(userId, mute);
}

int AgoraRtcEngine::setRemoteVideoStreamType(agora::rtc::uid_t userId, agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType)
{
	return m_rtcEngine->setRemoteVideoStreamType(userId, streamType);
}

int AgoraRtcEngine::setRemoteDefaultVideoStreamType(agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType)
{
	return m_rtcEngine->setRemoteDefaultVideoStreamType(streamType);
}

int AgoraRtcEngine::enableAudioVolumeIndication(int interval, int smooth, bool report_vad)
{
	return m_rtcEngine->enableAudioVolumeIndication(interval, smooth, report_vad);
}

int AgoraRtcEngine::startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality)
{
	return m_rtcEngine->startAudioRecording(filePath, sampleRate, quality);
}

int AgoraRtcEngine::stopAudioRecording()
{
	return m_rtcEngine->stopAudioRecording();
}

int AgoraRtcEngine::startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle)
{
	return m_rtcEngine->startAudioMixing(filePath, loopback, replace, cycle);
}

int AgoraRtcEngine::stopAudioMixing()
{
	return m_rtcEngine->stopAudioMixing();
}

int AgoraRtcEngine::pauseAudioMixing()
{
	return m_rtcEngine->pauseAudioMixing();
}

int AgoraRtcEngine::resumeAudioMixing()
{
	return m_rtcEngine->resumeAudioMixing();
}

int AgoraRtcEngine::adjustAudioMixingVolume(int volume)
{
	return m_rtcEngine->adjustAudioMixingVolume(volume);
}

int AgoraRtcEngine::adjustAudioMixingPlayoutVolume(int volume)
{
	return m_rtcEngine->adjustAudioMixingPlayoutVolume(volume);
}

int AgoraRtcEngine::getAudioMixingPlayoutVolume()
{
	return m_rtcEngine->getAudioMixingPlayoutVolume();
}

int AgoraRtcEngine::adjustAudioMixingPublishVolume(int volume)
{
	return m_rtcEngine->adjustAudioMixingPublishVolume(volume);
}

int AgoraRtcEngine::getAudioMixingPublishVolume()
{
	return m_rtcEngine->getAudioMixingPublishVolume();
}

int AgoraRtcEngine::getAudioMixingDuration()
{
	return m_rtcEngine->getAudioMixingDuration();
}

int AgoraRtcEngine::getAudioMixingCurrentPosition()
{
	return m_rtcEngine->getAudioMixingCurrentPosition();
}

int AgoraRtcEngine::setAudioMixingPosition(int pos /*in ms*/)
{
	return m_rtcEngine->setAudioMixingPosition(pos);
}

int AgoraRtcEngine::getEffectsVolume()
{
	return m_rtcEngine->getEffectsVolume();
}

int AgoraRtcEngine::setEffectsVolume(int volume)
{
	return m_rtcEngine->setEffectsVolume(volume);
}

int AgoraRtcEngine::setVolumeOfEffect(int soundId, int volume)
{
	return m_rtcEngine->setVolumeOfEffect(soundId, volume);
}

int AgoraRtcEngine::playEffect(
	int soundId,
	const char* filePath,
	int loopCount,
	double pitch,
	double pan,
	int gain,
	bool publish)
{
	return m_rtcEngine->playEffect(soundId, filePath, loopCount, pitch, pan, gain, publish);
}

int AgoraRtcEngine::stopEffect(int soundId)
{
	return m_rtcEngine->stopEffect(soundId);
}

int AgoraRtcEngine::stopAllEffects()
{
	return m_rtcEngine->stopAllEffects();
}

int AgoraRtcEngine::preloadEffect(int soundId, const char* filePath)
{
	return m_rtcEngine->preloadEffect(soundId, filePath);
}

int AgoraRtcEngine::unloadEffect(int soundId)
{
	return m_rtcEngine->unloadEffect(soundId);
}

int AgoraRtcEngine::pauseEffect(int soundId)
{
	return m_rtcEngine->pauseEffect(soundId);
}

int AgoraRtcEngine::pauseAllEffects()
{
	return m_rtcEngine->pauseAllEffects();
}

int AgoraRtcEngine::resumeEffect(int soundId)
{
	return m_rtcEngine->resumeEffect(soundId);
}

int AgoraRtcEngine::resumeAllEffects()
{
	return m_rtcEngine->resumeAllEffects();
}

int AgoraRtcEngine::enableSoundPositionIndication(bool enabled)
{
	return m_rtcEngine->enableSoundPositionIndication(enabled);
}

int AgoraRtcEngine::setRemoteVoicePosition(uid_t uid, double pan, double gain)
{
	return m_rtcEngine->setRemoteVoicePosition(uid, pan, gain);
}

int AgoraRtcEngine::setLocalVoicePitch(double pitch)
{
	return m_rtcEngine->setLocalVoicePitch(pitch);
}

int AgoraRtcEngine::setLocalVoiceEqualization(agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain)
{
	return m_rtcEngine->setLocalVoiceEqualization(bandFrequency, bandGain);
}

int AgoraRtcEngine::setLocalVoiceReverb(agora::rtc::AUDIO_REVERB_TYPE reverbKey, int value)
{
	return m_rtcEngine->setLocalVoiceReverb(reverbKey, value);
}

int AgoraRtcEngine::setLocalVoiceChanger(agora::rtc::VOICE_CHANGER_PRESET voiceChanger)
{
	return m_rtcEngine->setLocalVoiceChanger(voiceChanger);
}

int AgoraRtcEngine::setLocalVoiceReverbPreset(agora::rtc::AUDIO_REVERB_PRESET reverbPreset)
{
	return m_rtcEngine->setLocalVoiceReverbPreset(reverbPreset);
}

int AgoraRtcEngine::setLogFile(const char* filePath)
{
	return m_rtcEngine->setLogFile(filePath);
}

int AgoraRtcEngine::setLogFilter(unsigned int filter)
{
	return m_rtcEngine->setLogFilter(filter);
}

int AgoraRtcEngine::setLogFileSize(unsigned int fileSizeInKBytes)
{
	return m_rtcEngine->setLogFileSize(fileSizeInKBytes);
}

int AgoraRtcEngine::setLocalRenderMode(agora::rtc::RENDER_MODE_TYPE renderMode)
{
	return m_rtcEngine->setLocalRenderMode(renderMode);
}

int AgoraRtcEngine::setRemoteRenderMode(agora::rtc::uid_t userId, agora::rtc::RENDER_MODE_TYPE renderMode)
{
	return m_rtcEngine->setRemoteRenderMode(userId, renderMode);
}

int AgoraRtcEngine::setLocalVideoMirrorMode(agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode)
{
	return m_rtcEngine->setLocalVideoMirrorMode(mirrorMode);
}

int AgoraRtcEngine::enableDualStreamMode(bool enabled)
{
	return m_rtcEngine->enableDualStreamMode(enabled);
}

int AgoraRtcEngine::setExternalAudioSource(bool enabled, int sampleRate, int channels)
{
	return m_rtcEngine->setExternalAudioSource(enabled, sampleRate, channels);
}

int AgoraRtcEngine::setExternalAudioSink(bool enabled, int sampleRate, int channels)
{
	return m_rtcEngine->setExternalAudioSink(enabled, sampleRate, channels);
}

int AgoraRtcEngine::setRecordingAudioFrameParameters(
	int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	return m_rtcEngine->setRecordingAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
}

int AgoraRtcEngine::setPlaybackAudioFrameParameters(
	int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall)
{
	return m_rtcEngine->setPlaybackAudioFrameParameters(sampleRate, channel, mode, samplesPerCall);
}

int AgoraRtcEngine::setMixedAudioFrameParameters(int sampleRate, int samplesPerCall)
{
	return m_rtcEngine->setMixedAudioFrameParameters(sampleRate, samplesPerCall);
}

int AgoraRtcEngine::adjustRecordingSignalVolume(int volume)
{
	return m_rtcEngine->adjustRecordingSignalVolume(volume);
}

int AgoraRtcEngine::adjustPlaybackSignalVolume(int volume)
{
	return m_rtcEngine->adjustPlaybackSignalVolume(volume);
}

int AgoraRtcEngine::enableWebSdkInteroperability(bool enabled)
{
	return m_rtcEngine->enableWebSdkInteroperability(enabled);
}

int AgoraRtcEngine::setLocalPublishFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option)
{
	return m_rtcEngine->setLocalPublishFallbackOption(option);
}

int AgoraRtcEngine::setRemoteSubscribeFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option)
{
	return m_rtcEngine->setRemoteSubscribeFallbackOption(option);
}

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)

int AgoraRtcEngine::switchCamera()
{
	return m_rtcEngine->switchCamera();
}
int AgoraRtcEngine::switchCamera(CAMERA_DIRECTION direction)
{
	return m_rtcEngine->switchCamera(direction);
}

int AgoraRtcEngine::setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker)
{
	return m_rtcEngine->setDefaultAudioRouteToSpeakerphone(defaultToSpeaker);
}

int AgoraRtcEngine::setEnableSpeakerphone(bool speakerOn)
{
	return m_rtcEngine->setEnableSpeakerphone(speakerOn);
}

int AgoraRtcEngine::setInEarMonitoringVolume(int volume)
{
	return m_rtcEngine->setInEarMonitoringVolume(volume);
}

bool AgoraRtcEngine::isSpeakerphoneEnabled()
{
	return m_rtcEngine->isSpeakerphoneEnabled();
}

#endif

#if (defined(__APPLE__) && TARGET_OS_IOS)
int AgoraRtcEngine::setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction)
{
	return m_rtcEngine->setAudioSessionOperationRestriction(restriction);
}
#endif

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
int AgoraRtcEngine::enableLoopbackRecording(bool enabled, const char* deviceName)
{
	return m_rtcEngine->enableLoopbackRecording(enabled, deviceName);
}
#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
int AgoraRtcEngine::startScreenCaptureByDisplayId(
	unsigned int displayId,
	const Rectangle& regionRect,
	const ScreenCaptureParameters& captureParams)
{
	return m_rtcEngine->startScreenCaptureByDisplayId(displayId, regionRect, captureParams);
}
#endif

#if defined(_WIN32)
int AgoraRtcEngine::startScreenCaptureByScreenRect(
	const Rectangle& screenRect,
	const Rectangle& regionRect,
	const ScreenCaptureParameters& captureParams)
{
	return m_rtcEngine->startScreenCaptureByScreenRect(screenRect, regionRect, captureParams);
}
#endif

int AgoraRtcEngine::startScreenCaptureByWindowId(
	view_t windowId,
	const Rectangle& regionRect,
	const ScreenCaptureParameters& captureParams)
{
	return m_rtcEngine->startScreenCaptureByWindowId(windowId, regionRect, captureParams);
}

int AgoraRtcEngine::setScreenCaptureContentHint(VideoContentHint contentHint)
{
	return m_rtcEngine->setScreenCaptureContentHint(contentHint);
}

int AgoraRtcEngine::updateScreenCaptureParameters(const ScreenCaptureParameters& captureParams)
{
	return m_rtcEngine->updateScreenCaptureParameters(captureParams);
}

int AgoraRtcEngine::updateScreenCaptureRegion(const Rectangle& regionRect)
{
	return m_rtcEngine->updateScreenCaptureRegion(regionRect);
}

int AgoraRtcEngine::stopScreenCapture()
{
	return m_rtcEngine->stopScreenCapture();
}

#endif

int AgoraRtcEngine::getCallId(agora::util::AString& callId)
{
	return m_rtcEngine->getCallId(callId);
}

int AgoraRtcEngine::rate(const char* callId, int rating, const char* description)
{
	return m_rtcEngine->rate(callId, rating, description);
}

int AgoraRtcEngine::complain(const char* callId, const char* description)
{
	return m_rtcEngine->complain(callId, description);
}

const char* AgoraRtcEngine::getVersion(int* build)
{
	return m_rtcEngine->getVersion(build);
}

int AgoraRtcEngine::enableLastmileTest()
{
	return m_rtcEngine->enableLastmileTest();
}

int AgoraRtcEngine::disableLastmileTest()
{
	return m_rtcEngine->disableLastmileTest();
}

int AgoraRtcEngine::startLastmileProbeTest(const LastmileProbeConfig& config)
{
	return m_rtcEngine->startLastmileProbeTest(config);
}

int AgoraRtcEngine::stopLastmileProbeTest()
{
	return m_rtcEngine->stopLastmileProbeTest();
}

const char* AgoraRtcEngine::getErrorDescription(int code)
{
	return m_rtcEngine->getErrorDescription(code);
}

int AgoraRtcEngine::setEncryptionSecret(const char* secret)
{
	return m_rtcEngine->setEncryptionSecret(secret);
}

int AgoraRtcEngine::setEncryptionMode(const char* encryptionMode)
{
	return m_rtcEngine->setEncryptionMode(encryptionMode);
}

int AgoraRtcEngine::registerPacketObserver(IPacketObserver* observer)
{
	return m_rtcEngine->registerPacketObserver(observer);
}

int AgoraRtcEngine::createDataStream(int* streamId, bool reliable, bool ordered)
{
	return m_rtcEngine->createDataStream(streamId, reliable, ordered);
}

int AgoraRtcEngine::sendStreamMessage(int streamId, const char* data, size_t length)
{
	return m_rtcEngine->sendStreamMessage(streamId, data, length);
}

int AgoraRtcEngine::addPublishStreamUrl(const char* url, bool transcodingEnabled)
{
	return m_rtcEngine->addPublishStreamUrl(url, transcodingEnabled);
}

int AgoraRtcEngine::removePublishStreamUrl(const char* url)
{
	return m_rtcEngine->removePublishStreamUrl(url);
}

int AgoraRtcEngine::setLiveTranscoding(const LiveTranscoding& transcoding)
{
	return m_rtcEngine->setLiveTranscoding(transcoding);
}

int AgoraRtcEngine::addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options)
{
	return m_rtcEngine->addVideoWatermark(watermarkUrl, options);
}

int AgoraRtcEngine::clearVideoWatermarks()
{
	return m_rtcEngine->clearVideoWatermarks();
}

int AgoraRtcEngine::setBeautyEffectOptions(bool enabled, BeautyOptions options)
{
	return m_rtcEngine->setBeautyEffectOptions(enabled, options);
}

int AgoraRtcEngine::addInjectStreamUrl(const char* url, const InjectStreamConfig& config)
{
	return m_rtcEngine->addInjectStreamUrl(url, config);
}

int AgoraRtcEngine::startChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration)
{
	return m_rtcEngine->startChannelMediaRelay(configuration);
}

int AgoraRtcEngine::updateChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration)
{
	return m_rtcEngine->updateChannelMediaRelay(configuration);
}

int AgoraRtcEngine::stopChannelMediaRelay()
{
	return m_rtcEngine->stopChannelMediaRelay();
}

int AgoraRtcEngine::removeInjectStreamUrl(const char* url)
{
	return m_rtcEngine->removeInjectStreamUrl(url);
}

bool AgoraRtcEngine::registerEventHandler(IRtcEngineEventHandler* eventHandler)
{
	return m_rtcEngine->registerEventHandler(eventHandler);
}

bool AgoraRtcEngine::unregisterEventHandler(IRtcEngineEventHandler* eventHandler)
{
	return m_rtcEngine->unregisterEventHandler(eventHandler);
}

agora::rtc::CONNECTION_STATE_TYPE AgoraRtcEngine::getConnectionState()
{
	return m_rtcEngine->getConnectionState();
}

int AgoraRtcEngine::registerMediaMetadataObserver(IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type)
{
	return m_rtcEngine->registerMediaMetadataObserver(observer, type);
}

}
}
}