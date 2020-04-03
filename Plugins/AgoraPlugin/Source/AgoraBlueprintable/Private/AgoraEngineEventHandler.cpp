// Copyright (c) 2019 Agora.io. All rights reserved.


#include "AgoraEngineEventHandler.h"
#include "AgoraBlueprintable.h"
#include "Agora.h"

namespace agora
{
namespace blueprints
{
RtcEngineEventHandler::RtcEngineEventHandler( UIAgora* outer )
   : m_eventHandler( outer )
{
   if( !m_eventHandler )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "RtcEngineEventHandler::RtcEngineEventHandler - Outer class is nullptr" ) );
   }
}

RtcEngineEventHandler::~RtcEngineEventHandler()
{
   m_functionQueue.clear();
   m_eventHandler = nullptr;
}

void RtcEngineEventHandler::OnTick()
{
   //todo: use "if" instead of "while"?
   while( !m_functionQueue.empty() )
   {
      std::function<void()> curFunction;
      if( m_functionQueue.tryPop( curFunction ) )
      {
         curFunction();
      }
   }
}

void RtcEngineEventHandler::onWarning( int Warn, const char * Msg )
{
   FString ConvertedMsg( ANSI_TO_TCHAR( Msg ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnWarningDelegate.Broadcast( Warn, ConvertedMsg );
   } );
}

void RtcEngineEventHandler::onError( int Err, const char* Msg )
{
   FString ConvertedMsg( ANSI_TO_TCHAR( Msg ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnErrorDelegate.Broadcast( Err, ConvertedMsg );
   } );
}

void RtcEngineEventHandler::onJoinChannelSuccess( const char* Channel, agora::rtc::uid_t Uid, int Elapsed )
{
   FString ConvertedChannel( ANSI_TO_TCHAR( Channel ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnJoinChannelSuccessDelegate.Broadcast( ConvertedChannel, Uid, Elapsed );
   } );
}

void RtcEngineEventHandler::onRejoinChannelSuccess( const char* Channel, agora::rtc::uid_t Uid, int Elapsed )
{
   FString ConvertedChannel( ANSI_TO_TCHAR( Channel ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRejoinChannelSuccessDelegate.Broadcast( ConvertedChannel, Uid, Elapsed );
   } );
}

void RtcEngineEventHandler::onLeaveChannel( const agora::rtc::RtcStats& Stats )
{
   FRtcStats ConvertedStats = FRtcStats( Stats );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLeaveChannelDelegate.Broadcast( ConvertedStats );
   } );
}

void RtcEngineEventHandler::onClientRoleChanged( agora::rtc::CLIENT_ROLE_TYPE OldRole, agora::rtc::CLIENT_ROLE_TYPE NewRole )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnClientRoleChangedDelegate.Broadcast( convert( OldRole ), convert( NewRole ) );
   } );
}

void RtcEngineEventHandler::onUserJoined( agora::rtc::uid_t Uid, int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnUserJoinedDelegate.Broadcast( Uid, Elapsed );
   } );
}

void RtcEngineEventHandler::onUserOffline( agora::rtc::uid_t Uid, agora::rtc::USER_OFFLINE_REASON_TYPE Reason )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnUserOfflineDelegate.Broadcast( Uid, convert( Reason ) );
   } );
}

void RtcEngineEventHandler::onLastmileQuality( int Quality )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLastmileQualityDelegate.Broadcast( Quality );
   } );
}

void RtcEngineEventHandler::onLastmileProbeResult( const agora::rtc::LastmileProbeResult& Result )
{
   FLastmileProbeResult ConvertedResult = convert( Result );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLastmileProbeResultDelegate.Broadcast( ConvertedResult );
   } );
}

void RtcEngineEventHandler::onConnectionInterrupted()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnConnectionInterruptedDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onConnectionLost()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnConnectionLostDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onConnectionBanned()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnConnectionBannedDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onApiCallExecuted( int Err, const char* Api, const char* Result )
{
   FString ConvertedApi( ANSI_TO_TCHAR( Api ) );
   FString ConvertedResult( ANSI_TO_TCHAR( Result ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnApiCallExecutedDelegate.Broadcast( Err, ConvertedApi, ConvertedResult );
   } );
}

void RtcEngineEventHandler::onRequestToken()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRequestTokenDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onTokenPrivilegeWillExpire( const char* Token )
{
   FString ConvertedToken( ANSI_TO_TCHAR( Token ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnTokenPrivilegeWillExpireDelegate.Broadcast( ConvertedToken );
   } );
}

void RtcEngineEventHandler::onAudioQuality( agora::rtc::uid_t Uid, int Quality, unsigned short Delay, unsigned short Lost )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnAudioQualityDelegate.Broadcast( Uid, Quality, Delay, Lost );
   } );
}

void RtcEngineEventHandler::onRtcStats( const agora::rtc::RtcStats& Stats )
{
   FRtcStats ConvertedStats = FRtcStats( Stats );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRtcStatsDelegate.Broadcast( ConvertedStats );
   } );
}

void RtcEngineEventHandler::onNetworkQuality( agora::rtc::uid_t Uid, int TxQuality, int RxQuality )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnNetworkQualityDelegate.Broadcast( Uid, TxQuality, RxQuality );
   } );
}

void RtcEngineEventHandler::onLocalVideoStats( const agora::rtc::LocalVideoStats& Stats )
{
   FLocalVideoStats ConvertedStats = convert( Stats );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLocalVideoStatsDelegate.Broadcast( ConvertedStats );
   } );
}

void RtcEngineEventHandler::onRemoteVideoStats( const agora::rtc::RemoteVideoStats& Stats )
{
   FRemoteVideoStats ConvertedStats = convert( Stats );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteVideoStatsDelegate.Broadcast( ConvertedStats );
   } );
}

void RtcEngineEventHandler::onLocalAudioStats( const agora::rtc::LocalAudioStats& Stats )
{
   FLocalAudioStats ConvertedStats = convert( Stats );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLocalAudioStatsDelegate.Broadcast( ConvertedStats );
   } );
}

void RtcEngineEventHandler::onRemoteAudioStats( const agora::rtc::RemoteAudioStats& Stats )
{
   FRemoteAudioStats ConvertedStats = convert( Stats );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteAudioStatsDelegate.Broadcast( ConvertedStats );
   } );
}

void RtcEngineEventHandler::onLocalAudioStateChanged( agora::rtc::LOCAL_AUDIO_STREAM_STATE State, agora::rtc::LOCAL_AUDIO_STREAM_ERROR Error )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLocalAudioStateChangedDelegate.Broadcast( convert( State ), convert( Error ) );
   } );
}

void RtcEngineEventHandler::onRemoteAudioStateChanged( agora::rtc::uid_t Uid, agora::rtc::REMOTE_AUDIO_STATE State, agora::rtc::REMOTE_AUDIO_STATE_REASON Reason, int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteAudioStateChangedDelegate.Broadcast( Uid, convert( State ), convert( Reason ), Elapsed );
   } );
}

void RtcEngineEventHandler::onAudioVolumeIndication( const agora::rtc::AudioVolumeInfo* speakers,
                              unsigned int SpeakerNumber, 
                              int TotalVolume )
{
   TArray<FAudioVolumeInfo> Speakers;
   for( unsigned int i( 0 ); i < SpeakerNumber; i++ )
   {
      Speakers.Add( convert( speakers[i] ) );
   }
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnAudioVolumeIndicationDelegate.Broadcast( Speakers, TotalVolume );
   } );
}

void RtcEngineEventHandler::onActiveSpeaker( agora::rtc::uid_t Uid )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnActiveSpeakerDelegate.Broadcast( Uid );
   } );
}

void RtcEngineEventHandler::onVideoStopped()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnVideoStoppedDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onFirstLocalVideoFrame( int Width, int Height, int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnFirstLocalVideoFrameDelegate.Broadcast( Width, Height, Elapsed );
   } );
}

void RtcEngineEventHandler::onFirstRemoteVideoDecoded( agora::rtc::uid_t Uid, int Width, int Height, int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnFirstRemoteVideoDecodedDelegate.Broadcast( Uid, Width, Height, Elapsed );
   } );
}

void RtcEngineEventHandler::onFirstRemoteVideoFrame( agora::rtc::uid_t Uid, int Width, int Height, int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnFirstRemoteVideoFrameDelegate.Broadcast( Uid, Width, Height, Elapsed );
   } );
}

void RtcEngineEventHandler::onUserMuteAudio( agora::rtc::uid_t Uid, bool Muted )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnUserMuteAudioDelegate.Broadcast( Uid, Muted );
   } );
}

void RtcEngineEventHandler::onUserMuteVideo( agora::rtc::uid_t Uid, bool Muted )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnUserMuteVideoDelegate.Broadcast( Uid, Muted );
   } );
}

void RtcEngineEventHandler::onUserEnableVideo( agora::rtc::uid_t Uid, bool Enabled )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnUserEnableVideoDelegate.Broadcast( Uid, Enabled );
   } );
}

void RtcEngineEventHandler::onAudioDeviceStateChanged( const char * DeviceId, int DeviceType, int DeviceState )
{
   FString ConvertedDeviceId( ANSI_TO_TCHAR( DeviceId ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnAudioDeviceStateChangedDelegate.Broadcast( ConvertedDeviceId, DeviceType, DeviceState );
   } );
}

void RtcEngineEventHandler::onAudioDeviceVolumeChanged( agora::rtc::MEDIA_DEVICE_TYPE DeviceType, int Volume, bool Muted )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnAudioDeviceVolumeChangedDelegate.Broadcast( convert( DeviceType ), Volume, Muted );
   } );
}

void RtcEngineEventHandler::onCameraReady()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnCameraReadyDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onCameraFocusAreaChanged( int X, int Y, int Width, int Height )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnCameraFocusAreaChangedDelegate.Broadcast( X, Y, Width, Height );
   } );
}

void RtcEngineEventHandler::onCameraExposureAreaChanged( int X, int Y, int Width, int Height )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnCameraExposureAreaChangedDelegate.Broadcast( X, Y, Width, Height );
   } );
}

void RtcEngineEventHandler::onAudioMixingFinished()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnAudioMixingFinishedDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onAudioMixingStateChanged( agora::rtc::AUDIO_MIXING_STATE_TYPE State, agora::rtc::AUDIO_MIXING_ERROR_TYPE ErrorCode )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnAudioMixingStateChangedDelegate.Broadcast( convert( State ), convert( ErrorCode ) );
   } );
}

void RtcEngineEventHandler::onRemoteAudioMixingBegin()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteAudioMixingBeginDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onRemoteAudioMixingEnd()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteAudioMixingEndDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onAudioEffectFinished( int SoundId )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnAudioEffectFinishedDelegate.Broadcast( SoundId );
   } );
}

void RtcEngineEventHandler::onFirstRemoteAudioDecoded( agora::rtc::uid_t Uid, int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnFirstRemoteAudioDecodedDelegate.Broadcast( Uid, Elapsed );
   } );
}

void RtcEngineEventHandler::onVideoDeviceStateChanged( const char * DeviceId, int DeviceType, int DeviceState )
{
   FString ConvertedDeviceId( ANSI_TO_TCHAR( DeviceId ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnVideoDeviceStateChangedDelegate.Broadcast( ConvertedDeviceId, DeviceType, DeviceState );
   } );
}

void RtcEngineEventHandler::onLocalVideoStateChanged( agora::rtc::LOCAL_VIDEO_STREAM_STATE LocalVideoState, agora::rtc::LOCAL_VIDEO_STREAM_ERROR Error )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLocalVideoStateChangedDelegate.Broadcast( convert( LocalVideoState ), convert( Error ) );
   } );
}

void RtcEngineEventHandler::onVideoSizeChanged( agora::rtc::uid_t Uid, int Width, int Height, int Rotation )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnVideoSizeChangedDelegate.Broadcast( Uid, Width, Height, Rotation );
   } );
}

void RtcEngineEventHandler::onRemoteVideoStateChanged( agora::rtc::uid_t Uid, agora::rtc::REMOTE_VIDEO_STATE State, agora::rtc::REMOTE_VIDEO_STATE_REASON Reason, int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteVideoStateChangedDelegate.Broadcast( Uid, convert( State ), convert( Reason ), Elapsed );
   } );
}

void RtcEngineEventHandler::onUserEnableLocalVideo( agora::rtc::uid_t Uid, bool Enabled )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnUserEnableLocalVideoDelegate.Broadcast( Uid, Enabled );
   } );
}

void RtcEngineEventHandler::onStreamMessage( agora::rtc::uid_t Uid, int StreamId, const char * Data, size_t Length )
{
   FString ConvertedData( ANSI_TO_TCHAR( Data ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnStreamMessageDelegate.Broadcast( Uid, StreamId, ConvertedData, Length );
   } );
}

void RtcEngineEventHandler::onStreamMessageError( agora::rtc::uid_t Uid, int StreamId, int Code, int Missed, int Cached )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnStreamMessageErrorDelegate.Broadcast( Uid, StreamId, Code, Missed, Cached );
   } );
}

void RtcEngineEventHandler::onMediaEngineLoadSuccess()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnMediaEngineLoadSuccessDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onMediaEngineStartCallSuccess()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnMediaEngineStartCallSuccessDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onChannelMediaRelayStateChanged( agora::rtc::CHANNEL_MEDIA_RELAY_STATE State, agora::rtc::CHANNEL_MEDIA_RELAY_ERROR Code )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnChannelMediaRelayStateChangedDelegate.Broadcast( convert( State ), convert( Code ) );
   } );
}

void RtcEngineEventHandler::onChannelMediaRelayEvent( agora::rtc::CHANNEL_MEDIA_RELAY_EVENT Code )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnChannelMediaRelayEventDelegate.Broadcast( convert( Code ) );
   } );
}

void RtcEngineEventHandler::onFirstLocalAudioFrame( int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnFirstLocalAudioFrameDelegate.Broadcast( Elapsed );
   } );
}

void RtcEngineEventHandler::onFirstRemoteAudioFrame( agora::rtc::uid_t Uid, int Elapsed )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnFirstRemoteAudioFrameDelegate.Broadcast( Uid, Elapsed );
   } );
}

void RtcEngineEventHandler::onRtmpStreamingStateChanged( const char * Url, agora::rtc::RTMP_STREAM_PUBLISH_STATE State, agora::rtc::RTMP_STREAM_PUBLISH_ERROR ErrCode )
{
   FString ConvertedUrl( ANSI_TO_TCHAR( Url ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRtmpStreamingStateChangedDelegate.Broadcast( ConvertedUrl, convert( State ), convert( ErrCode ) );
   } );
}

void RtcEngineEventHandler::onStreamPublished( const char * Url, int Error )
{
   FString ConvertedUrl( ANSI_TO_TCHAR( Url ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnStreamPublishedDelegate.Broadcast( ConvertedUrl, Error );
   } );
}

void RtcEngineEventHandler::onStreamUnpublished( const char * Url )
{
   FString ConvertedUrl( ANSI_TO_TCHAR( Url ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnStreamUnpublishedDelegate.Broadcast( ConvertedUrl );
   } );
}

void RtcEngineEventHandler::onTranscodingUpdated()
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnTranscodingUpdatedDelegate.Broadcast();
   } );
}

void RtcEngineEventHandler::onStreamInjectedStatus( const char * Url, agora::rtc::uid_t Uid, int Status )
{
   FString ConvertedUrl( ANSI_TO_TCHAR( Url ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnStreamInjectedStatusDelegate.Broadcast( ConvertedUrl, Uid, Status );
   } );
}

void RtcEngineEventHandler::onAudioRouteChanged( agora::rtc::AUDIO_ROUTE_TYPE Routing )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnAudioRouteChangedDelegate.Broadcast( convert( Routing ) );
   } );
}

void RtcEngineEventHandler::onLocalPublishFallbackToAudioOnly( bool IsFallbackOrRecover )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLocalPublishFallbackToAudioOnlyDelegate.Broadcast( IsFallbackOrRecover );
   } );
}

void RtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly( agora::rtc::uid_t Uid, bool IsFallbackOrRecover )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteSubscribeFallbackToAudioOnlyDelegate.Broadcast( Uid, IsFallbackOrRecover );
   } );
}

void RtcEngineEventHandler::onRemoteAudioTransportStats(
   agora::rtc::uid_t Uid, unsigned short Delay, unsigned short Lost,
   unsigned short RxKBitRate )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteAudioTransportStatsDelegate.Broadcast( Uid, Delay, Lost, RxKBitRate );
   } );
}

void RtcEngineEventHandler::onRemoteVideoTransportStats(
   agora::rtc::uid_t Uid, unsigned short Delay, unsigned short Lost,
   unsigned short RxKBitRate )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnRemoteVideoTransportStatsDelegate.Broadcast( Uid, Delay, Lost, RxKBitRate );
   } );
}

void RtcEngineEventHandler::onMicrophoneEnabled( bool Enabled )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnMicrophoneEnabledDelegate.Broadcast( Enabled );
   } );
}

void RtcEngineEventHandler::onConnectionStateChanged( agora::rtc::CONNECTION_STATE_TYPE State, agora::rtc::CONNECTION_CHANGED_REASON_TYPE Reason )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnConnectionStateChangedDelegate.Broadcast( convert( State ), convert( Reason ) );
   } );
}

void RtcEngineEventHandler::onNetworkTypeChanged( agora::rtc::NETWORK_TYPE Type )
{
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnNetworkTypeChangedDelegate.Broadcast( convert( Type ) );
   } );
}

void RtcEngineEventHandler::onLocalUserRegistered( agora::rtc::uid_t Uid, const char* userAccount )
{
   FString UserAccount( ANSI_TO_TCHAR( userAccount ) );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnLocalUserRegisteredDelegate.Broadcast( Uid, UserAccount );
   } );
}

void RtcEngineEventHandler::onUserInfoUpdated( agora::rtc::uid_t Uid, const agora::rtc::UserInfo& info )
{
   FAgoraUserInfo Info = convert( info );
   m_functionQueue.push( [=]()
   {
      if( m_eventHandler )
         m_eventHandler->OnUserInfoUpdatedDelegate.Broadcast( Uid, Info );
   } );
}

}
}