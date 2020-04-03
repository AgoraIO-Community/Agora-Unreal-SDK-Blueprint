//  Copyright (c) 2019 Agora.io. All rights reserved.

#if PLATFORM_WINDOWS

#include "AgoraLiveEngine.h"

#include <utility>

#include "AgoraRtcEngine.h"

namespace agora
{
namespace rtc
{
namespace ue4
{

AgoraLiveEngine::AgoraLiveEngine(const AgoraLiveEngine& other)
	: m_liveEngine(other.m_liveEngine)
{
}
AgoraLiveEngine::AgoraLiveEngine(AgoraLiveEngine&& other) noexcept
	: m_liveEngine(std::exchange(other.m_liveEngine, nullptr))
{
}
AgoraLiveEngine& AgoraLiveEngine::operator=(const AgoraLiveEngine& other)
{
	return *this = AgoraLiveEngine(other);
}
AgoraLiveEngine& AgoraLiveEngine::operator=(AgoraLiveEngine&& other) noexcept
{
	std::swap(m_liveEngine, other.m_liveEngine);
	return *this;
}

AgoraLiveEngine::AgoraLiveEngine(agora::rtc::ILiveEngine* liveEngine)
	: m_liveEngine(liveEngine)
{
}

AgoraLiveEngine::~AgoraLiveEngine()
{
	release(m_sync);
}

AgoraLiveEngine* AgoraLiveEngine::createAgoraLiveEngine()
{
	agora::rtc::ILiveEngine* agoraEngine = ::createAgoraLiveEngine();
	if (!agoraEngine)
	{
		return nullptr;
	}
	return new AgoraLiveEngine(agoraEngine);
}

int AgoraLiveEngine::initialize(const char* appId)
{
	return m_liveEngine->initialize(appId);
}

const char* AgoraLiveEngine::getVersion(int* build)
{
	return m_liveEngine->getVersion(build);
}

AgoraRtcEngine* AgoraLiveEngine::getRtcEngine()
{
	auto rtcEngine = m_liveEngine->getRtcEngine();
	return new AgoraRtcEngine(rtcEngine);
}

int AgoraLiveEngine::setEventHandler(agora::rtc::ILiveEngineEventHandler* eventHandler)
{
	return m_liveEngine->setEventHandler(eventHandler);
}

int AgoraLiveEngine::joinChannel(const char* token, const char* channelId, agora::rtc::LiveChannelConfig* config, agora::rtc::uid_t uid)
{
	return m_liveEngine->joinChannel(token, channelId, config, uid);
}

int AgoraLiveEngine::leaveChannel()
{
	return m_liveEngine->leaveChannel();
}

int AgoraLiveEngine::renewToken(const char* token)
{
	return m_liveEngine->renewToken(token);
}

int AgoraLiveEngine::startPreview(agora::rtc::view_t view, agora::rtc::RENDER_MODE_TYPE type)
{
	return m_liveEngine->startPreview(view, type);
}

int AgoraLiveEngine::stopPreview()
{
	return m_liveEngine->stopPreview();
}

void AgoraLiveEngine::setSyncForRelease(bool sync)
{
	m_sync = sync;
}

void AgoraLiveEngine::release(bool sync)
{
	return m_liveEngine->release(sync);
}

}
}
}
#endif
