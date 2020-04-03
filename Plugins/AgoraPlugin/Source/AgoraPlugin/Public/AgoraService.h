//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#if PLATFORM_WINDOWS

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/IAgoraService.h>
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif


namespace agora
{
namespace rtc
{
namespace ue4
{

/**
 * Wrapper around agora::base::IAgoraService
 */
class AGORAPLUGIN_API AgoraService
{
public:
	AgoraService() = delete;
	AgoraService(const AgoraService& other);
	AgoraService(AgoraService&& other) noexcept;
	AgoraService& operator=(const AgoraService& other);
	AgoraService& operator=(AgoraService&& other) noexcept;
	~AgoraService();

public:

   /**
   * @brief          Creates the AgoraService object
   * @return
   *                 -  Success: Returns a pointer to the AgoraService object
   *                 -  Failure: Returns nullptr.
   */
	static AgoraService* createAgoraService();

	//TODO: duplicate getVersion?
	//const char* getAgoraSdkVersion(int* build);

   /**
   * @brief          Retrieves the warning or error description.
   * @param          err
   *                 Error code
   * @return         Error description
   */
	static const char* getAgoraSdkErrorDescription(int err);

   /**
   * @brief          Sets function, which loads external symbol
   * @param          func(symname)
   *                 Function(Symbol name)
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	static int setAgoraSdkExternalSymbolLoader(void* (*func)(const char* symname));

   /**
   * @brief          Initializes the Agora SDK service.
   * @brief          Ensure that you call the createAgoraRtcEngine and initialize methods before calling any other API.
   * @param          context
   *                 A const reference to AgoraServiceContext
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int initialize(const agora::base::AgoraServiceContext& context);

   /**
   * @brief          Retrieves the SDK version number.
   * @brief          Ensure that you call the createAgoraRtcEngine and initialize methods before calling any other API.
   * @param          build
   *                 Pointer to the build number.
   * @return         The version of the current SDK in the string format. For example, 2.3.1.
   */
	const char* getVersion(int* build);

	//TODO: where is IRtmService?
	//virtual rtm::IRtmService* createRtmService() = 0;

private:
   /**
   * @brief Releases all AgoraService resources.
   */
	void release();

private:
	AgoraService(agora::base::IAgoraService* agoraService);

private:
	agora::base::IAgoraService* m_agoraService;
};

}
}
}
#endif
