//  Copyright (c) 2019 Agora.io. All rights reserved.

#include "AgoraMediaEngine.h"

#include <utility>

#include "AgoraRtcEngine.h"

namespace agora
{
namespace media
{
namespace ue4
{

AgoraMediaEngine* AgoraMediaEngine::Create(agora::rtc::ue4::AgoraRtcEngine* RtcEngine)
{
	auto MediaEngine = new AgoraMediaEngine();
	bool res = MediaEngine->queryInterface(RtcEngine);
	if (!res)
	{
		return nullptr;
	}
	return MediaEngine;
}

bool AgoraMediaEngine::queryInterface(agora::rtc::ue4::AgoraRtcEngine* AgoraEngine)
{
	return m_mediaEngine.queryInterface(AgoraEngine->m_rtcEngine, agora::AGORA_IID_MEDIA_ENGINE);
}

void AgoraMediaEngine::release()
{
	m_mediaEngine->release();
}

int AgoraMediaEngine::registerAudioFrameObserver(agora::media::IAudioFrameObserver* observer)
{
	return m_mediaEngine->registerAudioFrameObserver(observer);
}

int AgoraMediaEngine::registerVideoFrameObserver(agora::media::IVideoFrameObserver* observer)
{
	return m_mediaEngine->registerVideoFrameObserver(observer);
}

int AgoraMediaEngine::pushAudioFrame(agora::media::IAudioFrameObserver::AudioFrame* frame)
{
	return m_mediaEngine->pushAudioFrame(frame);
}

int AgoraMediaEngine::pullAudioFrame(agora::media::IAudioFrameObserver::AudioFrame* frame)
{
	return m_mediaEngine->pullAudioFrame(frame);
}

int AgoraMediaEngine::setExternalVideoSource(bool enable, bool useTexture)
{
	return m_mediaEngine->setExternalVideoSource(enable, useTexture);
}

int AgoraMediaEngine::pushVideoFrame(agora::media::ExternalVideoFrame* frame)
{
	return m_mediaEngine->pushVideoFrame(frame);
}

}
}
}