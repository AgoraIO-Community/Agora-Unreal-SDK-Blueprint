//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#if PLATFORM_WINDOWS

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/IAgoraLiveEngine.h>
#include <Agora/IAgoraLivePublisher.h>
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
 * Wrapper around agora::rtc::IPublisherEngine
 */
class AGORAPLUGIN_API AgoraPublisherEngine
{
public:
	AgoraPublisherEngine() = delete;
	AgoraPublisherEngine(const AgoraPublisherEngine& other);
	AgoraPublisherEngine(AgoraPublisherEngine&& other) noexcept;
	AgoraPublisherEngine& operator=(const AgoraPublisherEngine& other);
	AgoraPublisherEngine& operator=(AgoraPublisherEngine&& other) noexcept;
	~AgoraPublisherEngine();

public:
   /**
   * @brief          Creates the PublicsherEngine object
   * @return
   *                 -  Success: Returns a pointer to the SubscriberEngine object
   *                 -  Failure: Returns nullptr.
   */
	static AgoraPublisherEngine* createAgoraLivePublisherEngine();

public:
   /**
   * @brief          Initializes the PublisherEngine object.
   * @param          engine
   *                 Pointer to LiveEngine
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int initialize(AgoraLiveEngine* engine);

   /**
   * @brief          Sets the event handler of the publisher engine.
   * @param          eventHandler
   *                 Event handler.
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setEventHandler(agora::rtc::IPublisherEventHandler* eventHandler);

   /**
   * @brief          Publishes a stream.
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int publish();

   /**
   * @brief          Unpublishes a stream.
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int unpublish();

   /**
   * @brief          Adds a publish stream URL.
   * @param          url 
   *                 Publish stream URL.
   * @param          transcodingEnabled
   *                 Whether the transcoding is enabled: true/false.
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int addStreamUrl(const char* url, bool transcodingEnabled);

   /**
   * @brief          Removes a publish stream URL.
   * @param          url 
   *                 Publish stream URL to remove.
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int removeStreamUrl(const char* url);

   /**
   * @brief          Sets the publish media type.
   * @param          type
   *                 The media type: \ref MEDIA_TYPE
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setMediaType(agora::rtc::MEDIA_TYPE type);

   /**
   * @brief          Sets the live transcoding.
   * @param          transcoding
   *                 The transcoding option: \ref LiveTranscoding
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setLiveTranscoding(const agora::rtc::LiveTranscoding& transcoding);

   /**
   * @brief          Adds the inject stream URL.
   * @param          url 
   *                 The added injected stream URL.
   * @param          config 
   *                 The inject stream configuration: InjectStreamConfig
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int addInjectStreamUrl(const char* url, const agora::rtc::InjectStreamConfig& config);

   /**
   * @brief          Removes the injected stream URL.
   * @param          url 
   *                 The injected stream URL to remove.
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int removeInjectStreamUrl(const char* url);

   /**
   * @brief          Sets the video profile.
   * @param          profile 
   *                 The video profile: VIDEO_PROFILE_TYPE
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setVideoProfile(agora::rtc::VIDEO_PROFILE_TYPE profile);

private:
   /**
   * @brief Releases all PublisherEngine resources.
   */
	void release();

private:
	AgoraPublisherEngine(agora::rtc::IPublisherEngine* publisherEngine);

private:
	agora::rtc::IPublisherEngine* m_publisherEngine = nullptr;
};

}
}
}
#endif
