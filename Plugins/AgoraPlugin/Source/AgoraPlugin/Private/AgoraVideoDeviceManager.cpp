//  Copyright (c) 2019 Agora.io. All rights reserved.

#include "AgoraVideoDeviceManager.h"

#include "AgoraRtcEngine.h"

namespace agora
{
namespace rtc
{
namespace ue4
{

VideoDeviceCollection::VideoDeviceCollection(agora::rtc::IVideoDeviceCollection* collection)
	: m_videoDeviceCollection(collection)
{
}
VideoDeviceCollection::VideoDeviceCollection(const VideoDeviceCollection& other)
	: m_videoDeviceCollection(other.m_videoDeviceCollection)
{
}
VideoDeviceCollection::VideoDeviceCollection(VideoDeviceCollection&& other) noexcept
	: m_videoDeviceCollection(std::exchange(other.m_videoDeviceCollection, nullptr))
{
}
VideoDeviceCollection& VideoDeviceCollection::operator=(const VideoDeviceCollection& other)
{
	return *this = VideoDeviceCollection(other);
}
VideoDeviceCollection& VideoDeviceCollection::operator=(VideoDeviceCollection&& other) noexcept
{
	std::swap(m_videoDeviceCollection, other.m_videoDeviceCollection);
	return *this;
}

VideoDeviceCollection::~VideoDeviceCollection()
{
	release();
}

int VideoDeviceCollection::getCount()
{
	if (!m_videoDeviceCollection)
	{
		return 0;
	}
	return m_videoDeviceCollection->getCount();
}

int VideoDeviceCollection::getDevice(
	int index,
	char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH],
	char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	if (!m_videoDeviceCollection)
	{
		return -1;
	}
	return m_videoDeviceCollection->getDevice(index, deviceName, deviceId);
}

int VideoDeviceCollection::setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	if (!m_videoDeviceCollection)
	{
		return -1;
	}
	return m_videoDeviceCollection->setDevice(deviceId);
}

void VideoDeviceCollection::release()
{
	if (m_videoDeviceCollection)
	{
		m_videoDeviceCollection->release();
		m_videoDeviceCollection = nullptr;
	}
}

//=========================================================

AgoraVideoDeviceManager* AgoraVideoDeviceManager::Create(AgoraRtcEngine* RtcEngine)
{
	auto VideoDeviceManager = new AgoraVideoDeviceManager();
	bool res = VideoDeviceManager->queryInterface(RtcEngine);
	if (!res)
	{
		return nullptr;
	}
	return VideoDeviceManager;
}

bool AgoraVideoDeviceManager::queryInterface(AgoraRtcEngine* engine)
{
	return m_videoDeviceManager.queryInterface(engine->m_rtcEngine, agora::AGORA_IID_VIDEO_DEVICE_MANAGER);
}

VideoDeviceCollection* AgoraVideoDeviceManager::enumerateVideoDevices()
{
	auto collection = m_videoDeviceManager->enumerateVideoDevices();
	if (!collection)
	{
		return nullptr;
	}
	return new VideoDeviceCollection(collection);
}

int AgoraVideoDeviceManager::startDeviceTest(agora::rtc::view_t hwnd)
{
	return m_videoDeviceManager->startDeviceTest(hwnd);
}

int AgoraVideoDeviceManager::stopDeviceTest()
{
	return m_videoDeviceManager->stopDeviceTest();
}

int AgoraVideoDeviceManager::setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	return m_videoDeviceManager->setDevice(deviceId);
}

int AgoraVideoDeviceManager::getDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	return m_videoDeviceManager->getDevice(deviceId);
}

void AgoraVideoDeviceManager::release()
{
	m_videoDeviceManager->release();
}

}
}
}