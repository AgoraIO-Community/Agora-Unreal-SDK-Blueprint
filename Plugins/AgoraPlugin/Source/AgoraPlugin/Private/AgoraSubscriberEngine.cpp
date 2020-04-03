//  Copyright (c) 2019 Agora.io. All rights reserved.

#if PLATFORM_WINDOWS

#include "AgoraSubscriberEngine.h"

#include <utility>

#include "AgoraLiveEngine.h"

namespace agora
{
namespace rtc
{
namespace ue4
{

AgoraSubscriberEngine::AgoraSubscriberEngine(const AgoraSubscriberEngine& other)
	: m_subscriberEngine(other.m_subscriberEngine)
{
}
AgoraSubscriberEngine::AgoraSubscriberEngine(AgoraSubscriberEngine&& other) noexcept
	: m_subscriberEngine(std::exchange(other.m_subscriberEngine, nullptr))
{
}
AgoraSubscriberEngine& AgoraSubscriberEngine::operator=(const AgoraSubscriberEngine& other)
{
	return *this = AgoraSubscriberEngine(other);
}
AgoraSubscriberEngine& AgoraSubscriberEngine::operator=(AgoraSubscriberEngine&& other) noexcept
{
	std::swap(m_subscriberEngine, other.m_subscriberEngine);
	return *this;
}

AgoraSubscriberEngine::AgoraSubscriberEngine(agora::rtc::ISubscriberEngine* subscriberEngine)
	: m_subscriberEngine(subscriberEngine)
{
}

AgoraSubscriberEngine::~AgoraSubscriberEngine()
{
	release(m_sync);
}

AgoraSubscriberEngine* AgoraSubscriberEngine::createAgoraLiveSubscriberEngine()
{
	agora::rtc::ISubscriberEngine* agoraEngine = ::createAgoraLiveSubscriberEngine();
	if (!agoraEngine)
	{
		return nullptr;
	}
	return new AgoraSubscriberEngine(agoraEngine);
}

void AgoraSubscriberEngine::release(bool sync)
{
	return m_subscriberEngine->release(sync);
}

int AgoraSubscriberEngine::initialize(AgoraLiveEngine* engine)
{
	return m_subscriberEngine->initialize(engine->m_liveEngine);
}

int AgoraSubscriberEngine::setEventHandler(agora::rtc::ISubscriberEventHandler* eventHandler)
{
	return m_subscriberEngine->setEventHandler(eventHandler);
}

int AgoraSubscriberEngine::subscribe(
	agora::rtc::uid_t uid,
	agora::rtc::MEDIA_TYPE type,
	agora::rtc::view_t view,
	agora::rtc::RENDER_MODE_TYPE mode,
	agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType)
{
	return m_subscriberEngine->subscribe(uid, type, view, mode, streamType);
}

int AgoraSubscriberEngine::unsubscribe(agora::rtc::uid_t uid)
{
	return m_subscriberEngine->unsubscribe(uid);
}

void AgoraSubscriberEngine::setSyncForRelease(bool sync)
{
	m_sync = sync;
}

}
}
}
#endif
