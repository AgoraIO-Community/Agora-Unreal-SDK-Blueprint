//  Copyright (c) 2019 Agora.io. All rights reserved.

#if PLATFORM_WINDOWS

#include "AgoraService.h"

#include <utility>

namespace agora
{
namespace rtc
{
namespace ue4
{

AgoraService::AgoraService(const AgoraService& other)
	: m_agoraService(other.m_agoraService)
{
}
AgoraService::AgoraService(AgoraService&& other) noexcept
	: m_agoraService(std::exchange(other.m_agoraService, nullptr))
{
}
AgoraService& AgoraService::operator=(const AgoraService& other)
{
	return *this = AgoraService(other);
}
AgoraService& AgoraService::operator=(AgoraService&& other) noexcept
{
	std::swap(m_agoraService, other.m_agoraService);
	return *this;
}

AgoraService::AgoraService(agora::base::IAgoraService* agoraService)
	: m_agoraService(agoraService)
{
}

AgoraService::~AgoraService()
{
	release();
}

AgoraService* AgoraService::createAgoraService()
{
	agora::base::IAgoraService* agoraService = ::createAgoraService();
	if (!agoraService)
	{
		return nullptr;
	}
	return new AgoraService(agoraService);
}

const char* AgoraService::getAgoraSdkErrorDescription(int err)
{
	return ::getAgoraSdkErrorDescription(err);
}

int AgoraService::setAgoraSdkExternalSymbolLoader(void* (*func)(const char* symname))
{
	return ::setAgoraSdkExternalSymbolLoader(func);
}

int AgoraService::initialize(const agora::base::AgoraServiceContext& context)
{
	return m_agoraService->initialize(context);
}

const char* AgoraService::getVersion(int* build)
{
	return m_agoraService->getVersion(build);
}

//virtual rtm::IRtmService* createRtmService() = 0;

void AgoraService::release()
{
	return m_agoraService->release();
}

}
}
}
#endif
