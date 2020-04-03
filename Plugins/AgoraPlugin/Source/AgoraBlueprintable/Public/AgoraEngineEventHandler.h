// Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "concurrent_queue.h"
#include <functional>

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/IAgoraRtcEngine.h>
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UECompatibility.h"

class UIAgora;

namespace agora
{
namespace blueprints
{
/**
Retrieves Agora callbacks.
*/
class RtcEngineEventHandler : public agora::rtc::IRtcEngineEventHandler
{
public:
   RtcEngineEventHandler( UIAgora* outer );
   ~RtcEngineEventHandler();

   /** All UIAgora callbacks are called here. This method is used to syncronize Agora and UE threads.*/
   void OnTick();

   /** @ref UIAgora::OnWarningDelegate "OnWarning"*/
   virtual void onWarning( int Warn, const char* Msg ) override;
   
   /** @ref UIAgora::OnErrorDelegate "OnError" */
   virtual void onError( int Err, const char* Msg );
   
   /** @ref UIAgora::OnJoinChannelSuccessDelegate "OnJoinChannelSuccess" */
   virtual void onJoinChannelSuccess( const char* Channel, agora::rtc::uid_t Uid, int Elapsed );
   
   /** @ref UIAgora::OnRejoinChannelSuccessDelegate "OnRejoinChannelSuccess" */
   virtual void onRejoinChannelSuccess( const char* Channel, agora::rtc::uid_t Uid, int Elapsed );
   
   /** @ref UIAgora::OnLeaveChannelDelegate "OnLeaveChannel" */
   virtual void onLeaveChannel( const agora::rtc::RtcStats& Stats ) override;
   
   /** @ref UIAgora::OnClientRoleChangedDelegate "OnClientRoleChanged" */
   virtual void onClientRoleChanged( agora::rtc::CLIENT_ROLE_TYPE OldRole, agora::rtc::CLIENT_ROLE_TYPE NewRole ) override;
   
   /** @ref UIAgora::OnUserJoinedDelegate "OnUserJoined" */
   virtual void onUserJoined( agora::rtc::uid_t Uid, int Elapsed ) override;
   
   /** @ref UIAgora::OnUserOfflineDelegate "OnUserOffline" */
   virtual void onUserOffline( agora::rtc::uid_t Uid, agora::rtc::USER_OFFLINE_REASON_TYPE Reason ) override;
   
   /** @ref UIAgora::OnLastmileQualityDelegate "OnLastmileQuality" */
   virtual void onLastmileQuality( int Quality ) override;
   
   /** @ref UIAgora::OnLastmileProbeResultDelegate "OnLastmileProbeResult" */
   virtual void onLastmileProbeResult( const agora::rtc::LastmileProbeResult& Result ) override;
   
   /** @ref UIAgora::OnConnectionInterruptedDelegate "OnConnectionInterrupted" */
   virtual void onConnectionInterrupted() override;
   
   /** @ref UIAgora::OnConnectionLostDelegate "OnConnectionLost" */
   virtual void onConnectionLost() override;
   
   /** @ref UIAgora::OnConnectionBannedDelegate "OnConnectionBanned" */
   virtual void onConnectionBanned() override;
   
   /** @ref UIAgora::OnApiCallExecutedDelegate "OnApiCallExecuted" */
   virtual void onApiCallExecuted( int Err, const char* Api, const char* Result ) override;
   
   /** @ref UIAgora::OnRequestTokenDelegate "OnRequestToken" */
   virtual void onRequestToken() override;
   
   /** @ref UIAgora::OnTokenPrivilegeWillExpireDelegate "OnTokenPrivilegeWillExpire" */
   virtual void onTokenPrivilegeWillExpire( const char* Token ) override;
   
   /** @ref UIAgora::OnAudioQualityDelegate "OnAudioQuality" */
   virtual void onAudioQuality( agora::rtc::uid_t Uid, int Quality, unsigned short Delay, unsigned short Lost ) override;
   
   /** @ref UIAgora::OnRtcStatsDelegate "OnRtcStats" */
   virtual void onRtcStats( const agora::rtc::RtcStats& Stats ) override;
   
   /** @ref UIAgora::OnNetworkQualityDelegate "OnNetworkQuality" */
   virtual void onNetworkQuality( agora::rtc::uid_t Uid, int TxQuality, int RxQuality ) override;
   
   /** @ref UIAgora::OnLocalVideoStatsDelegate "OnLocalVideoStats" */
   virtual void onLocalVideoStats( const agora::rtc::LocalVideoStats& Stats ) override;
   
   /** @ref UIAgora::OnRemoteVideoStatsDelegate "OnRemoteVideoStats" */
   virtual void onRemoteVideoStats( const agora::rtc::RemoteVideoStats& Stats ) override;
   
   /** @ref UIAgora::OnLocalAudioStatsDelegate "OnLocalAudioStats" */
   virtual void onLocalAudioStats( const agora::rtc::LocalAudioStats& Stats ) override;
   
   /** @ref UIAgora::OnRemoteAudioStatsDelegate "OnRemoteAudioStats" */
   virtual void onRemoteAudioStats( const agora::rtc::RemoteAudioStats& Stats ) override;
   
   /** @ref UIAgora::OnLocalAudioStateChangedDelegate "OnLocalAudioStateChanged" */
   virtual void onLocalAudioStateChanged( agora::rtc::LOCAL_AUDIO_STREAM_STATE State, agora::rtc::LOCAL_AUDIO_STREAM_ERROR Error ) override;
   
   /** @ref UIAgora::OnRemoteAudioStateChangedDelegate "OnRemoteAudioStateChanged" */
   virtual void onRemoteAudioStateChanged( agora::rtc::uid_t Uid, agora::rtc::REMOTE_AUDIO_STATE State, agora::rtc::REMOTE_AUDIO_STATE_REASON Reason, int Elapsed ) override;
   
   /** @ref UIAgora::OnAudioVolumeIndicationDelegate "OnAudioVolumeIndication" */
   virtual void onAudioVolumeIndication( const agora::rtc::AudioVolumeInfo* Speakers, unsigned int SpeakerNumber, int TotalVolume ) override;
   
   /** @ref UIAgora::OnActiveSpeakerDelegate "OnActiveSpeaker" */
   virtual void onActiveSpeaker( agora::rtc::uid_t Uid ) override;
   
   /** @ref UIAgora::OnVideoStoppedDelegate "OnVideoStopped" */
   virtual void onVideoStopped() override;
   
   /** @ref UIAgora::OnFirstLocalVideoFrameDelegate "OnFirstLocalVideoFrame" */
   virtual void onFirstLocalVideoFrame( int Width, int Height, int Elapsed ) override;
   
   /** @ref UIAgora::OnFirstRemoteVideoDecodedDelegate "OnFirstRemoteVideoDecoded" */
   virtual void onFirstRemoteVideoDecoded( agora::rtc::uid_t Uid, int Width, int Height, int Elapsed ) override;
   
   /** @ref UIAgora::OnFirstRemoteVideoFrameDelegate "OnFirstRemoteVideoFrame" */
   virtual void onFirstRemoteVideoFrame( agora::rtc::uid_t Uid, int Width, int Height, int Elapsed ) override;
   
   /** @ref UIAgora::OnUserMuteAudioDelegate "OnUserMuteAudio" */
   virtual void onUserMuteAudio( agora::rtc::uid_t Uid, bool Muted ) override;
   
   /** @ref UIAgora::OnUserMuteVideoDelegate "OnUserMuteVideo" */
   virtual void onUserMuteVideo( agora::rtc::uid_t Uid, bool Muted ) override;
   
   /** @ref UIAgora::OnUserEnableVideoDelegate "OnUserEnableVideo" */
   virtual void onUserEnableVideo( agora::rtc::uid_t Uid, bool Enabled ) override;
   
   /** @ref UIAgora::OnAudioDeviceStateChangedDelegate "OnAudioDeviceStateChanged" */
   virtual void onAudioDeviceStateChanged( const char* DeviceId, int DeviceType, int DeviceState ) override;
   
   /** @ref UIAgora::OnAudioDeviceVolumeChangedDelegate "OnAudioDeviceVolumeChanged" */
   virtual void onAudioDeviceVolumeChanged( agora::rtc::MEDIA_DEVICE_TYPE DeviceType, int Volume, bool Muted ) override;
   
   /** @ref UIAgora::OnCameraReadyDelegate "OnCameraReady" */
   virtual void onCameraReady() override;
   
   /** @ref UIAgora::OnCameraFocusAreaChangedDelegate "OnCameraFocusAreaChanged" */
   virtual void onCameraFocusAreaChanged( int X, int Y, int Width, int Height ) override;
   
   /** @ref UIAgora::OnCameraExposureAreaChangedDelegate "OnCameraExposureAreaChanged" */
   virtual void onCameraExposureAreaChanged( int X, int Y, int Width, int Height ) override;
   
   /** @ref UIAgora::OnAudioMixingFinishedDelegate "OnAudioMixingFinished" */
   virtual void onAudioMixingFinished() override;
   
   /** @ref UIAgora::OnAudioMixingStateChangedDelegate "OnAudioMixingStateChanged" */
   virtual void onAudioMixingStateChanged( agora::rtc::AUDIO_MIXING_STATE_TYPE State, agora::rtc::AUDIO_MIXING_ERROR_TYPE ErrorCode ) override;
   
   /** @ref UIAgora::OnRemoteAudioMixingBeginDelegate "OnRemoteAudioMixingBegin" */
   virtual void onRemoteAudioMixingBegin() override;
   
   /** @ref UIAgora::OnRemoteAudioMixingEndDelegate "OnRemoteAudioMixingEnd" */
   virtual void onRemoteAudioMixingEnd() override;
   
   /** @ref UIAgora::OnAudioEffectFinishedDelegate "OnAudioEffectFinished" */
   virtual void onAudioEffectFinished( int SoundId ) override;
   
   /** @ref UIAgora::OnFirstRemoteAudioDecodedDelegate "OnFirstRemoteAudioDecoded" */
   virtual void onFirstRemoteAudioDecoded( agora::rtc::uid_t Uid, int Elapsed ) override;
   
   /** @ref UIAgora::OnVideoDeviceStateChangedDelegate "OnVideoDeviceStateChanged" */
   virtual void onVideoDeviceStateChanged( const char* DeviceId, int DeviceType, int DeviceState ) override;
   
   /** @ref UIAgora::OnLocalVideoStateChangedDelegate "OnLocalVideoStateChanged" */
   virtual void onLocalVideoStateChanged( agora::rtc::LOCAL_VIDEO_STREAM_STATE LocalVideoState, agora::rtc::LOCAL_VIDEO_STREAM_ERROR Error ) override;
   
   /** @ref UIAgora::OnVideoSizeChangedDelegate "OnVideoSizeChanged" */
   virtual void onVideoSizeChanged( agora::rtc::uid_t Uid, int Width, int Height, int Rotation ) override;
   
   /** @ref UIAgora::OnRemoteVideoStateChangedDelegate "OnRemoteVideoStateChanged" */
   virtual void onRemoteVideoStateChanged( agora::rtc::uid_t Uid, agora::rtc::REMOTE_VIDEO_STATE State, agora::rtc::REMOTE_VIDEO_STATE_REASON Reason, int Elapsed ) override;
   
   /** @ref UIAgora::OnUserEnableLocalVideoDelegate "OnUserEnableLocalVideo" */
   virtual void onUserEnableLocalVideo( agora::rtc::uid_t Uid, bool Enabled ) override;
   
   /** @ref UIAgora::OnStreamMessageDelegate "OnStreamMessage" */
   virtual void onStreamMessage( agora::rtc::uid_t Uid, int StreamId, const char* Data, size_t Length ) override;
   
   /** @ref UIAgora::OnStreamMessageErrorDelegate "OnStreamMessageError" */
   virtual void onStreamMessageError( agora::rtc::uid_t Uid, int StreamId, int Code, int Missed, int Cached ) override;
   
   /** @ref UIAgora::OnMediaEngineLoadSuccessDelegate "OnMediaEngineLoadSuccess" */
   virtual void onMediaEngineLoadSuccess() override;
   
   /** @ref UIAgora::OnMediaEngineStartCallSuccessDelegate "OnMediaEngineStartCallSuccess" */
   virtual void onMediaEngineStartCallSuccess() override;
   
   /** @ref UIAgora::OnChannelMediaRelayStateChangedDelegate "OnChannelMediaRelayStateChanged" */
   virtual void onChannelMediaRelayStateChanged( agora::rtc::CHANNEL_MEDIA_RELAY_STATE State, agora::rtc::CHANNEL_MEDIA_RELAY_ERROR Code ) override;
   
   /** @ref UIAgora::OnChannelMediaRelayEventDelegate "OnChannelMediaRelayEvent" */
   virtual void onChannelMediaRelayEvent( agora::rtc::CHANNEL_MEDIA_RELAY_EVENT Code ) override;
   
   /** @ref UIAgora::OnFirstLocalAudioFrameDelegate "OnFirstLocalAudioFrame" */
   virtual void onFirstLocalAudioFrame( int Elapsed ) override;
   
   /** @ref UIAgora::OnFirstRemoteAudioFrameDelegate "OnFirstRemoteAudioFrame" */
   virtual void onFirstRemoteAudioFrame( agora::rtc::uid_t Uid, int Elapsed ) override;
   
   /** @ref UIAgora::OnRtmpStreamingStateChangedDelegate "OnRtmpStreamingStateChanged" */
   virtual void onRtmpStreamingStateChanged( const char *Url, agora::rtc::RTMP_STREAM_PUBLISH_STATE State, agora::rtc::RTMP_STREAM_PUBLISH_ERROR ErrCode ) override;
   
   /** @ref UIAgora::OnStreamPublishedDelegate "OnStreamPublished" */
   virtual void onStreamPublished( const char *Url, int Error ) override;
   
   /** @ref UIAgora::OnStreamUnpublishedDelegate "OnStreamUnpublished" */
   virtual void onStreamUnpublished( const char *Url ) override;
   
   /** @ref UIAgora::OnTranscodingUpdatedDelegate "OnTranscodingUpdated" */
   virtual void onTranscodingUpdated() override;
   
   /** @ref UIAgora::OnStreamInjectedStatusDelegate "OnStreamInjectedStatus" */
   virtual void onStreamInjectedStatus( const char* Url, agora::rtc::uid_t Uid, int Status ) override;
   
   /** @ref UIAgora::OnAudioRouteChangedDelegate "OnAudioRouteChanged" */
   virtual void onAudioRouteChanged( agora::rtc::AUDIO_ROUTE_TYPE Routing ) override;

   
   /** @ref UIAgora::OnLocalPublishFallbackToAudioOnlyDelegate "OnLocalPublishFallbackToAudioOnly" */
   virtual void onLocalPublishFallbackToAudioOnly( bool isFallbackOrRecover ) override;
   
   /** @ref UIAgora::OnRemoteSubscribeFallbackToAudioOnlyDelegate "OnRemoteSubscribeFallbackToAudioOnly" */
   virtual void onRemoteSubscribeFallbackToAudioOnly( agora::rtc::uid_t uid, bool isFallbackOrRecover ) override;
   
   /** @ref UIAgora::OnRemoteAudioTransportStatsDelegate "OnRemoteAudioTransportStats" */
   virtual void onRemoteAudioTransportStats( agora::rtc::uid_t Uid, unsigned short Delay, unsigned short Lost, unsigned short RxKBitRate ) override;
  
   /** @ref UIAgora::OnRemoteVideoTransportStatsDelegate "OnRemoteVideoTransportStats:" */
   virtual void onRemoteVideoTransportStats( agora::rtc::uid_t Uid, unsigned short Delay, unsigned short Lost,unsigned short RxKBitRate ) override;
   
   /** @ref UIAgora::OnMicrophoneEnabledDelegate "OnMicrophoneEnabled" */
   virtual void onMicrophoneEnabled( bool Enabled ) override;
   
   /** @ref UIAgora::OnConnectionStateChangedDelegate "OnConnectionStateChanged" */
   virtual void onConnectionStateChanged( agora::rtc::CONNECTION_STATE_TYPE State, agora::rtc::CONNECTION_CHANGED_REASON_TYPE Reason ) override;
   
   /** @ref UIAgora::OnNetworkTypeChangedDelegate "OnNetworkTypeChanged" */
   virtual void onNetworkTypeChanged( agora::rtc::NETWORK_TYPE Type ) override;
   
   /** @ref UIAgora::OnLocalUserRegisteredDelegate "OnLocalUserRegistered" */
   virtual void onLocalUserRegistered( agora::rtc::uid_t Uid, const char* UserAccount ) override;
   
   /** @ref UIAgora::OnUserInfoUpdatedDelegate "OnUserInfoUpdated" */
   virtual void onUserInfoUpdated( agora::rtc::uid_t Uid, const agora::rtc::UserInfo& Info ) override;

private:
   UIAgora* m_eventHandler = nullptr;
   /** Events queue*/
   ConcurrentQueue<std::function<void()>> m_functionQueue;
};

}
}