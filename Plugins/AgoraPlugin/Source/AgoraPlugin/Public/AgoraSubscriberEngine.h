//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#if PLATFORM_WINDOWS

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/IAgoraLiveEngine.h>
#include <Agora/IAgoraLiveSubscriber.h>
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

namespace agora
{
namespace rtc
{
namespace ue4
{

class AgoraLiveEngine;
/**
 * Wrapper around agora::rtc::ISubscriberEngine
 */
class AGORAPLUGIN_API AgoraSubscriberEngine
{
public:
	AgoraSubscriberEngine() = delete;
	AgoraSubscriberEngine(const AgoraSubscriberEngine& other);
	AgoraSubscriberEngine(AgoraSubscriberEngine&& other) noexcept;
	AgoraSubscriberEngine& operator=(const AgoraSubscriberEngine& other);
	AgoraSubscriberEngine& operator=(AgoraSubscriberEngine&& other) noexcept;
	~AgoraSubscriberEngine();

public:
   /**
   * @brief          Creates the SubscriberEngine object
   * @return
   *                 -  Success: Returns a pointer to the SubscriberEngine object
   *                 -  Failure: Returns nullptr.
   */
	static AgoraSubscriberEngine* createAgoraLiveSubscriberEngine();

public:
   /**
   * @brief          Initializes the SubscriberEngine object.
   * @param          engine
   *                 Pointer to LiveEngine
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int initialize(AgoraLiveEngine* engine);

   /**
   * @brief          Sets the event handler of the subscriber engine.
   * @param          eventHandler
   *                 Event handler.
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setEventHandler(agora::rtc::ISubscriberEventHandler* eventHandler);

   /**
   * @brief          Subscribes to a remote user.
   * @param          uid 
   *                 UID of the remote user.
   * @param          type 
   *                 Media type.
   * @param          view 
   *                 Reserved view.
   * @param          mode 
   *                 Render mode.
   * @param          streamType 
                     Remote user stream type.
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int subscribe(
		agora::rtc::uid_t uid,
		agora::rtc::MEDIA_TYPE type,
		agora::rtc::view_t view,
		agora::rtc::RENDER_MODE_TYPE mode,
		agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType);

   /**
   * @brief          Unsubscribes a user.
	* @param          uid 
   *                 UID of the remote user.
	*/
	int unsubscribe(agora::rtc::uid_t uid);

   /** 
   * @brief          Determines whether the release will be called synchronously or asynchronously
   * @param          sync
   *                 - true: Synchronous call
   *                 - false: Asynchronous call
   * @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	void setSyncForRelease(bool sync);
private:
   /**
   * @brief Releases all SubscriberEngine resources.
   */
	void release(bool sync = false);

private:
	AgoraSubscriberEngine(agora::rtc::ISubscriberEngine* subscriberEngine);

private:
	agora::rtc::ISubscriberEngine* m_subscriberEngine = nullptr;
	bool m_sync = false;
};

}
}
}
#endif
