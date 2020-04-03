//  Copyright (c) 2019 Agora.io. All rights reserved.

#if PLATFORM_WINDOWS

#include "AgoraPublisherEngine.h"

#include <utility>

#include "AgoraLiveEngine.h"

namespace agora
{
namespace rtc
{
namespace ue4
{

AgoraPublisherEngine::AgoraPublisherEngine(const AgoraPublisherEngine& other)
	: m_publisherEngine(other.m_publisherEngine)
{
}
AgoraPublisherEngine::AgoraPublisherEngine(AgoraPublisherEngine&& other) noexcept
	: m_publisherEngine(std::exchange(other.m_publisherEngine, nullptr))
{
}
AgoraPublisherEngine& AgoraPublisherEngine::operator=(const AgoraPublisherEngine& other)
{
	return *this = AgoraPublisherEngine(other);
}
AgoraPublisherEngine& AgoraPublisherEngine::operator=(AgoraPublisherEngine&& other) noexcept
{
	std::swap(m_publisherEngine, other.m_publisherEngine);
	return *this;
}

AgoraPublisherEngine::AgoraPublisherEngine(agora::rtc::IPublisherEngine* publisherEngine)
	: m_publisherEngine(publisherEngine)
{
}

AgoraPublisherEngine::~AgoraPublisherEngine()
{
	release();
}

AgoraPublisherEngine* AgoraPublisherEngine::createAgoraLivePublisherEngine()
{
	agora::rtc::IPublisherEngine* agoraEngine = ::createAgoraLivePublisherEngine();
	if (!agoraEngine)
	{
		return nullptr;
	}
	return new AgoraPublisherEngine(agoraEngine);
}

int AgoraPublisherEngine::initialize(AgoraLiveEngine* engine)
{
	return m_publisherEngine->initialize(engine->m_liveEngine);
}

int AgoraPublisherEngine::setEventHandler(agora::rtc::IPublisherEventHandler* eventHandler)
{
	return m_publisherEngine->setEventHandler(eventHandler);
}

int AgoraPublisherEngine::publish()
{
	return m_publisherEngine->publish();
}

int AgoraPublisherEngine::unpublish()
{
	return m_publisherEngine->unpublish();
}

int AgoraPublisherEngine::addStreamUrl(const char* url, bool transcodingEnabled)
{
	return m_publisherEngine->addStreamUrl(url, transcodingEnabled);
}

int AgoraPublisherEngine::removeStreamUrl(const char* url)
{
	return m_publisherEngine->removeStreamUrl(url);
}

int AgoraPublisherEngine::setMediaType(agora::rtc::MEDIA_TYPE type)
{
	return m_publisherEngine->setMediaType(type);
}

int AgoraPublisherEngine::setLiveTranscoding(const agora::rtc::LiveTranscoding& transcoding)
{
	return m_publisherEngine->setLiveTranscoding(transcoding);
}

int AgoraPublisherEngine::addInjectStreamUrl(const char* url, const agora::rtc::InjectStreamConfig& config)
{
	return m_publisherEngine->addInjectStreamUrl(url, config);
}

int AgoraPublisherEngine::removeInjectStreamUrl(const char* url)
{
	return m_publisherEngine->removeInjectStreamUrl(url);
}

int AgoraPublisherEngine::setVideoProfile(agora::rtc::VIDEO_PROFILE_TYPE profile)
{
	return m_publisherEngine->setVideoProfile(profile);
}

void AgoraPublisherEngine::release()
{
	return m_publisherEngine->release();
}

}
}
}
#endif
