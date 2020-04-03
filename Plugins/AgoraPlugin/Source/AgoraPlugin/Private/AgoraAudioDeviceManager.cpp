//  Copyright (c) 2019 Agora.io. All rights reserved.

#include "AgoraAudioDeviceManager.h"

#include "AgoraRtcEngine.h"

namespace agora
{
namespace rtc
{
namespace ue4
{

AudioDeviceCollection::AudioDeviceCollection(agora::rtc::IAudioDeviceCollection* collection)
	: m_audioDeviceCollection(collection)
{
}

AudioDeviceCollection::AudioDeviceCollection(const AudioDeviceCollection& other)
	: m_audioDeviceCollection(other.m_audioDeviceCollection)
{
}
AudioDeviceCollection::AudioDeviceCollection(AudioDeviceCollection&& other) noexcept
	: m_audioDeviceCollection(std::exchange(other.m_audioDeviceCollection, nullptr))
{
}
AudioDeviceCollection& AudioDeviceCollection::operator=(const AudioDeviceCollection& other)
{
	return *this = AudioDeviceCollection(other);
}
AudioDeviceCollection& AudioDeviceCollection::operator=(AudioDeviceCollection&& other) noexcept
{
	std::swap(m_audioDeviceCollection, other.m_audioDeviceCollection);
	return *this;
}

AudioDeviceCollection::~AudioDeviceCollection()
{
	release();
}

int AudioDeviceCollection::getCount()
{
	if (!m_audioDeviceCollection)
	{
		return 0;
	}
	return m_audioDeviceCollection->getCount();
}

int AudioDeviceCollection::getDevice(
	int index,
	char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH],
	char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	if (!m_audioDeviceCollection)
	{
		return -1;
	}
	return m_audioDeviceCollection->getDevice(index, deviceName, deviceId);
}

int AudioDeviceCollection::setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	if (!m_audioDeviceCollection)
	{
		return -1;
	}
	return m_audioDeviceCollection->setDevice(deviceId);
}

int AudioDeviceCollection::setApplicationVolume(int volume)
{
	if (!m_audioDeviceCollection)
	{
		return -1;
	}
	return m_audioDeviceCollection->setApplicationVolume(volume);
}

int AudioDeviceCollection::getApplicationVolume(int& volume)
{
	if (!m_audioDeviceCollection)
	{
		return -1;
	}
	return m_audioDeviceCollection->getApplicationVolume(volume);
}

int AudioDeviceCollection::setApplicationMute(bool mute)
{
	if (!m_audioDeviceCollection)
	{
		return -1;
	}
	return m_audioDeviceCollection->setApplicationMute(mute);
}

int AudioDeviceCollection::isApplicationMute(bool& mute)
{
	if (!m_audioDeviceCollection)
	{
		return -1;
	}
	return m_audioDeviceCollection->isApplicationMute(mute);
}

void AudioDeviceCollection::release()
{
	if (m_audioDeviceCollection)
	{
		m_audioDeviceCollection->release();
		m_audioDeviceCollection = nullptr;
	}
}

//============================================================


AgoraAudioDeviceManager* AgoraAudioDeviceManager::Create(AgoraRtcEngine* RtcEngine)
{
	auto AudioDeviceManager = new AgoraAudioDeviceManager();
	bool res = AudioDeviceManager->queryInterface(RtcEngine);
	if (!res)
	{
		return nullptr;
	}
	return AudioDeviceManager;
}

bool AgoraAudioDeviceManager::queryInterface(AgoraRtcEngine* engine)
{
	return m_audioDeviceManager.queryInterface(engine->m_rtcEngine, agora::AGORA_IID_AUDIO_DEVICE_MANAGER);
}

AudioDeviceCollection* AgoraAudioDeviceManager::enumeratePlaybackDevices()
{
	auto collection = m_audioDeviceManager->enumeratePlaybackDevices();
	if (!collection)
	{
		return nullptr;
	}
	return new AudioDeviceCollection(collection);
}

AudioDeviceCollection* AgoraAudioDeviceManager::enumerateRecordingDevices()
{
	auto collection = m_audioDeviceManager->enumerateRecordingDevices();
	if (!collection)
	{
		return nullptr;
	}
	return new AudioDeviceCollection(collection);
}

int AgoraAudioDeviceManager::setPlaybackDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	return m_audioDeviceManager->setPlaybackDevice(deviceId);
}

int AgoraAudioDeviceManager::setRecordingDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	return m_audioDeviceManager->setRecordingDevice(deviceId);
}

int AgoraAudioDeviceManager::startPlaybackDeviceTest(const char* testAudioFilePath)
{
	return m_audioDeviceManager->startPlaybackDeviceTest(testAudioFilePath);
}

int AgoraAudioDeviceManager::stopPlaybackDeviceTest()
{
	return m_audioDeviceManager->stopPlaybackDeviceTest();
}

int AgoraAudioDeviceManager::setPlaybackDeviceVolume(int volume)
{
	return m_audioDeviceManager->setPlaybackDeviceVolume(volume);
}

int AgoraAudioDeviceManager::getPlaybackDeviceVolume(int* volume)
{
	return m_audioDeviceManager->getPlaybackDeviceVolume(volume);
}

int AgoraAudioDeviceManager::setRecordingDeviceVolume(int volume)
{
	return m_audioDeviceManager->setRecordingDeviceVolume(volume);
}

int AgoraAudioDeviceManager::getRecordingDeviceVolume(int* volume)
{
	return m_audioDeviceManager->getRecordingDeviceVolume(volume);
}

int AgoraAudioDeviceManager::setPlaybackDeviceMute(bool mute)
{
	return m_audioDeviceManager->setPlaybackDeviceMute(mute);
}

int AgoraAudioDeviceManager::getPlaybackDeviceMute(bool* mute)
{
	return m_audioDeviceManager->getPlaybackDeviceMute(mute);
}

int AgoraAudioDeviceManager::setRecordingDeviceMute(bool mute)
{
	return m_audioDeviceManager->setRecordingDeviceMute(mute);
}

int AgoraAudioDeviceManager::getRecordingDeviceMute(bool* mute)
{
	return m_audioDeviceManager->getRecordingDeviceMute(mute);
}

int AgoraAudioDeviceManager::startRecordingDeviceTest(int indicationInterval)
{
	return m_audioDeviceManager->startRecordingDeviceTest(indicationInterval);
}

int AgoraAudioDeviceManager::stopRecordingDeviceTest()
{
	return m_audioDeviceManager->stopRecordingDeviceTest();
}

int AgoraAudioDeviceManager::getPlaybackDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	return m_audioDeviceManager->getPlaybackDevice(deviceId);
}

int AgoraAudioDeviceManager::getPlaybackDeviceInfo(
	char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH],
	char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	return m_audioDeviceManager->getPlaybackDeviceInfo(deviceId, deviceName);
}

int AgoraAudioDeviceManager::getRecordingDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	return m_audioDeviceManager->getRecordingDevice(deviceId);
}

int AgoraAudioDeviceManager::getRecordingDeviceInfo(
	char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH],
	char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH])
{
	return m_audioDeviceManager->getRecordingDeviceInfo(deviceId, deviceName);
}

int AgoraAudioDeviceManager::startAudioDeviceLoopbackTest(int indicationInterval)
{
	return m_audioDeviceManager->startAudioDeviceLoopbackTest(indicationInterval);
}

int AgoraAudioDeviceManager::stopAudioDeviceLoopbackTest()
{
	return m_audioDeviceManager->stopAudioDeviceLoopbackTest();
}

void AgoraAudioDeviceManager::release()
{
	return m_audioDeviceManager->release();
}

}
}
}