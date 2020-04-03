// Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include <memory>

#include "AgoraEngineEventHandler.h"
#include "AudioFrameObserver.h"
#include "VideoFrameObserver.h"
#include "AgoraAudioManager.h"
#include "AgoraVideoManager.h"
#include "MediaDevice.h"
#include "UECompatibility.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "Agora.generated.h"

namespace agora {
namespace blueprints {
class IVideoFrameObserver;
}
namespace rtc {
namespace ue4 {
class AgoraRtcEngine;
}
}
namespace media {
class IVideoFrameObserver;
namespace ue4 {
class AgoraMediaEngine;
}
}
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FWarning, int, ErrorCode, FString, ErrorMessage );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FError, int, Err, const FString&, Msg );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FJoinChannelSuccess, const FString&, Channel, int64, Uid, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FRejoinChannelSuccess, const FString&, Channel, int64, Uid, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLeaveChannel, const FRtcStats&, Stats );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FClientRoleChanged, ECLIENT_ROLE_TYPE, OldRole, ECLIENT_ROLE_TYPE, NewRole );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUserJoined, int64, Uid, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUserOffline, int64, Uid, EUSER_OFFLINE_REASON_TYPE, Reason );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLastmileQuality, int, Quality );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLastmileProbeResultDelegate, const FLastmileProbeResult&, Result );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FConnectionInterrupted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FConnectionLost );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FConnectionBanned );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FApiCallExecuted, int, Err, const FString&, Api, const FString&, Result );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FRequestToken );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FTokenPrivilegeWillExpire, const FString&, Token );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FAudioQuality, int64, Uid, int, Quality, int, Delay, int, Lost );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FRtcStatsDelegate, const FRtcStats&, Stats );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FNetworkQuality, int64, Uid, int, TxQuality, int, RxQuality );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLocalVideoStatsDelegate, const FLocalVideoStats&, Stats );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FRemoteVideoStatsDelegate, const FRemoteVideoStats&, Stats );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLocalAudioStatsDelegate, const FLocalAudioStats&, Stats );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FRemoteAudioStatsDelegate, const FRemoteAudioStats&, Stats );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FLocalAudioStateChanged, ELOCAL_AUDIO_STREAM_STATE, State, ELOCAL_AUDIO_STREAM_ERROR, Error );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FRemoteAudioStateChanged, int64, Uid, EREMOTE_AUDIO_STATE, State, EREMOTE_AUDIO_STATE_REASON, Reason, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FAudioVolumeIndication, const TArray<FAudioVolumeInfo>&, speakers, int, totalVolume );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FActiveSpeaker, int64, Uid );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FVideoStopped );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FFirstLocalVideoFrame, int, Width, int, Height, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FFirstRemoteVideoDecoded, int64, Uid, int, Width, int, Height, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FFirstRemoteVideoFrame, int64, Uid, int, Width, int, Height, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUserMuteAudio, int64, Uid, bool, Muted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUserMuteVideo, int64, Uid, bool, Muted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUserEnableVideo, int64, Uid, bool, Enabled );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FAudioDeviceStateChanged, const FString&, DeviceId, int, DeviceType, int, DeviceState );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FAudioDeviceVolumeChanged, EMEDIA_DEVICE_TYPE, DeviceType, int, Volume, bool, Muted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FCameraReady );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FCameraFocusAreaChanged, int, X, int, Y, int, Width, int, Height );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FCameraExposureAreaChanged, int, X, int, Y, int, Width, int, Height );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FAudioMixingFinished );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FAudioMixingStateChanged, EAUDIO_MIXING_STATE_TYPE, State, EAUDIO_MIXING_ERROR_TYPE, ErrorCode );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FRemoteAudioMixingBegin );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FRemoteAudioMixingEnd );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAudioEffectFinished, int, SoundId );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FFirstRemoteAudioDecoded, int64, Uid, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FVideoDeviceStateChanged, const FString&, DeviceId, int, DeviceType, int, DeviceState );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FLocalVideoStateChanged, ELOCAL_VIDEO_STREAM_STATE, LocalVideoState, ELOCAL_VIDEO_STREAM_ERROR, Error );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FVideoSizeChanged, int64, Uid, int, Width, int, Height, int, Rotation );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FRemoteVideoStateChanged, int64, Uid, EREMOTE_VIDEO_STATE, State, EREMOTE_VIDEO_STATE_REASON, Reason, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUserEnableLocalVideo, int64, Uid, bool, Enabled );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FStreamMessage, int64, Uid, int, StreamId, const FString&, Data, int64, Length );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams( FStreamMessageError, int64, Uid, int, StreamId, int, Code, int, Missed, int, Cached );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FMediaEngineLoadSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FMediaEngineStartCallSuccess );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FChannelMediaRelayStateChanged, ECHANNEL_MEDIA_RELAY_STATE, State, ECHANNEL_MEDIA_RELAY_ERROR, Code );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FChannelMediaRelayEvent, ECHANNEL_MEDIA_RELAY_EVENT, Code );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFirstLocalAudioFrame, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FFirstRemoteAudioFrame, int64, Uid, int, Elapsed );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FRtmpStreamingStateChanged, const FString&, Url, ERTMP_STREAM_PUBLISH_STATE, State, ERTMP_STREAM_PUBLISH_ERROR, ErrCode );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FStreamPublished, const FString&, Url, int, Error );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FStreamUnpublished, const FString&, Url );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FTranscodingUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FStreamInjectedStatus, const FString&, Url, int64, Uid, int, Status );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAudioRouteChanged, EAUDIO_ROUTE_TYPE, Routing );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLocalPublishFallbackToAudioOnly, bool, IsFallbackOrRecover );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FRemoteSubscribeFallbackToAudioOnly, int64, Uid, bool, IsFallbackOrRecover );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FRemoteAudioTransportStats, int64, Uid, int, Delay, int, Lost, int, RxKBitRate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FRemoteVideoTransportStats, int64, Uid, int, Delay, int, Lost, int, RxKBitRate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FMicrophoneEnabled, bool, Enabled );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FConnectionStateChanged, ECONNECTION_STATE_TYPE, State, ECONNECTION_CHANGED_REASON_TYPE, Reason );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FNetworkTypeChanged, ENETWORK_TYPE, Type );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FLocalUserRegistered, int64, Uid, FString, UserAccount );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FUserInfoUpdated, int64, Uid, FAgoraUserInfo, Info );

/**
Allows to use Agora functions in blueprints.

This class includes AgoraRtcEngineEventHandler callbacks, rtcEngine fuctions, Audio and Video Managers functions.

UIAgora implemented as abstract class with \ref createAudioFrameObserver and \ref createVideoFrameObserver
factory methods. You can inherit from this class and override these methods to use custom 
\ref agora::blueprints::IAudioFrameObserver "IAudioFrameObserver" and \ref agora::blueprints::IVideoFrameObserver "IVideoFrameObserver".
 
 @note Methods agora::rtc::IRtcEngine::registerPacketObserver and agora::rtc::IRtcEngine::registerMediaMetadataObserver
 are not implemented in this class. If you need these functions in blueprints simply inherit from this class and add 
 IPacketObserver and/or IMetadataObserver classes and required methods in child class.
 */
UCLASS( Abstract )
class AGORABLUEPRINTABLE_API UIAgora : public UObject, public FTickableGameObject
{
   GENERATED_BODY()

public:
   // delegates:

   /** Reports a warning during SDK runtime.

     In most cases, the application can ignore the warning reported by the SDK because the SDK can usually fix the issue and resume running. For example, when losing connection with the server, the SDK may report #WARN_LOOKUP_CHANNEL_TIMEOUT and automatically try to reconnect.

     @param ErrorCode Warning code: #WARN_CODE_TYPE.
     @param ErrorMessage Pointer to the warning message.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FWarning OnWarningDelegate;

   /** Reports an error during SDK runtime.

    In most cases, the SDK cannot fix the issue and resume running. The SDK requires the application to take action or informs the user about the issue.

    For example, the SDK reports an #ERR_START_CALL error when failing to initialize a call. The application informs the user that the call initialization failed and invokes the \ref LeaveChannel method to leave the channel.

    @param Err Error code: #ERROR_CODE_TYPE.
    @param Msg Pointer to the error message.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FError OnErrorDelegate;

   /** Occurs when a user joins a channel.

    This callback notifies the application that a user joins a specified channel when the application calls the \ref JoinChannel method.

    The channel name assignment is based on @p ChannelId specified in the \ref JoinChannel method.

    If the @p OptionalUserId is not specified in the *JoinChannel* method, the server automatically assigns a @p Uid.

    @param  Channel Channel name.
    @param  Uid User ID of the user joining the channel.
    @param  Elapsed Time elapsed (ms) from the user calling the \ref JoinChannel method until the SDK triggers this callback.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FJoinChannelSuccess OnJoinChannelSuccessDelegate;

   /** Occurs when a user rejoins the channel after disconnection due to network problems.

    When a user loses connection with the server because of network problems, the SDK automatically tries to reconnect and triggers this callback upon reconnection.

     @param Channel Pointer to the channel name.
     @param Uid User ID of the user rejoining the channel.
     @param Elapsed Time elapsed (ms) from starting to reconnect until the SDK triggers this callback.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRejoinChannelSuccess OnRejoinChannelSuccessDelegate;

   /** Occurs when a user leaves the channel.

   This callback notifies the application that a user leaves the channel when the application calls the \ref LeaveChannel method.

   The application retrieves information, such as the call duration and statistics.

    @param Stats Pointer to the statistics of the call: RtcStats.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLeaveChannel OnLeaveChannelDelegate;

   /** Occurs when the user role switches in a live broadcast. For example, from a host to an audience or vice versa.

   This callback notifies the application of a user role switch when the application calls the \ref SetClientRole method.

   The SDK triggers this callback when the local user switches the user role by calling the \ref SetClientRole method after joining the channel.
    @param OldRole Role that the user switches from: #ECLIENT_ROLE_TYPE.
    @param NewRole Role that the user switches to: #ECLIENT_ROLE_TYPE.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FClientRoleChanged OnClientRoleChangedDelegate;

   /** Occurs when a remote user (Communication)/ host (Live Broadcast) joins the channel.

     - Communication profile: This callback notifies the application that another user joins the channel. If other users are already in the channel, the SDK also reports to the application on the existing users.
     - Live-broadcast profile: This callback notifies the application that the host joins the channel. If other hosts are already in the channel, the SDK also reports to the application on the existing hosts. We recommend limiting the number of hosts to 17.

     The SDK triggers this callback under one of the following circumstances:
     - A remote user/host joins the channel by calling the \ref JoinChannel method.
     - A remote user switches the user role to the host by calling the \ref SetClientRole method after joining the channel.
     - A remote user/host rejoins the channel after a network interruption.
     - The host injects an online media stream into the channel by calling the \ref AddInjectStreamUrl method.

     @note In the Live-broadcast profile:
     - The host receives this callback when another host joins the channel.
     - The audience in the channel receives this callback when a new host joins the channel.
     - When a web application joins the channel, the SDK triggers this callback as long as the web application publishes streams.

     @param Uid User ID of the user or host joining the channel.
     @param Elapsed Time delay (ms) from the local user calling the \ref JoinChannel method until the SDK triggers this callback.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FUserJoined OnUserJoinedDelegate;

   /** Occurs when a remote user (Communication)/host (Live Broadcast) leaves the channel.

   Reasons why the user is offline:

   - Leave the channel: When the user/host leaves the channel, the user/host sends a goodbye message. When the message is received, the SDK assumes that the user/host leaves the channel.
   - Drop offline: When no data packet of the user or host is received for a certain period of time (20 seconds for the Communication profile, and more for the Live-broadcast profile), the SDK assumes that the user/host drops offline. Unreliable network connections may lead to false detections, so we recommend using a signaling system for more reliable offline detection.

    @param Uid User ID of the user leaving the channel or going offline.
    @param Reason Reason why the user is offline: #EUSER_OFFLINE_REASON_TYPE.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FUserOffline OnUserOfflineDelegate;

   /** Reports the last mile network quality of the local user once every two seconds before the user joins the channel.

     Last mile refers to the connection between the local device and Agora's edge server. After the application calls the \ref EnableLastmileTest method, this callback reports once every two seconds the uplink and downlink last mile network conditions of the local user before the user joins the channel.

     @param Quality The last mile network quality: #QUALITY_TYPE.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLastmileQuality OnLastmileQualityDelegate;

   /** Reports the last-mile network probe result.

   The SDK triggers this callback within 30 seconds after the app calls the \ref StartLastmileProbeTest method.

   @param Result The uplink and downlink last-mile network probe test result. See FLastmileProbeResult.
   */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLastmileProbeResultDelegate OnLastmileProbeResultDelegate;

   /** Occurs when the connection between the SDK and the server is interrupted.

   @deprecated Deprecated as of v2.3.2. Replaced by the \ref OnConnectionStateChangedDelegate "OnConnectionStateChanged(CONNECTION_STATE_RECONNECTING, CONNECTION_CHANGED_INTERRUPTED)" callback.

    The SDK triggers this callback when it loses connection with the server for more than four seconds after the connection is established.

    After triggering this callback, the SDK tries reconnecting to the server. You can use this callback to implement pop-up reminders.

    This callback is different from \ref OnConnectionLostDelegate "OnConnectionLost":
    - The SDK triggers the \ref OnConnectionInterruptedDelegate "OnConnectionInterrupted" callback when it loses connection with the server for more than four seconds after it successfully joins the channel.
    - The SDK triggers the \ref OnConnectionLostDelegate "OnConnectionLost" callback when it loses connection with the server for more than 10 seconds, whether or not it joins the channel.

    If the SDK fails to rejoin the channel 20 minutes after being disconnected from Agora's edge server, the SDK stops rejoining the channel.

   */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FConnectionInterrupted OnConnectionInterruptedDelegate;

   /** Occurs when the SDK cannot reconnect to Agora's edge server 10 seconds after its connection to the server is interrupted.

    The SDK triggers this callback when it cannot connect to the server 10 seconds after calling the \ref JoinChannel method, whether or not it is in the channel.

    This callback is different from \ref OnConnectionInterruptedDelegate "OnConnectionInterrupted":

    - The SDK triggers the \ref OnConnectionInterruptedDelegate "OnConnectionInterrupted" callback when it loses connection with the server for more than four seconds after it successfully joins the channel.
    - The SDK triggers the \ref OnConnectionLostDelegate "OnConnectionLost" callback when it loses connection with the server for more than 10 seconds, whether or not it joins the channel.

    If the SDK fails to rejoin the channel 20 minutes after being disconnected from Agora's edge server, the SDK stops rejoining the channel.

     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FConnectionLost OnConnectionLostDelegate;

   /**  @deprecated Deprecated as of v2.3.2. Replaced by the \ref OnConnectionStateChangedDelegate "OnConnectionStateChanged(CONNECTION_STATE_FAILED, CONNECTION_CHANGED_BANNED_BY_SERVER)" callback.

    Occurs when your connection is banned by the Agora Server.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FConnectionBanned OnConnectionBannedDelegate;

   /** Occurs when a method is executed by the SDK.

    @param Err The error code (#ERROR_CODE_TYPE) returned by the SDK when a method call fails. If the SDK returns 0, then the method call is successful.
    @param Api Pointer to the method executed by the SDK.
    @param Result Pointer to the result of the method call.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FApiCallExecuted OnApiCallExecutedDelegate;

   /** Occurs when the token expires.

    After a token is specified by calling the \ref JoinChannel method, if the SDK losses connection with the Agora server due to network issues, the token may expire after a certain period of time and a new token may be required to reconnect to the server.

    This callback notifies the application to generate a new token. Call the \ref RenewToken method to renew the token.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRequestToken OnRequestTokenDelegate;

   /** Occurs when the token expires in 30 seconds.

     The user becomes offline if the token used in the \ref JoinChannel method expires. The SDK triggers this callback 30 seconds before the token expires to remind the application to get a new token. Upon receiving this callback, generate a new token on the server and call the \ref RenewToken method to pass the new token to the SDK.

     @param Token Pointer to the token that expires in 30 seconds.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FTokenPrivilegeWillExpire OnTokenPrivilegeWillExpireDelegate;

   /** Reports the statistics of the audio stream from each remote user/host.

     @deprecated Deprecated as of v2.3.2. Use the \ref OnRemoteAudioStatsDelegate "OnRemoteAudioStats" callback instead.

     The SDK triggers this callback once every two seconds to report the audio quality of each remote user/host sending an audio stream. If a channel has multiple users/hosts sending audio streams, the SDK triggers this callback as many times.

     @param Uid User ID of the speaker.
     @param Quality Audio quality of the user: #QUALITY_TYPE.
     @param Delay Time delay (ms) of sending the audio packet from the sender to the receiver, including the time delay of audio sampling pre-processing, transmission, and the jitter buffer.
     @param Lost Packet loss rate (%) of the audio packet sent from the sender to the receiver.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FAudioQuality OnAudioQualityDelegate;

   /** Reports the statistics of the current call session once every two seconds.

      @param Stats Pointer to the RTC engine statistics: FRtcStats.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRtcStatsDelegate OnRtcStatsDelegate;

   /** Reports the last mile network quality of each user in the channel once every two seconds.

     Last mile refers to the connection between the local device and Agora's edge server. This callback reports once every two seconds the last mile network conditions of each user in the channel. If a channel includes multiple users, the SDK triggers this callback as many times.

     @param Uid User ID. The network quality of the user with this @p Uid is reported. If @p Uid is 0, the local network quality is reported.
     @param TxQuality Uplink transmission quality rating of the user in terms of the transmission bitrate, packet loss rate, average RTT (Round-Trip Time), and jitter of the uplink network. @p TxQuality is a quality rating helping you understand how well the current uplink network conditions can support the selected VideoEncoderConfiguration. For example, a 1000 Kbps uplink network may be adequate for video frames with a resolution of 640 &times; 480 and a frame rate of 15 fps in the Live-broadcast profile, but may be inadequate for resolutions higher than 1280 &times; 720. See #QUALITY_TYPE.
     @param RxQuality Downlink network quality rating of the user in terms of the packet loss rate, average RTT, and jitter of the downlink network. See #QUALITY_TYPE.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FNetworkQuality OnNetworkQualityDelegate;

   /** Reports the statistics of the local video stream.

      The SDK triggers this callback once every two seconds for each user/host. If there are multiple users/hosts in the channel, the SDK triggers this callback as many times.

      @note If you have called the \ref EnableDualStreamMode method, the \ref OnLocalVideoStatsDelegate "OnLocalVideoStats" callback reports the statistics of the high-video stream (high bitrate, and high-resolution video stream).

      @param Stats Statistics of the local video stream. See FLocalVideoStats.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLocalVideoStatsDelegate OnLocalVideoStatsDelegate;

   /** Reports the statistics of the video stream from each remote user/host.

     The SDK triggers this callback once every two seconds for each remote user/host. If a channel includes multiple remote users, the SDK triggers this callback as many times.

     @param Stats Statistics of the remote video stream. See FRemoteVideoStats.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteVideoStatsDelegate OnRemoteVideoStatsDelegate;

   /** Reports the statistics of the local audio stream.

      The SDK triggers this callback once every two seconds.

      @param Stats The statistics of the local audio stream. See FLocalAudioStats.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLocalAudioStatsDelegate OnLocalAudioStatsDelegate;

   /** Reports the statistics of the audio stream from each remote user/host.

     This callback replaces the \ref OnAudioQualityDelegate "OnAudioQuality" callback.

     The SDK triggers this callback once every two seconds for each remote user/host. If a channel includes multiple remote users, the SDK triggers this callback as many times.

     @param Stats Pointer to the statistics of the received remote audio streams. See FRemoteAudioStats.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteAudioStatsDelegate OnRemoteAudioStatsDelegate;

   /** Occurs when the local audio state changes.

     This callback indicates the state change of the local audio stream, including the state of the audio recording and encoding, and allows you to troubleshoot issues when exceptions occur.

     @note When the state is #LOCAL_AUDIO_STREAM_STATE_FAILED (3), see the `Error` parameter for details.

     @param State State of the local audio. See #ELOCAL_AUDIO_STREAM_STATE.
     @param Error The error information of the local audio. See #ELOCAL_AUDIO_STREAM_ERROR.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLocalAudioStateChanged OnLocalAudioStateChangedDelegate;

   /** Occurs when the remote audio state changes.

     This callback indicates the state change of the remote audio stream.

     @param Uid ID of the remote user whose audio state changes.
     @param State State of the remote audio. See #EREMOTE_AUDIO_STATE.
     @param Reason The reason of the remote audio state change. See #EREMOTE_AUDIO_STATE_REASON.
     @param Elapsed Time elapsed (ms) from the local user calling the \ref JoinChannel method until the SDK triggers this callback.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteAudioStateChanged OnRemoteAudioStateChangedDelegate;

   /** Reports which users are speaking, the speakers' volume and whether the local user is speaking.

    This callback reports the IDs and volumes of the loudest speakers at the moment in the channel, and whether the local user is speaking.

    By default, this callback is disabled. You can enable it by calling the \ref EnableAudioVolumeIndication method.
    Once enabled, this callback is triggered at the set interval, regardless of whether a user speaks or not.

    The SDK triggers two independent `OnAudioVolumeIndication` callbacks at one time, which separately report the volume information of the local user and all the remote speakers.
    For more information, see the detailed parameter descriptions.

    @note
    - To enable the voice activity detection of the local user, ensure that you set `ReportVad`(true) in the `EnableAudioVolumeIndication` method.
    - Calling the \ref MuteLocalAudioStream method affects the SDK's behavior:
       - If the local user calls the \ref MuteLocalAudioStream method, the SDK stops triggering the local user's callback.
       - 20 seconds after a remote speaker calls the *MuteLocalAudioStream* method, the remote speakers' callback excludes this remote user's information; 20 seconds after all remote users call the *MuteLocalAudioStream* method, the SDK stops triggering the remote speakers' callback.
    - An empty @p Speakers array in the *OnAudioVolumeIndication* callback suggests that no remote user is speaking at the moment.

    @param Speakers A pointer to TArray<AudioVolumeInfo>:
    - Total number of speakers is [0, 3]
    - In the local user’s callback total number of speakers is 1, regardless of whether the local user speaks or not.
    - In the remote speakers' callback, the callback reports the IDs and volumes of the three loudest speakers when there are more than three remote users in the channel, and total number of speakers is 3.
    - In the local user's callback, this struct contains the following members:
      - `uid` = 0,
      - `volume` = `TotalVolume`, which reports the sum of the voice volume and audio-mixing volume of the local user, and
      - `vad`, which reports the voice activity status of the local user.
    - In the remote speakers' callback, this array contains the following members:
      - `uid` of the remote speaker,
      - `volume`, which reports the sum of the voice volume and audio-mixing volume of each remote speaker, and
      - `vad` = 0.

      An empty speakers array in the callback indicates that no remote user is speaking at the moment.
    @param TotalVolume Total volume after audio mixing. The value ranges between 0 (lowest volume) and 255 (highest volume).
    - In the local user’s callback, `TotalVolume` is the sum of the voice volume and audio-mixing volume of the local user.
    - In the remote speakers' callback, `TotalVolume` is the sum of the voice volume and audio-mixing volume of all the remote speakers.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FAudioVolumeIndication OnAudioVolumeIndicationDelegate;

   /** Reports which user is the loudest speaker.

    If the user enables the audio volume indication by calling the \ref EnableAudioVolumeIndication method, this callback returns the @p Uid of the active speaker detected by the audio volume detection module of the SDK.

    @note
    - To receive this callback, you need to call the \ref EnableAudioVolumeIndication method.
    - This callback returns the user ID of the user with the highest voice volume during a period of time, instead of at the moment.

    @param Uid User ID of the active speaker. A @p Uid of 0 represents the local user.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FActiveSpeaker OnActiveSpeakerDelegate;

   /** Occurs when the video stops playing.

    The application can use this callback to change the configuration of the view (for example, displaying other pictures in the view) after the video stops playing.

    @deprecated Deprecated as of v2.4.1. Use LOCAL_VIDEO_STREAM_STATE_STOPPED(0) in the \ref OnLocalVideoStateChangedDelegate "OnLocalVideoStateChanged" callback instead.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FVideoStopped OnVideoStoppedDelegate;

   /** Occurs when the engine receives and renders the first local video frame on the video window.

   @param Width Width (pixels) of the first local video frame.
   @param Height Height (pixels) of the first local video frame.
   @param Elapsed Time elapsed (ms) from the local user calling the \ref JoinChannel method until the SDK triggers this callback.
   If you call the \ref StartPreview method  before calling the *JoinChannel* method, then @p Elapsed is the time elapsed from calling the *StartPreview* method until the SDK triggers this callback.
   */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FFirstLocalVideoFrame OnFirstLocalVideoFrameDelegate;

   /** Occurs when the first remote video frame is received and decoded.

      @deprecated
      This callback is deprecated and replaced by the \ref OnRemoteVideoStateChangedDelegate "OnRemoteVideoStateChanged" callback with the following parameters:
      - #REMOTE_VIDEO_STATE_STARTING (1)
      - #REMOTE_VIDEO_STATE_DECODING (2)

      This callback is triggered in either of the following scenarios:

      - The remote user joins the channel and sends the video stream.
      - The remote user stops sending the video stream and re-sends it after 15 seconds. Reasons for such an interruption include:
      - The remote user leaves the channel.
      - The remote user drops offline.
      - The remote user calls the \ref MuteLocalVideoStream method to stop sending the video stream.
      - The remote user calls the \ref DisableVideo method to disable video.

     The application can configure the user view settings in this callback.

     @param Uid User ID of the remote user sending the video stream.
     @param Width Width (pixels) of the video stream.
     @param Height Height (pixels) of the video stream.
     @param Elapsed Time elapsed (ms) from the local user calling the \ref JoinChannel method until the SDK triggers this callback.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FFirstRemoteVideoDecoded OnFirstRemoteVideoDecodedDelegate;

   /** Occurs when the first remote video frame is rendered.

    The SDK triggers this callback when the first frame of the remote video is displayed in the user's video window. The application can retrieve the time elapsed from a user joining the channel until the first video frame is displayed.

    @param Uid User ID of the remote user sending the video stream.
    @param Width Width (pixels) of the video frame.
    @param Height Height (pixels) of the video stream.
    @param Elapsed Time elapsed (ms) from the local user calling the \ref JoinChannel method until the SDK triggers this callback.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FFirstRemoteVideoFrame OnFirstRemoteVideoFrameDelegate;

   /** Occurs when a remote user's audio stream playback pauses/resumes.

    The SDK triggers this callback when the remote user stops or resumes sending the audio stream by calling the \ref MuteLocalAudioStream method.
     @note This callback returns invalid when the number of users in a channel exceeds 20.

     @param Uid User ID of the remote user.
     @param Muted Whether the remote user's audio stream is muted/unmuted:
     - true: Muted.
     - false: Unmuted.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FUserMuteAudio OnUserMuteAudioDelegate;

   /** Occurs when a remote user's video stream playback pauses/resumes.

     You can also use the \ref OnRemoteVideoStateChangedDelegate "OnRemoteVideoStateChanged" callback with the following parameters:
     - #REMOTE_VIDEO_STATE_STOPPED (0) and #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5).
     - #REMOTE_VIDEO_STATE_DECODING (2) and #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6).

     The SDK triggers this callback when the remote user stops or resumes sending the video stream by calling the \ref MuteLocalVideoStream method.

     @note This callback returns invalid when the number of users in a channel exceeds 20.

     @param Uid User ID of the remote user.
     @param Muted Whether the remote user's video stream playback is paused/resumed:
     - true: Paused.
     - false: Resumed.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FUserMuteVideo OnUserMuteVideoDelegate;

   /** Occurs when a specific remote user enables/disables the video module.

      @deprecated This callback is deprecated and replaced by the \ref OnRemoteVideoStateChangedDelegate "OnRemoteVideoStateChanged" callback with the following parameters:
      - #REMOTE_VIDEO_STATE_STOPPED (0) and #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5).
      - #REMOTE_VIDEO_STATE_DECODING (2) and #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6).

      Once the video module is disabled, the remote user can only use a voice call. The remote user cannot send or receive any video from other users.

      The SDK triggers this callback when the remote user enables or disables the video module by calling the \ref EnableVideo or \ref DisableVideo method.

      @note This callback returns invalid when the number of users in a channel exceeds 20.

      @param Uid User ID of the remote user.
      @param Enabled Whether the remote user enables/disables the video module:
       - true: Enable. The remote user can enter a video session.
       - false: Disable. The remote user can only enter a voice session, and cannot send or receive any video stream.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FUserEnableVideo OnUserEnableVideoDelegate;

   /** Occurs when the audio device state changes.

     This callback notifies the application that the system's audio device state is changed. For example, a headset is unplugged from the device.

     @param DeviceId Pointer to the device ID.
     @param DeviceType Device type: #MEDIA_DEVICE_TYPE.
     @param DeviceState Device state: #MEDIA_DEVICE_STATE_TYPE.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FAudioDeviceStateChanged OnAudioDeviceStateChangedDelegate;

   /** Occurs when the volume of the playback device, microphone, or application changes.

    @param DeviceType Device type: #EMEDIA_DEVICE_TYPE.
    @param Volume Volume of the device. The value ranges between 0 and 255.
    @param Muted
    - true: The audio device is muted.
    - false: The audio device is not muted.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FAudioDeviceVolumeChanged OnAudioDeviceVolumeChangedDelegate;

   /** Occurs when the camera turns on and is ready to capture the video.

    If the camera fails to turn on, fix the error reported in the \ref OnErrorDelegate "OnError" callback.

    @deprecated Deprecated as of v2.4.1. Use #LOCAL_VIDEO_STREAM_STATE_CAPTURING (1) in the \ref OnLocalVideoStateChangedDelegate "OnLocalVideoStateChanged" callback instead.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FCameraReady OnCameraReadyDelegate;

   /** Occurs when the camera focus area changes.

     The SDK triggers this callback when the local user changes the camera focus position by calling the SetCameraFocusPositionInPreview method.

     @note This callback is for Android and iOS only.

     @param X x coordinate of the changed camera focus area.
     @param Y y coordinate of the changed camera focus area.
     @param Width Width of the changed camera focus area.
     @param Height Height of the changed camera focus area.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FCameraFocusAreaChanged OnCameraFocusAreaChangedDelegate;

   /** Occurs when the camera exposure area changes.

   The SDK triggers this callback when the local user changes the camera exposure position by calling the SetCameraExposurePosition method.

    @note This callback is for Android and iOS only.

    @param X x coordinate of the changed camera exposure area.
    @param Y y coordinate of the changed camera exposure area.
    @param Width Width of the changed camera exposure area.
    @param Height Height of the changed camera exposure area.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FCameraExposureAreaChanged  OnCameraExposureAreaChangedDelegate;

   /** Occurs when the audio mixing file playback finishes.

    @deprecated  use OnAudioMixingStateChanged instead.

    You can start an audio mixing file playback by calling the \ref StartAudioMixing method. The SDK triggers this callback when the audio mixing file playback finishes.

    If the *StartAudioMixing* method call fails, an error code returns in the \ref OnErrorDelegate "OnErrorDelegate" callback.

    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FAudioMixingFinished OnAudioMixingFinishedDelegate;

   /** Occurs when the state of the local user's audio mixing file changes.

    - When the audio mixing file plays, pauses playing, or stops playing, this callback returns 710, 711, or 713 in @p State, and 0 in @p ErrorCode.
    - When exceptions occur during playback, this callback returns 714 in @p State and an error in @p ErrorCode.
    - If the local audio mixing file does not exist, or if the SDK does not support the file format or cannot access the music file URL, the SDK returns WARN_AUDIO_MIXING_OPEN_ERROR = 701.

    @param State The state code. See #EAUDIO_MIXING_STATE_TYPE.
    @param ErrorCode The error code. See #EAUDIO_MIXING_ERROR_TYPE.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FAudioMixingStateChanged OnAudioMixingStateChangedDelegate;

   /** Occurs when a remote user starts audio mixing.

     When a remote user calls \ref StartAudioMixing to play the background music, the SDK reports this callback.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteAudioMixingBegin OnRemoteAudioMixingBeginDelegate;

   /** Occurs when a remote user finishes audio mixing.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteAudioMixingEnd OnRemoteAudioMixingEndDelegate;

   /** Occurs when the local audio effect playback finishes.

     The SDK triggers this callback when the local audio effect file playback finishes.

     @param SoundId ID of the local audio effect. Each local audio effect has a unique ID.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FAudioEffectFinished OnAudioEffectFinishedDelegate;

   /**
    Occurs when the SDK decodes the first remote audio frame for playback.

    This callback is triggered in either of the following scenarios:

    - The remote user joins the channel and sends the audio stream.
    - The remote user stops sending the audio stream and re-sends it after 15 seconds. Reasons for such an interruption include:
        - The remote user leaves channel.
        - The remote user drops offline.
        - The remote user calls the \ref MuteLocalAudioStream  method to stop sending the local audio stream.
        - The remote user calls the \ref DisableAudio method to disable audio.

    @param Uid User ID of the remote user sending the audio stream.
    @param Elapsed Time elapsed (ms) from the local user calling the \ref JoinChannel method until the SDK triggers this callback.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FFirstRemoteAudioDecoded OnFirstRemoteAudioDecodedDelegate;

   /** Occurs when the video device state changes.

     @note On a Windows device with an external camera for video capturing, the video disables once the external camera is unplugged.

     @param DeviceId Pointer to the device ID of the video device that changes state.
     @param DeviceType Device type: #MEDIA_DEVICE_TYPE.
     @param DeviceState Device state: #MEDIA_DEVICE_STATE_TYPE.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FVideoDeviceStateChanged OnVideoDeviceStateChangedDelegate;

   /** Occurs when the local video stream state changes.

    @note This callback indicates the state of the local video stream, including camera capturing and video encoding, and allows you to troubleshoot issues when exceptions occur.

    @param LocalVideoState State type #ELOCAL_VIDEO_STREAM_STATE. When the state is LOCAL_VIDEO_STREAM_STATE_FAILED (3), see the *Error* parameter for details.
    @param Error The detailed error information. code #ELOCAL_VIDEO_STREAM_ERROR.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLocalVideoStateChanged OnLocalVideoStateChangedDelegate;

   /** Occurs when the video size or rotation of a specified user changes.

    @param Uid User ID of the remote user or local user (0) whose video size or rotation changes.
    @param Width New width (pixels) of the video.
    @param Height New height (pixels) of the video.
    @param Rotation New rotation of the video [0 to 360).
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FVideoSizeChanged OnVideoSizeChangedDelegate;

   /** Occurs when the remote video state changes.

    @param Uid ID of the remote user whose video state changes.
    @param State State of the remote video. See #EREMOTE_VIDEO_STATE.
    @param Reason The reason of the remote video state change. See #EREMOTE_VIDEO_STATE_REASON.
    @param Elapsed Time elapsed (ms) from the local user calling the \ref JoinChannel method until the SDK triggers this callback.
   */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteVideoStateChanged OnRemoteVideoStateChangedDelegate;

   /** Occurs when a specified remote user enables/disables the local video capturing function.

      @deprecated
      This callback is deprecated and replaced by the \ref OnRemoteVideoStateChangedDelegate "OnRemoteVideoStateChanged" callback with the following parameters:
      - #REMOTE_VIDEO_STATE_STOPPED (0) and #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5).
      - #REMOTE_VIDEO_STATE_DECODING (2) and #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6).

     This callback is only applicable to the scenario when the user only wants to watch the remote video without sending any video stream to the other user.

     The SDK triggers this callback when the remote user resumes or stops capturing the video stream by calling the \ref EnableLocalVideo method.

     @param Uid User ID of the remote user.
     @param Enabled Whether the specified remote user enables/disables the local video capturing function:
      - true: Enable. Other users in the channel can see the video of this remote user.
      - false: Disable. Other users in the channel can no longer receive the video stream from this remote user, while this remote user can still receive the video streams from other users.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FUserEnableLocalVideo OnUserEnableLocalVideoDelegate;

   /** Occurs when the local user receives the data stream from the remote user within five seconds.

   The SDK triggers this callback when the local user receives the stream message that the remote user sends by calling the \ref SendStreamMessage method.
   @param Uid User ID of the remote user sending the message.
   @param StreamId Stream ID.
   @param Data Pointer to the data received by the local user.
   @param Length Length of the data in bytes.
   */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FStreamMessage OnStreamMessageDelegate;

   /** Occurs when the local user does not receive the data stream from the remote user within five seconds.

  The SDK triggers this callback when the local user fails to receive the stream message that the remote user sends by calling the \ref SendStreamMessage method.
     @param Uid User ID of the remote user sending the message.
     @param StreamId Stream ID.
     @param Code Error code: #ERROR_CODE_TYPE.
     @param Missed Number of lost messages.
     @param Cached Number of incoming cached messages when the data stream is interrupted.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FStreamMessageError OnStreamMessageErrorDelegate;

   /** Occurs when the media engine loads.*/
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FMediaEngineLoadSuccess OnMediaEngineLoadSuccessDelegate;

   /** Occurs when the media engine call starts.*/
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FMediaEngineStartCallSuccess OnMediaEngineStartCallSuccessDelegate;

   /** Occurs when the state of the media stream relay changes.

      The SDK returns the state of the current media relay with any error message.

      @param State The state code in #ECHANNEL_MEDIA_RELAY_STATE.
      @param Ñode The error code in #ECHANNEL_MEDIA_RELAY_ERROR.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FChannelMediaRelayStateChanged OnChannelMediaRelayStateChangedDelegate;

   /** Reports events during the media stream relay.

     @param Code The event code in #ECHANNEL_MEDIA_RELAY_EVENT.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FChannelMediaRelayEvent OnChannelMediaRelayEventDelegate;

   /** Occurs when the engine sends the first local audio frame.

   @param Elapsed Time elapsed (ms) from the local user calling \ref JoinChannel until the SDK triggers this callback.
   */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FFirstLocalAudioFrame OnFirstLocalAudioFrameDelegate;

   /** Occurs when the engine receives the first audio frame from a specific remote user.

   @param Uid User ID of the remote user.
   @param Elapsed Time elapsed (ms) from the remote user calling \ref JoinChannel until the SDK triggers this callback.
   */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FFirstRemoteAudioFrame OnFirstRemoteAudioFrameDelegate;

   /** Occurs when the state of the RTMP streaming changes.

  The SDK triggers this callback to report the result of the local user calling the \ref AddPublishStreamUrl or \ref RemovePublishStreamUrl method.

  This callback indicates the state of the RTMP streaming. When exceptions occur, you can troubleshoot issues by referring to the detailed error descriptions in the *ErrCode* parameter.

  @param Url The RTMP URL address.
  @param State The RTMP streaming state. See: #ERTMP_STREAM_PUBLISH_STATE.
  @param ErrCode The detailed error information for streaming. See: #ERTMP_STREAM_PUBLISH_ERROR.
  */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRtmpStreamingStateChanged OnRtmpStreamingStateChangedDelegate;

   /** Reports the result of calling the \ref AddPublishStreamUrl method. (CDN live only.)

    @param Url The RTMP URL address.
    @param Error Error code: #ERROR_CODE_TYPE. Main errors include:
    - #ERR_OK (0): The publishing succeeds.
    - #ERR_FAILED (1): The publishing fails.
    - #ERR_INVALID_ARGUMENT (2): Invalid argument used. If, for example, you did not call \ref SetLiveTranscoding to configure LiveTranscoding before calling \ref AddPublishStreamUrl , the SDK reports #ERR_INVALID_ARGUMENT.
    - #ERR_TIMEDOUT (10): The publishing timed out.
    - #ERR_ALREADY_IN_USE (19): The chosen URL address is already in use for CDN live streaming.
    - #ERR_RESOURCE_LIMITED (22): The backend system does not have enough resources for the CDN live streaming.
    - #ERR_ENCRYPTED_STREAM_NOT_ALLOWED_PUBLISH (130): You cannot publish an encrypted stream.
    - #ERR_PUBLISH_STREAM_CDN_ERROR (151)
    - #ERR_PUBLISH_STREAM_NUM_REACH_LIMIT (152)
    - #ERR_PUBLISH_STREAM_NOT_AUTHORIZED (153)
    - #ERR_PUBLISH_STREAM_INTERNAL_SERVER_ERROR (154)
    - #ERR_PUBLISH_STREAM_FORMAT_NOT_SUPPORTED (156)
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FStreamPublished OnStreamPublishedDelegate;

   /** Reports the result of calling the \ref RemovePublishStreamUrl method. (CDN live only.)

     This callback indicates whether you have successfully removed an RTMP stream from the CDN.

     @param Url The RTMP URL address.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FStreamUnpublished OnStreamUnpublishedDelegate;

   /** Occurs when the publisher's transcoding is updated. */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FTranscodingUpdated OnTranscodingUpdatedDelegate;

   /** Occurs when a voice or video stream URL address is added to a live broadcast.

   @param Url Pointer to the URL address of the externally injected stream.
   @param Uid User ID.
   @param Status State of the externally injected stream: #INJECT_STREAM_STATUS.
   */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FStreamInjectedStatus OnStreamInjectedStatusDelegate;

   /** Occurs when the local audio route changes.

     The SDK triggers this callback when the local audio route switches to an earpiece, speakerphone, headset, or Bluetooth device.

     @note This callback is for Android and iOS only.

     @param Routing Audio output routing. See: #EAUDIO_ROUTE_TYPE.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FAudioRouteChanged OnAudioRouteChangedDelegate;

   /** Occurs when the locally published media stream falls back to an audio-only stream due to poor network conditions or switches back to the video after the network conditions improve.

    If you call \ref SetLocalPublishFallbackOption and set *Option* as #STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK triggers this callback when the locally published stream falls back to audio-only mode due to poor uplink conditions, or when the audio stream switches back to the video after the uplink network condition improves.

    @param IsFallbackOrRecover Whether the locally published stream falls back to audio-only or switches back to the video:
    - true: The locally published stream falls back to audio-only due to poor network conditions.
    - false: The locally published stream switches back to the video after the network conditions improve.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLocalPublishFallbackToAudioOnly OnLocalPublishFallbackToAudioOnlyDelegate;

   /** Occurs when the remote media stream falls back to audio-only stream due to poor network conditions or switches back to the video stream after the network conditions improve.

     If you call \ref SetRemoteSubscribeFallbackOption and set @p Option as #STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK triggers this callback when the remote media stream falls back to audio-only mode due to poor uplink conditions, or when the remote media stream switches back to the video after the uplink network condition improves.

      @note Once the remote media stream switches to the low stream due to poor network conditions, you can monitor the stream switch between a high and low stream in the RemoteVideoStats callback.

      @param Uid ID of the remote user sending the stream.
      @param IsFallbackOrRecover Whether the remotely subscribed media stream falls back to audio-only or switches back to the video:
      - true: The remotely subscribed media stream falls back to audio-only due to poor network conditions.
      - false: The remotely subscribed media stream switches back to the video stream after the network conditions improved.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteSubscribeFallbackToAudioOnly OnRemoteSubscribeFallbackToAudioOnlyDelegate;

   /** Reports the transport-layer statistics of each remote audio stream.

     @deprecated This callback is deprecated and replaced by the \ref OnRemoteAudioStatsDelegate "OnRemoteAudioStats" callback.

     This callback reports the transport-layer statistics, such as the packet loss rate and network time delay, once every two seconds after the local user receives an audio packet from a remote user.

     @param Uid  User ID of the remote user sending the audio packet.
     @param Delay Network time delay (ms) from the remote user sending the audio packet to the local user.
     @param Lost Packet loss rate (%) of the audio packet sent from the remote user.
     @param RxKBitRate  Received bitrate (Kbps) of the audio packet sent from the remote user.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteAudioTransportStats OnRemoteAudioTransportStatsDelegate;

   /** Reports the transport-layer statistics of each remote video stream.

    @deprecated This callback is deprecated and replaced by the \ref OnRemoteVideoStatsDelegate "OnRemoteVideoStats" callback.

    This callback reports the transport-layer statistics, such as the packet loss rate and network time delay, once every two seconds after the local user receives a video packet from a remote user.

    @param Uid User ID of the remote user sending the video packet.
    @param Delay Network time delay (ms) from the remote user sending the video packet to the local user.
    @param Lost Packet loss rate (%) of the video packet sent from the remote user.
    @param RxKBitRate Received bitrate (Kbps) of the video packet sent from the remote user.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FRemoteVideoTransportStats OnRemoteVideoTransportStatsDelegate;

   /** Occurs when the microphone is enabled/disabled.

    @deprecated The \ref OnMicrophoneEnabledDelegate "OnMicrophoneEnabled" callback is deprecated. Use #LOCAL_AUDIO_STREAM_STATE_STOPPED (0) or #LOCAL_AUDIO_STREAM_STATE_RECORDING (1) in the \ref OnLocalAudioStateChangedDelegate "OnLocalAudioStateChanged" callback instead.

    The SDK triggers this callback when the local user resumes or stops capturing the local audio stream by calling the \ref EnableLocalAudio method.

    @param Enabled Whether the microphone is enabled/disabled:
     - true: Enabled.
     - false: Disabled.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FMicrophoneEnabled OnMicrophoneEnabledDelegate;

   /** Occurs when the connection state between the SDK and the server changes.

     @param State See #ECONNECTION_STATE_TYPE.
     @param Reason See #ECONNECTION_CHANGED_REASON_TYPE.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FConnectionStateChanged OnConnectionStateChangedDelegate;

   /** Occurs when the local network type changes.

  When the network connection is interrupted, this callback indicates whether the interruption is caused by a network type change or poor network conditions.

    @param Type See #ENETWORK_TYPE.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FNetworkTypeChanged OnNetworkTypeChangedDelegate;

   /** Occurs when the local user successfully registers a user account by calling the \ref RegisterLocalUserAccount method or joins a channel by calling the \ref JoinChannelWithUserAccount method.This callback reports the user ID and user account of the local user.

     @param Uid The ID of the local user.
     @param UserAccount The user account of the local user.
     */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FLocalUserRegistered OnLocalUserRegisteredDelegate;

   /** Occurs when the SDK gets the user ID and user account of the remote user.

    After a remote user joins the channel, the SDK gets the UID and user account of the remote user,
    caches them in a mapping table object (`FAgoraUserInfo`), and triggers this callback on the local client.

    @param Uid The ID of the remote user.
    @param Info The `FAgoraUserInfo` object that contains the user ID and user account of the remote user.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|Callbacks" )
      FUserInfoUpdated OnUserInfoUpdatedDelegate;

   /** Initializes the Agora SDK service.
    
   Ensure you have called this method before operating agora.
   @param[out] Result Output parameter specifies is Agora was initialized successfuly.
   Result could be:
      - Success,
      - Error.
      See EResult.
	  In case of Error search message "UIAgora::Initialize" in log.
   @param[in] AppId App ID issued to you by Agora. Apply for a new App ID from Agora if it is missing from your kit.
   @param[in] OptionalContext For android, it the context(Activity or Application),
	                       for Windows - Video hot plug device.
                          The video window handle. Once set, this parameter enables you to plug
                          or unplug the video devices while they are powered.
   */
   UFUNCTION( BlueprintCallable, meta = ( ExpandEnumAsExecs = result ), Category = "Agora" )
      void Initialize( EResult& Result, const FString& AppId, UPlainData* OptionalContext = nullptr );

   virtual void BeginDestroy() override;
   virtual ~UIAgora() = default;

   /** Allows a user to join a channel.

    Users in the same channel can talk to each other, and multiple users in the same channel can start a group chat. Users with different App IDs cannot call each other.

 You must call the \ref LeaveChannel "LeaveChannel" method to exit the current call before entering another channel.

 A successful \ref JoinChannel method call triggers the following callbacks:
 - The local client: \ref OnJoinChannelSuccessDelegate "OnJoinChannelSuccess"
 - The remote client: \ref OnUserJoinedDelegate "OnUserJoined" , if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.

   When the connection between the client and Agora's server is interrupted due to poor network conditions, the SDK tries reconnecting to the server. When the local client successfully rejoins the channel, the SDK triggers the \ref OnRejoinChannelSuccessDelegate "OnRejoinChannelSuccess" callback on the local client.

    @param ChannelId Pointer to the unique channel name for the Agora RTC session in the string format smaller than 64 bytes. Supported characters:
    - The 26 lowercase English letters: a to z
    - The 26 uppercase English letters: A to Z
    - The 10 numbers: 0 to 9
    - The space
    - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","
    @param Token Pointer to the token generated by the application server. In most circumstances, a static App ID suffices. For added security, use a Channel Key.
    - If the user uses a static App ID, *token* is optional and can be not set.
    - If the user uses a Channel Key, Agora issues an additional App Certificate for you to generate a user key based on the algorithm and App Certificate for user authentication on the server.
    @param OptionalInfo (Optional) Pointer to additional information about the channel. This parameter can contain channel related information or nothing. Other users in the channel will not receive this message.
    @param OptionalUserId (Optional) User ID. An integer with a value ranging from 1 to 2<sup>32</sup>-1. The @p OptionalUserId must be unique. If a @p OptionalUserId is not assigned (or set to 0), the SDK assigns and returns a @p OptionalUserId in the \ref OnJoinChannelSuccessDelegate "OnJoinChannelSuccess" callback. Your application must record and maintain the returned *Uid* since the SDK does not do so.

    @return
    - 0: Success.
    - < 0: Failure.
       - #ERR_INVALID_ARGUMENT (-2)
       - #ERR_NOT_READY (-3)
       - #ERR_REFUSED (-5)
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int JoinChannel( const FString & ChannelId, const FString & Token, const FString & OptionalInfo, int64 OptionalUserId = 0 );
  
   /** Allows a user to leave a channel, such as hanging up or exiting a call.

    After joining a channel, the user must call the *LeaveChannel* method to end the call before joining another channel.

    This method returns 0 if the user leaves the channel and releases all resources related to the call.

    This method call is asynchronous, and the user has not left the channel when the method call returns. Once the user leaves the channel, the SDK triggers the \ref OnLeaveChannelDelegate "OnLeaveChannel" callback.

    A successful \ref LeaveChannel "LeaveChannel" method call triggers the following callbacks:
    - The local client: \ref OnLeaveChannelDelegate "OnLeaveChannel"
    - The remote client: \ref OnUserOfflineDelegate "OnUserOffline" , if the user leaving the channel is in the Communication channel, or is a BROADCASTER in the Live Broadcast profile.

    @note
    - If you call the \ref IRtcEngine::release "release" method immediately after the *LeaveChannel* method, the *LeaveChannel* process interrupts, and the \ref OnLeaveChannelDelegate "OnLeaveChannel" callback is not triggered.
    - If you call the *LeaveChannel* method during a CDN live streaming, the SDK triggers the \ref RemovePublishStreamUrl "RemovePublishStreamUrl" method.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int LeaveChannel();
   
   /** Retrieves the SDK version number.

   @return The version of the current SDK in the string format. For example, 2.3.1.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      FString GetVersion();
  
   /** Starts the local video preview before joining the channel.

     Before calling this method, you must:

     - Call the \ref SetupLocalVideo method to set up the local preview window and configure the attributes.
     - Call the \ref EnableVideo method to enable video.

     @note Once the StartPreview method is called to start the local video preview, if you leave the channel by calling the \ref LeaveChannel method, the local video preview remains until you call the \ref StopPreview method to disable it.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StartPreview();

   /** Stops the local video preview and disables video.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StopPreview();

   /** Enables the video module.

     Call this method either before joining a channel or during a call. If this method is called before joining a channel, the call starts in the video mode. If this method is called during an audio call, the audio mode switches to the video mode. To disable the video module, call the \ref DisableVideo method.

     A successful \ref EnableVideo method call triggers the \ref OnUserEnableVideoDelegate "OnUserEnableVideo" (true) callback on the remote client.
     @note
     - This method affects the internal engine and can be called after the \ref LeaveChannel method.
     - This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
         - \ref EnableLocalVideo : Whether to enable the camera to create the local video stream.
         - \ref MuteLocalVideoStream : Whether to publish the local video stream.
         - \ref MuteRemoteVideoStream : Whether to subscribe to and play the remote video stream.
         - \ref MuteAllRemoteVideoStreams : Whether to subscribe to and play all remote video streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableVideo();

   /** Disables the video module.

    This method can be called before joining a channel or during a call. If this method is called before joining a channel, the call starts in audio mode. If this method is called during a video call, the video mode switches to the audio mode. To enable the video module, call the \ref EnableVideo method.

    A successful \ref DisableVideo method call triggers the \ref OnUserEnableVideoDelegate "OnUserEnableVideo" (false) callback on the remote client.
     @note
     - This method affects the internal engine and can be called after the \ref LeaveChannel method.
     - This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
         - \ref EnableLocalVideo : Whether to enable the camera to create the local video stream.
         - \ref MuteLocalVideoStream : Whether to publish the local video stream.
         - \ref MuteRemoteVideoStream : Whether to subscribe to and play the remote video stream.
         - \ref MuteAllRemoteVideoStreams : Whether to subscribe to and play all remote video streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int DisableVideo();

   /** Enables the audio module.

   The audio mode is enabled by default.

    @note
    - This method affects the internal engine and can be called after the \ref LeaveChannel method. You can call this method either before or after joining a channel.
    - This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the audio engine modules separately:
        - \ref EnableLocalAudio : Whether to enable the microphone to create the local audio stream.
        - \ref MuteLocalAudioStream : Whether to publish the local audio stream.
        - \ref MuteRemoteAudioStream : Whether to subscribe to and play the remote audio stream.
        - \ref MuteAllRemoteAudioStreams : Whether to subscribe to and play all remote audio streams.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableAudio();

   /** Disables the audio module.

     @note
     - This method affects the internal engine and can be called after the \ref LeaveChannel method. You can call this method either before or after joining a channel.
     - This method resets the internal engine and takes some time to take effect. We recommend using the \ref EnableLocalAudio and \ref MuteLocalAudioStream methods to capture, process, and send the local audio streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int DisableAudio();

   /** Stops/Resumes sending the local audio stream.

     A successful \ref MuteLocalAudioStream method call triggers the \ref OnUserMuteAudioDelegate "OnUserMuteAudio" callback on the remote client.
     @note When @p Mute is set as @p true, this method does not disable the microphone, which does not affect any ongoing recording.

     @param Mute Sets whether to send/stop sending the local audio stream:
     - true: Stops sending the local audio stream.
     - false: (Default) Sends the local audio stream.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int MuteLocalAudioStream( bool Mute );

   /** Stops/Resumes sending the local video stream.

     A successful \ref MuteLocalVideoStream method call triggers the \ref OnUserMuteVideoDelegate "OnUserMuteVideo" callback on the remote client.
     @note When set to *true*, this method does not disable the camera which does not affect the retrieval of the local video streams. This method executes faster than the \ref EnableLocalVideo method which controls the sending of the local video stream.

     @param Mute Sets whether to send/stop sending the local video stream:
     - true: Stop sending the local video stream.
     - false: (Default) Send the local video stream.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int MuteLocalVideoStream( bool Mute );

   /** Sets the built-in encryption mode.

     The Agora SDK supports built-in encryption, which is set to the @p ENCRYPTION_MODE_AES_128_XTC mode by default. Call this method to use other encryption modes.

     All users in the same channel must use the same encryption mode and password.

     Refer to the information related to the AES encryption algorithm on the differences between the encryption modes.

     @note Call the \ref SetEncryptionSecret method to enable the built-in encryption function before calling this method.

     @param EncryptionMode Encryption mode:
     - ENCRYPTION_MODE_AES_128_XTC: (Default) 128-bit AES encryption, XTS mode.
     - ENCRYPTION_MODE_AES_128_ECB: 128-bit AES encryption, ECB mode.
     - ENCRYPTION_MODE_AES_256_XTS: 256-bit AES encryption, XTS mode.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|Encryption" )
      int SetEncryptionMode( EENCRYPTION_MODE EncryptionMode );

   /** Enables built-in encryption with an encryption password before users join a channel.

     All users in a channel must use the same encryption password. The encryption password is automatically cleared once a user leaves the channel.

     If an encryption password is not specified, the encryption functionality will be disabled.

     @note
     - Do not use this method for CDN live streaming.
     - For optimal transmission, ensure that the encrypted data size does not exceed the original data size + 16 bytes. 16 bytes is the maximum padding size for AES encryption.

     @param Secret Pointer to the encryption password.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|Encryption" )
      int SetEncryptionSecret( const FString& Secret );

   /** Sets the channel profile.

    The SDK needs to know the application scenario to set the appropriate channel profile to apply different optimization methods.

    @note
    - This method applies only to the Live-broadcast profile.
    - Users in the same channel must use the same channel profile.
    - Before calling this method to set a new channel profile, \ref IRtcEngine::release "release" the current engine and create a new engine using \ref Initialize .
    - Call this method before a user \ref JoinChannel "joins a channel" because you cannot configure the channel profile when the channel is in use.
    - In the Communication profile, the Agora SDK supports encoding only in raw data, not in texture.

    @param Profile Sets the channel profile. See #ECHANNEL_PROFILE_TYPE.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetChannelProfile( ECHANNEL_PROFILE_TYPE Profile );

   /** Sets the video encoder configuration.

     Each video encoder configuration corresponds to a set of video parameters, including the resolution, frame rate, bitrate, and video orientation.

     The parameters specified in this method are the maximum values under ideal network conditions. If the video engine cannot render the video using the specified parameters due to poor network conditions, the parameters further down the list are considered until a successful configuration is found.

     @note If you do not need to set the video encoder configuration after joining the channel, you can call this method before the \ref EnableVideo method to reduce the render time of the first video frame.

     @param Configuration Sets the local video encoder configuration. See FVideoEncoderConfiguration.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetVideoEncoderConfiguration( const FVideoEncoderConfiguration& Configuration );

   /** Starts an audio call test.

    This method starts an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly.

    In the audio call test, you record your voice. If the recording plays back within the set time interval, the audio devices and the network connection are working properly.

    @note
    - Call this method before joining a channel.
    - After calling this method, call the \ref StopEchoTest method to end the test. Otherwise, the app cannot run the next echo test, or call the \ref JoinChannel method.
    - In the Live-broadcast profile, only a host can call this method.
    @param IntervalInSeconds The time interval (s) between when you speak and when the recording plays back.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StartEchoTest( int IntervalInSeconds );

   /** Stops the audio call test.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StopEchoTest();

   /** Stops an audio recording on the client.

     You can call this method before calling the \ref LeaveChannel method else, the recording automatically stops when the \ref LeaveChannel method is called.

     @return
     - 0: Success
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StopAudioRecording();

   /** Stops playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StopAudioMixing();

   /** Pauses playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int PauseAudioMixing();

   /** Resumes playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int ResumeAudioMixing();

   /** Retrieves the audio mixing volume for local playback.

     This method helps troubleshoot audio volume related issues.

     @note Call this method when you are in a channel.

     @return
     - &ge; 0: The audio mixing volume, if this method call succeeds. The value range is [0,100].
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int GetAudioMixingPlayoutVolume();

   /** Retrieves the audio mixing volume for publishing.

     This method helps troubleshoot audio volume related issues.

     @note Call this method when you are in a channel.

     @return
     - &ge; 0: The audio mixing volume for publishing, if this method call succeeds. The value range is [0,100].
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int GetAudioMixingPublishVolume();

   /** Retrieves the duration (ms) of the music file.

     Call this method when you are in a channel.

     @return
     - &ge; 0: The audio mixing duration, if this method call succeeds.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int GetAudioMixingDuration();

   /** Retrieves the playback position (ms) of the music file.

     Call this method when you are in a channel.

     @return
     - &ge; 0: The current playback position of the audio mixing, if this method call succeeds.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int GetAudioMixingCurrentPosition();

   /** Retrieves the volume of the audio effects.

     The value ranges between 0.0 and 100.0.

     @return
     - &ge; 0: Volume of the audio effects, if this method call succeeds.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int GetEffectsVolume();

   /** Stops playing all audio effects.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StopAllEffects();

   /** Pauses all audio effects.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int PauseAllEffects();

   /** Resumes playing all audio effects.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int ResumeAllEffects();

   /**  Enables the network connection quality test.

     This method tests the quality of the users' network connections and is disabled by default.

     Before a user joins a channel or before an audience switches to a host, call this method to check the uplink network quality.

     This method consumes additional network traffic, and hence may affect communication quality.

     Call the \ref DisableLastmileTest method to disable this test after receiving the \ref OnLastmileQualityDelegate "OnLastmileQuality" callback, and before joining a channel.

     @note
     - Do not call any other methods before receiving the \ref OnLastmileQualityDelegate "OnLastmileQuality" callback. Otherwise, the callback may be interrupted by other methods, and hence may not be triggered.
     - A host should not call this method after joining a channel (when in a call).

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableLastmileTest();

   /** Disables the network connection quality test.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int DisableLastmileTest();

   /** Stops the last-mile network probe test. */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StopLastmileProbeTest();

   /** Removes the watermark image from the video stream added by the \ref AddVideoWatermark method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int ClearVideoWatermarks();

   /** Stops the media stream relay.
     
     Once the relay stops, the broadcaster quits all the destination channels.
     
      After a successful method call, the SDK triggers the \ref OnChannelMediaRelayStateChangedDelegate "OnChannelMediaRelayStateChanged" callback. If the callback returns #RELAY_STATE_IDLE (0) and #RELAY_OK (0), the broadcaster successfully stops the relay.
    
     @note If the method call fails, the SDK triggers the \ref OnChannelMediaRelayStateChangedDelegate "OnChannelMediaRelayStateChanged" callback with the #RELAY_ERROR_SERVER_NO_RESPONSE (2) or #RELAY_ERROR_SERVER_CONNECTION_LOST (8) state code. You can leave the channel by calling the \ref LeaveChannel method, and the media stream relay automatically stops.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StopChannelMediaRelay();

   /** Disables/Re-enables the local audio function.

    The audio function is enabled by default. This method disables or re-enables the local audio function, that is, to stop or restart local audio capturing.

    This method does not affect receiving or playing the remote audio streams,and EnableLocalAudio(false) is applicable to scenarios where the user wants to receive remote audio streams without sending any audio stream to other users in the channel.

    The SDK triggers the \ref OnMicrophoneEnabledDelegate "OnMicrophoneEnabled" callback once the local audio function is disabled or enabled.

     @note
     - Call this method after the \ref JoinChannel method.
     - This method is different from the \ref MuteLocalAudioStream method:

        - \ref EnableLocalAudio : Disables/Re-enables the local audio capturing and processing.
        - \ref MuteLocalAudioStream : Sends/Stops sending the local audio streams.

     @param Enabled Sets whether to disable/re-enable the local audio function:
     - true: (Default) Re-enable the local audio function, that is, to start the local audio capturing device (for example, the microphone).
     - false: Disable the local audio function, that is, to stop local audio capturing.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableLocalAudio( bool Enabled );

   /** Stops/Resumes receiving all remote users' audio streams.

     @param Mute Sets whether to receive/stop receiving all remote users' audio streams.
     - true: Stops receiving all remote users' audio streams.
     - false: (Default) Receives all remote users' audio streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int MuteAllRemoteAudioStreams( bool Mute );

   /** Stops/Resumes receiving all remote users' audio streams by default.

     @param Mute Sets whether to receive/stop receiving all remote users' audio streams by default:
     - true:  Stops receiving all remote users' audio streams by default.
     - false: (Default) Receives all remote users' audio streams by default.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetDefaultMuteAllRemoteAudioStreams( bool Mute );

   /** Enables/Disables the local video capture.

     This method disables or re-enables the local video capturer, and does not affect receiving the remote video stream.

     After you call the \ref EnableVideo method, the local video capturer is enabled by default. You can call \ref EnableLocalVideo (false) to disable the local video capturer. If you want to re-enable it, call \ref EnableLocalVideo (true).

     After the local video capturer is successfully disabled or re-enabled, the SDK triggers the \ref OnUserEnableLocalVideoDelegate "OnUserEnableLocalVideo" callback on the remote client.

     @note This method affects the internal engine and can be called after the \ref LeaveChannel method.

     @param Enabled Sets whether to disable/re-enable the local video, including the capturer, renderer, and sender:
     - true: (Default) Re-enable the local video.
     - false: Disable the local video. Once the local video is disabled, the remote users can no longer receive the video stream of this user, while this user can still receive the video streams of the other remote users.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableLocalVideo( bool Enabled );

   /** Stops/Resumes receiving all video stream from a specified remote user.

     @param  Mute Sets whether to receive/stop receiving all remote users' video streams:
     - true: Stop receiving all remote users' video streams.
     - false: (Default) Receive all remote users' video streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int MuteAllRemoteVideoStreams( bool Mute );

   /** Stops/Resumes receiving all remote users' video streams by default.

     @param Mute Sets whether to receive/stop receiving all remote users' video streams by default:
     - true: Stop receiving all remote users' video streams by default.
     - false: (Default) Receive all remote users' video streams by default.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetDefaultMuteAllRemoteVideoStreams( bool Mute );

   /** Enables/Disables stereo panning for remote users.

    Ensure that you call this method before joinChannel to enable stereo panning for remote users so that the local user can track the position of a remote user by calling \ref agora::rtc::IRtcEngine::setRemoteVoicePosition "setRemoteVoicePosition".

    @param Enabled Sets whether or not to enable stereo panning for remote users:
    - true: enables stereo panning.
    - false: disables stereo panning.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableSoundPositionIndication( bool Enabled );

   /** Sets the stream mode to the single-stream (default) or dual-stream mode. (Live broadcast only.)

     If the dual-stream mode is enabled, the receiver can choose to receive the high stream (high-resolution and high-bitrate video stream), or the low stream (low-resolution and low-bitrate video stream).

     @param Enabled Sets the stream mode:
     - true: Dual-stream mode.
     - false: (Default) Single-stream mode.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableDualStreamMode( bool Enabled );

   /** Enables interoperability with the Agora Web SDK.

     @note This method applies only to the Live-broadcast profile. In the Communication profile, interoperability with the Agora Web SDK is enabled by default.

     @param Enabled Sets whether to enable/disable interoperability with the Agora Web SDK:
     - true: Enable.
     - false: (Default) Disable.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableWebSdkInteroperability( bool Enabled );

   /** Adjusts the volume during audio mixing.

    Call this method when you are in a channel.

    @param Volume Audio mixing volume. The value ranges between 0 and 100 (default).

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int AdjustAudioMixingVolume( int Volume );

   /** Adjusts the audio mixing volume for local playback.

    @note Call this method when you are in a channel.

    @param Volume Audio mixing volume for local playback. The value ranges between 0 and 100 (default).

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int AdjustAudioMixingPlayoutVolume( int Volume );

   /** Adjusts the audio mixing volume for publishing (for remote users).

    @note Call this method when you are in a channel.

    @param Volume Audio mixing volume for publishing. The value ranges between 0 and 100 (default).

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int AdjustAudioMixingPublishVolume( int Volume );

   /** Sets the volume of the audio effects.

     @param Volume Sets the volume of the audio effects. The value ranges between 0 and 100 (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetEffectsVolume( int Volume );

   /** Sets the volume of a specified audio effect.

    @param SoundId ID of the audio effect. Each audio effect has a unique ID.
    @param Volume Sets the volume of the specified audio effect. The value ranges between 0 and 100 (default).

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetVolumeOfEffect( int SoundId, int Volume );

   /** Stops playing a specified audio effect.

     @param SoundId ID of the audio effect to stop playing. Each audio effect has a unique ID.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StopEffect( int SoundId );

   /** Releases a specified preloaded audio effect from the memory.

     @param SoundId ID of the audio effect. Each audio effect has a unique ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int UnloadEffect( int SoundId );

   /** Pauses a specified audio effect.

     @param SoundId ID of the audio effect. Each audio effect has a unique ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int PauseEffect( int SoundId );

   /** Resumes playing a specified audio effect.

     @param SoundId ID of the audio effect. Each audio effect has a unique ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int ResumeEffect( int SoundId );

   /** Changes the voice pitch of the local speaker.

     @param Pitch Sets the voice pitch. The value ranges between 0.5 and 2.0. The lower the value, the lower the voice pitch. The default value is 1.0 (no change to the local voice pitch).
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLocalVoicePitch( float Pitch );

   /** Sets the output log level of the SDK.

     You can use one or a combination of the log filter levels. The log level follows the sequence of OFF, CRITICAL, ERROR, WARNING, INFO, and DEBUG. Choose a level to see the logs preceding that level.

     If you set the log level to WARNING, you see the logs within levels CRITICAL, ERROR, and WARNING.

     @param Filter Sets the log filter level. See #LOG_FILTER_TYPE.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLogFilter( int64 Filter );

   /** Sets the log file size (KB).

    The SDK has two log files, each with a default size of 512 KB. If you set @p FileSizeInKBytes as 1024 KB, the SDK outputs log files with a total maximum size of 2 MB. If the total size of the log files exceed the set value, the new output log files overwrite the old output log files.

    @param FileSizeInKBytes The SDK log file size (KB).
    @return
    - 0: Success.
    - <0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLogFileSize( int64 FileSizeInKBytes );

   /** Enables the \ref OnAudioVolumeIndicationDelegate "OnAudioVolumeIndication" callback at a set time interval to report on which users are speaking and the speakers' volume.

     Once this method is enabled, the SDK returns the volume indication in the \ref OnAudioVolumeIndicationDelegate "OnAudioVolumeIndication" callback at the set time interval, whether or not any user is speaking in the channel.

     @param Interval Sets the time interval between two consecutive volume indications:
     - &le; 0: Disables the volume indication.
     - > 0: Time interval (ms) between two consecutive volume indications. We recommend setting @p Interval &gt; 200 ms. Do not set @p Interval &lt; 10 ms, or the *OnAudioVolumeIndication* callback will not be triggered.
     @param Smooth  Smoothing factor sets the sensitivity of the audio volume indicator. The value ranges between 0 and 10. The greater the value, the more sensitive the indicator. The recommended value is 3.
     @param ReportVad Enables or disables voice activity detection of the local user:
     - true enables the voice activity detection.
     - false disables the voice activity detection.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int EnableAudioVolumeIndication( int Interval, int Smooth, bool ReportVad );

   /** Sets the external audio source.

    @param Enabled Sets whether to enable/disable the external audio source:
    - true: Enables the external audio source.
    - false: (Default) Disables the external audio source.
    @param SampleRate Sets the sample rate of the external audio source, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
    @param Channels Sets the audio channels of the external audio source (two channels maximum).
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetExternalAudioSource( bool Enabled, int SampleRate, int Channels );

   /** Sets the external audio sink.

     If you enable the external audio sink, you can pull the audio frame by periodically calling the \ref  agora::media::IMediaEngine::pullAudioFrame "pullAudioFrame" method.

     @param Enabled
     - true: Enables the external audio sink.
     - false: Disables the external audio sink.
     @param SampleRate Sets the sample rate of the external audio sink, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz. 
     @param Channels Sets the audio channels of the external audio sink (two channels maximum).

     @note Enabling the external audio sink disables the "Raw Audio Data" method, and the application will not retrieve the audio frame from the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetExternalAudioSink( bool Enabled, int SampleRate, int Channels );

   /** Sets the mixed audio format for the \ref agora::media::IAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame" callback.

    @param SampleRate Sets the sample rate (@p samplesPerSec) returned in the *OnMixedAudioFrame* callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
    @param SamplesPerCall Sets the sample points (@p samples) returned in the *OnMixedAudioFrame* callback. @p SamplesPerCall is usually set as 1024 for stream pushing.

    SamplesPerCall = (int)(SampleRate &times; SampleInterval), where SampleInterval &ge; 0.01 in seconds.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetMixedAudioFrameParameters( int SampleRate, int SamplesPerCall );

   /** Adjusts the recording volume.

    @param Volume Recording volume. The value ranges between 0 and 400:
    - 0: Mute.
    - 100: Original volume.
    - 400: (Maximum) Four times the original volume with signal clipping protection.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int AdjustRecordingSignalVolume( int Volume );

   /** Adjusts the playback volume of the voice.

     @param Volume The playback volume of the voice. The value ranges between 0 and 400:
     - 0: Mute.
     - 100: Original volume.
     - 400: (Maximum) Four times the original volume with signal clipping protection.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int AdjustPlaybackSignalVolume( int Volume );

   /** Switches to a different channel.

     This method allows the audience of a Live-broadcast channel to switch to a different channel.
    
     After the user successfully switches to another channel, the \ref OnLeaveChannelDelegate "OnLeaveChannel" and \ref OnJoinChannelSuccessDelegate "OnJoinChannelSuccess" callbacks are triggered to indicate that the user has left the original channel and joined a new one.
    
     @note This method applies to the audience role in a Live-broadcast channel only.
    
     @param Token The token generated at your server:
     - For low-security requirements: You can use the temporary token generated in Dashboard. For details, see [Get a temporary token](https://docs.agora.io/en/Agora%20Platform/token?platfor%20*%20m=All%20Platforms#get-a-temporary-token).
     - For high-security requirements: Use the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Agora%20Platform/token?platfor%20*%20m=All%20Platforms#get-a-token).
     @param ChannelId Unique channel name for the AgoraRTC session in the string format. The string length must be less than 64 bytes. Supported character scopes are:
     - The 26 lowercase English letters: a to z.
     - The 26 uppercase English letters: A to Z.
     - The 10 numbers: 0 to 9.
     - The space.
     - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".",
     ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
    
     @return
     - 0: Success.
     - <0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SwitchChannel( const FString& Token, const FString& ChannelId );

   /** Gets a new token when the current token expires after a period of time.

     The *Token* expires after a period of time once the token schema is enabled when:

     - The SDK triggers the \ref OnTokenPrivilegeWillExpireDelegate "OnTokenPrivilegeWillExpire" callback, or
     - The \ref OnConnectionStateChangedDelegate "OnConnectionStateChanged" reports CONNECTION_CHANGED_TOKEN_EXPIRED(9).

     The application should call this method to get the new *Token*. Failure to do so will result in the SDK disconnecting from the server.

     @param Token Pointer to the new token.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int RenewToken( const FString& Token );

   /** Registers a user account.

     Once registered, the user account can be used to identify the local user when the user joins the channel.
     After the user successfully registers a user account, the SDK triggers the \ref OnLocalUserRegisteredDelegate "OnLocalUserRegistered" callback on the local client, reporting the user ID and user account of the local user.

     To join a channel with a user account, you can choose either of the following:

     - Call the \ref RegisterLocalUserAccount method to create a user account, and then the \ref JoinChannelWithUserAccount method to join the channel.
     - Call the \ref JoinChannelWithUserAccount method to join the channel.

     The difference between the two is that for the former, the time elapsed between calling the \ref JoinChannelWithUserAccount method and joining the channel is shorter than the latter.

     @note
     - Ensure that you set the `UserAccount` parameter. Otherwise, this method does not take effect.
     - Ensure that the value of the `UserAccount` parameter is unique in the channel.
     - To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account. If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.

     @param AppId AppId App ID of your project.
     @param UserAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
     - The 26 lowercase English letters: a to z.
     - The 26 uppercase English letters: A to Z.
     - The 10 numbers: 0 to 9.
     - The space.
     - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

     @return
     - 0: Success.
     - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int RegisterLocalUserAccount( const FString& AppId, const FString& UserAccount );

   /** Joins the channel with a user account.

     After the user successfully joins the channel, the SDK triggers the following callbacks:

     - The local client: \ref OnLocalUserRegisteredDelegate "OnLocalUserRegistered" and \ref OnJoinChannelSuccessDelegate "OnJoinChannelSuccess".
     The remote client: \ref OnUserJoinedDelegate "OnUserJoined" and \ref OnUserInfoUpdatedDelegate "OnUserInfoUpdated" , if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.

     @note To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account.
     If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.

     @param Token The token generated at your server:
     - For low-security requirements: You can use the temporary token generated at Dashboard. For details, see [Get a temporary token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-temporary-token).
     - For high-security requirements: Set it as the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-token).
     @param ChannelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
      The 26 lowercase English letters: a to z.
     - The 26 uppercase English letters: A to Z.
     - The 10 numbers: 0 to 9.
     - The space.
     - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
     @param UserAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
     - The 26 lowercase English letters: a to z.
     - The 26 uppercase English letters: A to Z.
     - The 10 numbers: 0 to 9.
     - The space.
     - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int JoinChannelWithUserAccount( const FString& Token, const FString& ChannelId, const FString& UserAccount );

   /** Starts playing and mixing the music file.

     This method mixes the specified local audio file with the audio stream from the microphone, or replaces the microphone's audio stream with the specified local audio file. You can choose whether the other user can hear the local audio playback and specify the number of playback loops. This method also supports online music playback.

     When the audio mixing file playback finishes after calling this method, the SDK triggers the \ref OnAudioMixingFinishedDelegate "OnAudioMixingFinished" callback.

     A successful \ref StartAudioMixing method call triggers the \ref OnAudioMixingStateChangedDelegate "OnAudioMixingStateChanged" (PLAY) callback on the local client.

     When the audio mixing file playback finishes, the SDK triggers the \ref OnAudioMixingStateChangedDelegate "OnAudioMixingStateChanged" (STOPPED) callback on the local client.
     @note
     - Call this method when you are in a channel.
     - If the local audio mixing file does not exist, or if the SDK does not support the file format or cannot access the music file URL, the SDK returns WARN_AUDIO_MIXING_OPEN_ERROR = 701.

     @param FilePath Pointer to the absolute path of the local or online audio file to mix. Supported audio formats: 3GP, ASF, ADTS, AVI, MP3, MPEG-4, SAMI, and WAVE. For more information, see [Supported Media Formats in Media Foundation](https://docs.microsoft.com/en-us/windows/desktop/medfound/supported-media-formats-in-media-foundation).
     @param Loopback Sets which user can hear the audio mixing:
     - true: Only the local user can hear the audio mixing.
     - false: Both users can hear the audio mixing.
     @param Replace Sets the audio mixing content:
     - true: Only the specified audio file is published; the audio stream received by the microphone is not published.
     - false: The local audio file is mixed with the audio stream from the microphone.
     @param Cycle Sets the number of playback loops:
     - Positive integer: Number of playback loops.
     - -1: Infinite playback loops.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StartAudioMixing( const FString& FilePath, bool Loopback, bool Replace, int Cycle );

   /** Preloads a specified audio effect file into the memory.

    @note This method does not support online audio effect files.

    To ensure smooth communication, limit the size of the audio effect file. We recommend using this method to preload the audio effect before calling the \ref JoinChannel method.

    Supported audio formats: mp3, aac, m4a, 3gp, and wav.

    @param SoundId ID of the audio effect. Each audio effect has a unique ID.
    @param FilePath Pointer to the absolute path of the audio effect file.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int PreloadEffect( int SoundId, const FString& FilePath );

   /** Plays a specified local or online audio effect file.

     This method allows you to set the loop count, pitch, pan, and gain of the audio effect file, as well as whether the remote user can hear the audio effect.

     To play multiple audio effect files simultaneously, call this method multiple times with different soundIds and filePaths. We recommend playing no more than three audio effect files at the same time.

     When the audio effect file playback finishes, the SDK returns the \ref OnAudioEffectFinishedDelegate "OnAudioEffectFinished" callback.

     @param SoundId ID of the specified audio effect. Each audio effect has a unique ID.

     @note
     - If the audio effect is preloaded into the memory through the \ref PreloadEffect "PreloadEffect" method, the value of @p SoundId must be the same as that in the *PreloadEffect* method.
     - Playing multiple online audio effect files simultaneously is not supported on macOS and Windows.

     @param FilePath The absolute path to the local audio effect file or the URL of the online audio effect file.
     @param LoopCount Sets the number of times the audio effect loops:
     - 0: Play the audio effect once.
     - 1: Play the audio effect twice.
     - -1: Play the audio effect in an indefinite loop until the \ref StopEffect or \ref StopAllEffects method is called.
     @param Pitch Sets the pitch of the audio effect. The value ranges between 0.5 and 2. The default value is 1 (no change to the pitch). The lower the value, the lower the pitch.
     @param Pan Sets the spatial position of the audio effect. The value ranges between -1.0 and 1.0:
     - 0.0: The audio effect displays ahead.
     - 1.0: The audio effect displays to the right.
     - -1.0: The audio effect displays to the left.
     @param Gain  Sets the volume of the audio effect. The value ranges between 0.0 and 100.0 (default). The lower the value, the lower the volume of the audio effect.
     @param Publish Sets whether or not to publish the specified audio effect to the remote stream:
     - true: The locally played audio effect is published to the Agora Cloud and the remote users can hear it.
     - false: The locally played audio effect is not published to the Agora Cloud and the remote users cannot hear it.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int PlayEffect( int SoundId, const FString& FilePath, int LoopCount, float Pitch, float Pan, int Gain, bool Publish );

   /** Specifies an SDK output log file.

     The log file records all SDK operations during runtime. If it does not exist, the SDK creates one.

     @note
     - The default log file is located at: "C:\Users\<user_name>\AppData\Local\Agora\<process_name>".
     - Ensure that you call this method immediately after calling the \ref Initialize method, otherwise the output log may not be complete.

     @param FilePath File path of the log file. The string of the log file is in UTF-8.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLogFile( const FString& FilePath );

   /** Allows a user to rate a call after the call ends.

    @param CallId Pointer to the ID of the call, retrieved from the \ref GetCallId method.
    @param Rating  Rating of the call. The value is between 1 (lowest score) and 5 (highest score). If you set a value out of this range, the #ERR_INVALID_ARGUMENT (2) error returns.
    @param Description (Optional) Pointer to the description of the rating, with a string length of less than 800 bytes.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int Rate( const FString& CallId, int Rating, const FString& Description );

   /** Allows a user to complain about the call quality after a call ends.

    @param CallId Pointer to the ID of the call, retrieved from the \ref GetCallId method.
    @param Description (Optional) Pointer to the description of the complaint, with a string length of less than 800 bytes.

    @return
    - 0: Success.
    - < 0: Failure.

    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int Complain( const FString& CallId, const FString& Description );

   /** Retrieves the warning or error description.

    @return code #WARN_CODE_TYPE or #ERROR_CODE_TYPE returned in the \ref OnWarningDelegate "OnWarning" or \ref OnErrorDelegate "OnError" callback.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      FString GetErrorDescription( int Code );

   /** Sends data stream messages to all users in a channel.

    The SDK has the following restrictions on this method:
    - Up to 30 packets can be sent per second in a channel with each packet having a maximum size of 1 kB.
    - Each client can send up to 6 kB of data per second.
    - Each user can have up to five data streams simultaneously.

    A successful \ref SendStreamMessage method call triggers the \ref OnStreamMessageDelegate "OnStreamMessage" callback on the remote client, from which the remote user gets the stream message.

    A failed \ref SendStreamMessage method call triggers the \ref OnStreamMessageErrorDelegate "OnStreamMessage" callback on the remote client.
    @note This method applies only to the Communication profile or to the hosts in the Live-broadcast profile. If an audience in the Live-broadcast profile calls this method, the audience may be switched to a host.

    @param StreamId ID of the sent data stream, returned in the \ref CreateDataStream method.
    @param Data Pointer to the sent data.
    @param Length Length of the sent data.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SendStreamMessage( int StreamId, const FString& Data, int Length );

   /** Publishes the local stream to a specified CDN live RTMP address.  (CDN live only.)

     The SDK returns the result of this method call in the \ref OnStreamPublishedDelegate "OnStreamPublished" callback.

     The \ref AddPublishStreamUrl method call triggers the \ref OnRtmpStreamingStateChangedDelegate "OnRtmpStreamingStateChanged" callback on the local client to report the state of adding a local stream to the CDN.
     @note
     - Ensure that the user joins the channel before calling this method.
     - This method adds only one stream RTMP URL address each time it is called.
     - The RTMP URL address must not contain special characters, such as Chinese language characters.
     - This method applies to Live Broadcast only.

     @param Url The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes.
     @param TranscodingEnabled Sets whether transcoding is enabled/disabled:
     - true: Enable transcoding. To [transcode](https://docs.agora.io/en/Agora%20Platform/terms?platform=All%20Platforms#transcoding) the audio or video streams when publishing them to CDN live, often used for combining the audio and video streams of multiple hosts in CDN live.
     - false: Disable transcoding.

     @return
     - 0: Success.
     - < 0: Failure.
          - #ERR_INVALID_ARGUMENT (2): The RTMP URL address is NULL or has a string length of 0.
          - #ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the stream.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int AddPublishStreamUrl( const FString& Url, bool TranscodingEnabled );

   /** Removes an RTMP stream from the CDN. (CDN live only.)

     This method removes the RTMP URL address (added by the \ref AddPublishStreamUrl method) from a CDN live stream. The SDK returns the result of this method call in the \ref OnStreamUnpublishedDelegate "OnStreamUnpublished" callback.

     The \ref RemovePublishStreamUrl method call triggers the \ref OnRtmpStreamingStateChangedDelegate "OnRtmpStreamingStateChanged" callback on the local client to report the state of removing an RTMP stream from the CDN.
     @note
     - This method removes only one RTMP URL address each time it is called.
     - The RTMP URL address must not contain special characters, such as Chinese language characters.
     - This method applies to Live Broadcast only.

     @param Url The RTMP URL address to be removed. The maximum length of this parameter is 1024 bytes.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int RemovePublishStreamUrl( const FString& Url );

   /** Removes the voice or video stream URL address from a live broadcast.

     This method removes the URL address (added by the \ref AddInjectStreamUrl method) from the live broadcast.

     @note If this method is called successfully, the SDK triggers the \ref OnUserOfflineDelegate "OnUserOffline" callback and returns a stream uid of 666.

     @param Url Pointer to the URL address of the added stream to be removed.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int RemoveInjectStreamUrl( const FString& Url );

   /** Stops/Resumes receiving a specified remote user's audio stream.

    @note If you called the \ref MuteAllRemoteAudioStreams method and set @p Mute as @p true to stop receiving all remote users' audio streams, call the *MuteAllRemoteAudioStreams* method and set @p Mute as @p false before calling this method. The *MuteAllRemoteAudioStreams* method sets all remote audio streams, while the *MuteRemoteAudioStream* method sets a specified remote audio stream.

    @param UserId User ID of the specified remote user sending the audio.
    @param Mute Sets whether to receive/stop receiving a specified remote user's audio stream:
    - true: Stops receiving the specified remote user's audio stream.
    - false: (Default) Receives the specified remote user's audio stream.

    @return
    - 0: Success.
    - < 0: Failure.

    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int MuteRemoteAudioStream( int64 UserId, bool Mute );

   /** Stops/Resumes receiving the video stream from a specified remote user.

    @note If you called the \ref MuteAllRemoteVideoStreams method and set @p Mute as @p true to stop receiving all remote video streams, call the *MuteAllRemoteVideoStreams* method and set @p Mute as @p false before calling this method.

    @param UserId User ID of the specified remote user.
    @param Mute Sets whether to stop/resume receiving the video stream from a specified remote user:
    - true: Stop receiving the specified remote user's video stream.
    - false: (Default) Receive the specified remote user's video stream.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int MuteRemoteVideoStream( int64 UserId, bool Mute );

   /** Sets the sound position and gain of a remote user.

     When the local user calls this method to set the sound position of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of space. This method applies to massively multiplayer online games, such as Battle Royale games.

     @note
     - For this method to work, enable stereo panning for remote users by calling the \ref EnableSoundPositionIndication method before joining a channel.
     - This method requires hardware support. For the best sound positioning, we recommend using a stereo speaker.

     @param UserId The ID of the remote user.
     @param Pan The sound position of the remote user. The value ranges from -1.0 to 1.0:
     - 0.0: the remote sound comes from the front.
     - -1.0: the remote sound comes from the left.
     - 1.0: the remote sound comes from the right.
     @param Gain Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user). The smaller the value, the less the gain.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetRemoteVoicePosition( int64 UserId, float Pan, float Gain );

   /** Sets the camera capture configuration.

     For a video call or live broadcast, generally the SDK controls the camera output parameters. When the default camera capturer settings do not meet special requirements or cause performance problems, we recommend using this method to set the camera capturer configuration:

     - If the resolution or frame rate of the captured raw video data are higher than those set by \ref SetVideoEncoderConfiguration , processing video frames requires extra CPU and RAM usage and degrades performance. We recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1 to avoid such problems.
     - If you do not need local video preview or are willing to sacrifice preview quality, we recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1 to optimize CPU and RAM usage.
     - If you want better quality for the local video preview, we recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2.

     @note Call this method before enabling the local camera. That said, you can call this method before calling \ref JoinChannel , \ref EnableVideo , or \ref EnableLocalVideo , depending on which method you use to turn on your local camera.

     @param Config Sets the camera capturer configuration. See FCameraCapturerConfiguration.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetCameraCapturerConfiguration( const FCameraCapturerConfiguration& Config );

   /** Sets the role of the user, such as a host or an audience (default), before joining a channel in a live broadcast.

     This method can be used to switch the user role in a live broadcast after the user joins a channel.

     In the Live Broadcast profile, when a user switches user roles after joining a channel, a successful \ref SetClientRole method call triggers the following callbacks:
     - The local client: \ref OnClientRoleChangedDelegate "OnClientRoleChanged"
     - The remote client: \ref OnUserJoinedDelegate "OnUserJoined" or \ref OnUserOfflineDelegate "OnUserOffline" (BECOME_AUDIENCE)

     @note
     This method applies only to the Live-broadcast profile.

     @param Role Sets the role of the user. See #ECLIENT_ROLE_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetClientRole( ECLIENT_ROLE_TYPE Role );

   /** Prioritizes a remote user's stream.

    Use this method with the \ref SetRemoteSubscribeFallbackOption method. If the fallback function is enabled for a subscribed stream, the SDK ensures the high-priority user gets the best possible stream quality.

    @note The Agora SDK supports setting @p userPriority as high for one user only.

    @param  UserId  The ID of the remote user.
    @param  UserPriority Sets the priority of the remote user. See #EPRIORITY_TYPE.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetRemoteUserPriority( int64 UserId, EPRIORITY_TYPE UserPriority );

   /** Sets the audio parameters and application scenarios.

     @note
     - The *SetAudioProfile* method must be called before the \ref JoinChannel method.
     - In the Communication and Live-broadcast profiles, the bitrate may be different from your settings due to network self-adaptation.
     - In scenarios involving music education, we recommend setting profile as #AUDIO_PROFILE_MUSIC_HIGH_QUALITY (4) and scenario as #AUDIO_SCENARIO_GAME_STREAMING (3).

     @param  Profile Sets the sample rate, bitrate, encoding mode, and the number of channels. See #AUDIO_PROFILE_TYPE.
     @param  Scenario Sets the audio application scenario. See #EAUDIO_SCENARIO_TYPE. Under different audio scenarios, the device uses different volume tracks, i.e. either the in-call volume or the media volume. For details, see [What is the difference between the in-call volume and the media volume?](https://docs.agora.io/en/faq/system_volume).

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetAudioProfile( EAUDIO_PROFILE_TYPE Profile, EAUDIO_SCENARIO_TYPE Scenario );

   /** Sets the remote user's video stream type received by the local user when the remote user sends dual streams.

     This method allows the application to adjust the corresponding video-stream type based on the size of the video window to reduce the bandwidth and resources.

     - If the remote user enables the dual-stream mode by calling the \ref EnableDualStreamMode method, the SDK receives the high-stream video by default.
     - If the dual-stream mode is not enabled, the SDK receives the high-stream video by default.

     The method result returns in the \ref OnApiCallExecutedDelegate "OnApiCallExecuted" callback. The SDK receives the high-stream video by default to reduce the bandwidth. If needed, users may use this method to switch to the low-stream video.
     By default, the aspect ratio of the low-stream video is the same as the high-stream video. Once the resolution of the high-stream video is set, the system automatically sets the resolution, frame rate, and bitrate of the low-stream video.

     @param UserId ID of the remote user sending the video stream.
     @param StreamType  Sets the video-stream type. See #EREMOTE_VIDEO_STREAM_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetRemoteVideoStreamType( int64 UserId, EREMOTE_VIDEO_STREAM_TYPE StreamType );

   /** Sets the default video-stream type for the video received by the local user when the remote user sends dual streams.

     - If the dual-stream mode is enabled by calling the \ref EnableDualStreamMode method, the user receives the high-stream video by default. The @p SetRemoteDefaultVideoStreamType method allows the application to adjust the corresponding video-stream type according to the size of the video window, reducing the bandwidth and resources.
     - If the dual-stream mode is not enabled, the user receives the high-stream video by default.

     The result after calling this method is returned in the \ref OnApiCallExecutedDelegate "OnApiCallExecuted" callback. The Agora SDK receives the high-stream video by default to reduce the bandwidth. If needed, users can switch to the low-stream video through this method.

     @param StreamType Sets the default video-stream type. See #EREMOTE_VIDEO_STREAM_TYPE.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetRemoteDefaultVideoStreamType( EREMOTE_VIDEO_STREAM_TYPE StreamType );

   /** Sets the local voice equalization effect.

     @param BandFrequency Sets the band frequency. The value ranges between 0 and 9, representing the respective 10-band center frequencies of the voice effects, including 31, 62, 125, 500, 1k, 2k, 4k, 8k, and 16k Hz. See #EAUDIO_EQUALIZATION_BAND_FREQUENCY.
     @param BandGain  Sets the gain of each band in dB. The value ranges between -15 and 15.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLocalVoiceEqualization( EAUDIO_EQUALIZATION_BAND_FREQUENCY BandFrequency, int BandGain );

   /**  Sets the local voice reverberation.

  v2.4.0 adds the \ref SetLocalVoiceReverbPreset method, a more user-friendly method for setting the local voice reverberation. You can use this method to set the local reverberation effect, such as pop music, R&B, rock music, and hip-hop.

  @param ReverbKey Sets the reverberation key. See #EAUDIO_REVERB_TYPE.
  @param Value Sets the value of the reverberation key.

  @return
  - 0: Success.
  - < 0: Failure.
  */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLocalVoiceReverb( EAUDIO_REVERB_TYPE ReverbKey, int Value );

   /** Sets the local voice changer option.

    @note Do not use this method together with the \ref SetLocalVoiceReverbPreset method, because the method called later overrides the one called earlier.

    @param VoiceChanger Sets the local voice changer option. See #EVOICE_CHANGER_PRESET.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLocalVoiceChanger( EVOICE_CHANGER_PRESET VoiceChanger );

   /** Sets the preset local voice reverberation effect.

     @note
     - Do not use this method together with \ref SetLocalVoiceReverb .
     - Do not use this method together with the \ref SetLocalVoiceChanger method, because the method called later overrides the one called earlier.

     @param ReverbPreset Sets the preset audio reverberation configuration. See #EAUDIO_REVERB_PRESET.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLocalVoiceReverbPreset( EAUDIO_REVERB_PRESET ReverbPreset );

   /** Sets the local video display mode.

    This method can be called multiple times during a call to change the display mode.

    @param RenderMode  Sets the local video display mode. See #ERENDER_MODE_TYPE.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLocalRenderMode( ERENDER_MODE_TYPE RenderMode );

   /** Sets the video display mode of a specified remote user.

     This method can be called multiple times during a call to change the display mode.

     @param UserId ID of the remote user.
     @param RenderMode  Sets the video display mode. See #ERENDER_MODE_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetRemoteRenderMode( int64 UserId, ERENDER_MODE_TYPE RenderMode );

   /** Sets the local video mirror mode.

     You must call this method before calling the \ref StartPreview method, otherwise the mirror mode will not work.

     @param MirrorMode Sets the local video mirror mode. See #EVIDEO_MIRROR_MODE_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLocalVideoMirrorMode( EVIDEO_MIRROR_MODE_TYPE MirrorMode );

   /** Sets the audio recording format for the \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" callback.

     @param RecordingSampleRate Sets the sample rate (@p samplesPerSec) returned in the *onRecordAudioFrame* callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
     @param Channel Sets the number of audio channels (@p channels) returned in the *onRecordAudioFrame* callback:
     - 1: Mono
     - 2: Stereo
     @param UseMode Sets the use mode (see #ERAW_AUDIO_FRAME_OP_MODE_TYPE) of the *onRecordAudioFrame* callback.
     @param SamplesPerCall Sets the sample points (@p samples) returned in the *onRecordAudioFrame* callback. @p SamplesPerCall is usually set as 1024 for stream pushing.

     SamplesPerCall = (int)(samplesPerSec &times; SampleInterval &times; numChannels), where SampleInterval &ge; 0.01 in seconds.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetRecordingAudioFrameParameters( int RecordingSampleRate, int Channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE UseMode, int SamplesPerCall );

   /** Sets the audio playback format for the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback.

     @param PlaybackSampleRate Sets the sample rate (@p samplesPerSec) returned in the *onPlaybackAudioFrame* callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
     @param Channel Sets the number of channels (@p channels) returned in the *onPlaybackAudioFrame* callback:
     - 1: Mono
     - 2: Stereo
     @param UseMode Sets the use mode (see #ERAW_AUDIO_FRAME_OP_MODE_TYPE) of the *onPlaybackAudioFrame* callback.
     @param SamplesPerCall Sets the sample points (*samples*) returned in the *onPlaybackAudioFrame* callback. @p SamplesPerCall is usually set as 1024 for stream pushing.

     SamplesPerCall = (int)(samplesPerSec &times; SampleInterval &times; numChannels), where SampleInterval &ge; 0.01 in seconds.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetPlaybackAudioFrameParameters( int PlaybackSampleRate, int Channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE UseMode, int SamplesPerCall );

   /** Sets the fallback option for the locally published video stream based on the network conditions.

    The default setting for @p Option is #STREAM_FALLBACK_OPTION_DISABLED, where there is no fallback behavior for the locally published video stream when the uplink network conditions are poor.

    If *Option* is set as #STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK will:

    - Disable the upstream video but enable audio only when the network conditions worsen and cannot support both video and audio.
    - Re-enable the video when the network conditions improve.

    When the locally published video stream falls back to audio only or when the audio-only stream switches back to the video, the SDK triggers the \ref OnLocalPublishFallbackToAudioOnlyDelegate "OnLocalPublishFallbackToAudioOnly" callback.

    @note Agora does not recommend using this method for CDN live streaming, because the remote CDN live user will have a noticeable lag when the locally publish stream falls back to audio-only.

    @param  Option Sets the fallback option for the locally published video stream. See #ESTREAM_FALLBACK_OPTIONS.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLocalPublishFallbackOption( ESTREAM_FALLBACK_OPTIONS Option );

   /** Sets the fallback option for the remotely subscribed video stream based on the network conditions.

     The default setting for @p Option is #STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW, where the remotely subscribed video stream falls back to the low-stream video (low resolution and low bitrate) under poor downlink network conditions.

     If *Option* is set as #STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK automatically switches the video from a high-stream to a low-stream, or disables the video when the downlink network conditions cannot support both audio and video to guarantee the quality of the audio. The SDK monitors the network quality and restores the video stream when the network conditions improve.

     When the remotely subscribed video stream falls back to audio only or when the audio-only stream switches back to the video stream, the SDK triggers the \ref OnRemoteSubscribeFallbackToAudioOnlyDelegate "OnRemoteSubscribeFallbackToAudioOnly" callback.

     @param  Option  Sets the fallback option for the remotely subscribed video stream. See #ESTREAM_FALLBACK_OPTIONS.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetRemoteSubscribeFallbackOption( ESTREAM_FALLBACK_OPTIONS Option );

   /** Starts an audio recording.

    The SDK allows recording during a call. Supported formats:

    - .wav: Large file size with high fidelity.
    - .aac: Small file size with low fidelity.

    Ensure that the directory to save the recording file exists and is writable.
    This method is usually called after the \ref JoinChannel method.
    The recording automatically stops when the \ref LeaveChannel method is called.

    @param FilePath Pointer to the absolute file path of the recording file. The string of the file name is in UTF-8.
    @param SampleRate Sample rate of the recorded audio, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
    @param Quality Sets the audio recording quality. See #EAUDIO_RECORDING_QUALITY_TYPE.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StartAudioRecording( const FString& FilePath, int SampleRate, EAUDIO_RECORDING_QUALITY_TYPE Quality );

   /** Gets the current connection state of the SDK.

    @return #ECONNECTION_STATE_TYPE.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      ECONNECTION_STATE_TYPE GetConnectionState();

   /** Gets the user information by passing in the user account.

     After a remote user joins the channel, the SDK gets the user ID and user account of the remote user, caches them
     in a mapping table object (`FAgoraUserInfo`), and triggers the \ref OnUserInfoUpdatedDelegate "OnUserInfoUpdated" callback on the local client.

     After receiving the o\ref OnUserInfoUpdatedDelegate "OnUserInfoUpdated" callback, you can call this method to get the user ID of the
     remote user from the `FAgoraUserInfo` object by passing in the user account.

     @param UserAccount The user account of the user. Ensure that you set this parameter.
     @param UserInfo A FAgoraUserInfo object that identifies the user:
     - Input: A FAgoraUserInfo object.
     - Output: A FAgoraUserInfo object that contains the user account and user ID of the user.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int GetUserInfoByUserAccount( const FString& UserAccount, FAgoraUserInfo& UserInfo );

   /** Gets the user information by passing in the user ID.

    After a remote user joins the channel, the SDK gets the user ID and user account of the remote user,
    caches them in a mapping table object (`FAgoraUserInfo`), and triggers the \ref OnUserInfoUpdatedDelegate "OnUserInfoUpdated" callback on the local client.

    After receiving the \ref OnUserInfoUpdatedDelegate "OnUserInfoUpdated" callback, you can call this method to get the user account of the remote user
    from the `FAgoraUserInfo` object by passing in the user ID.

    @param UserId The user ID of the remote user. Ensure that you set this parameter.
    @param UserInfo A FAgoraUserInfo object that identifies the user:
    - Input: A FAgoraUserInfo object.
    - Output: A FAgoraUserInfo object that contains the user account and user ID of the user.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int GetUserInfoByUid( int64 UserId, FAgoraUserInfo& UserInfo );

   /** Sets the local video view and configures the video display settings on the local machine.

     The application calls this method to bind each video window (view) of the local video streams and configures the video display settings. Call this method after initialization to configure the local video display settings before joining a channel. The binding is still valid after the user leaves the channel, which means that the window still displays. To unbind the view, set the *view* in FVideoCanvas to NULL.

     @param Canvas Pointer to the local video view and settings. See FVideoCanvas.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetupLocalVideo( const FVideoCanvas& Canvas );

   /** Sets the remote video view.

    This method binds the remote user to the video display window (sets the view for the remote user by the specified uid in FVideoCanvas).

    The application specifies the uid of the remote video in this method before the remote user joins the channel.

    If the remote uid is unknown to the application, set it after the application receives the \ref OnUserJoinedDelegate "OnUserJoined" callback.

    If the Video Recording function is enabled, the Video Recording Service joins the channel as a dummy client, causing other clients to also receive the \ref OnUserJoinedDelegate "OnUserJoined" callback. Do not bind the dummy client to the application view because the dummy client does not send any video streams. If your application does not recognize the dummy client, bind the remote user to the view when the SDK triggers the \ref OnFirstRemoteVideoDecodedDelegate "OnFirstRemoteVideoDecoded" callback.

    To unbind the remote user from the view, set the view in VideoCanvas to NULL. Once the remote user leaves the channel, the SDK unbinds the remote user.

    @param Canvas Pointer to the remote video view and settings. See FVideoCanvas.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetupRemoteVideo( const FVideoCanvas& Canvas );

   /** Sets the playback position of the music file to a different starting position (the default plays from the beginning).

     @param Pos The playback starting position (ms) of the music file.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetAudioMixingPosition( int Pos );

   /** Starts the last-mile network probe test.

   This method starts the last-mile network probe test before joining a channel to get the uplink and downlink last-mile network statistics, including the bandwidth, packet loss, jitter, and round-trip time (RTT).

   Call this method to check the uplink network quality before users join a channel or before an audience switches to a host.
   Once this method is enabled, the SDK returns the following callbacks:
   - \ref OnLastmileQualityDelegate "OnLastmileQuality": the SDK triggers this callback within two seconds depending on the network conditions. This callback rates the network conditions and is more closely linked to the user experience.
   - \ref OnLastmileProbeResultDelegate "OnLastmileProbeResult" : the SDK triggers this callback within 30 seconds depending on the network conditions. This callback returns the real-time statistics of the network conditions and is more objective.

   @note
   - This method consumes extra network traffic and may affect communication quality. We do not recommend calling this method together with EnableLastmileTest.
   - Do not call other methods before receiving the \ref OnLastmileQualityDelegate "OnLastmileQuality" and \ref OnLastmileProbeResultDelegate "OnLastmileProbeResult" callbacks. Otherwise, the callbacks may be interrupted.
   - In the Live-broadcast profile, a host should not call this method after joining a channel.

   @param ProbeConfig Sets the configurations of the last-mile network probe test. See FLastmileProbeConfig.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StartLastmileProbeTest( const FLastmileProbeConfig& ProbeConfig );

   /** Creates a data stream.

    Each user can create up to five data streams during the lifecycle of the RtcEngine.

    @note Set both the @p Reliable and @p Ordered parameters to true or false. Do not set one as true and the other as false.

    @param Id Pointer to the ID of the created data stream.
    @param Reliable Sets whether or not the recipients are guaranteed to receive the data stream from the sender within five seconds:
    - true: The recipients receive the data stream from the sender within five seconds. If the recipient does not receive the data stream within five seconds, an error is reported to the application.
    - false: There is no guarantee that the recipients receive the data stream within five seconds and no error message is reported for any delay or missing data stream.
    @param Ordered Sets whether or not the recipients receive the data stream in the sent order:
    - true: The recipients receive the data stream in the sent order.
    - false: The recipients do not receive the data stream in the sent order.

    @return
    - Returns 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int CreateDataStream( int& Id, bool Reliable, bool Ordered );

   /** Sets the video layout and audio settings for CDN live. (CDN live only.)
     @note This method applies to Live Broadcast only.

     @param Transcoding Sets the CDN live audio/video transcoding settings. See FLiveTranscoding.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetLiveTranscoding( const FLiveTranscoding& Transcoding );

   /** Adds a watermark image to the local video.

    This method adds a PNG watermark image to the local video in a live broadcast. Once the watermark image is added, all the audience in the channel (CDN audience included),
    and the recording device can see and capture it. Agora supports adding only one watermark image onto the local video, and the newly watermark image replaces the previous one.

    The watermark position depends on the settings in the \ref SetVideoEncoderConfiguration method:
    - If the orientation mode of the encoding video is #ORIENTATION_MODE_FIXED_LANDSCAPE, or the landscape mode in #ORIENTATION_MODE_ADAPTIVE, the watermark uses the landscape orientation.
    - If the orientation mode of the encoding video is #ORIENTATION_MODE_FIXED_PORTRAIT, or the portrait mode in #ORIENTATION_MODE_ADAPTIVE, the watermark uses the portrait orientation.
    - When setting the watermark position, the region must be less than the dimensions set in the `SetVideoEncoderConfiguration` method. Otherwise, the watermark image will be cropped.

    @note
    - Ensure that you have called the `EnableVideo` method to enable the video module before calling this method.
    - If you only want to add a watermark image to the local video for the audience in the CDN live broadcast channel to see and capture, you can call this method or the `SetLiveTranscoding` method.
    - This method supports adding a watermark image in the PNG file format only. Supported pixel formats of the PNG image are RGBA, RGB, Palette, Gray, and Alpha_gray.
    - If the dimensions of the PNG image differ from your settings in this method, the image will be cropped or zoomed to conform to your settings.
    - If you have enabled the local video preview by calling the `StartPreview` method, you can use the `visibleInPreview` member in the FWatermarkOptions class to set whether or not the watermark is visible in preview.
    - If you have mirrored the local video by calling the `SetLocalVideoMirrorMode` method, the watermark image in preview is also mirrored.

    @param WatermarkUrl The local file path of the watermark image to be added. This method supports adding a watermark image from the local absolute or relative file path.
    @param Options Pointer to the watermark's options to be added. See FWatermarkOptions for more infomation.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int AddVideoWatermark( const FString& WatermarkUrl, const FWatermarkOptions& Options );

   /** Enables/Disables image enhancement and sets the options.

   @note This method is for Android and iOS only.

   @param Enabled Sets whether or not to enable image enhancement:
   - true: enables image enhancement.
   - false: disables image enhancement.
   @param Options Sets the image enhancement option. See FBeautyOptions.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int SetBeautyEffectOptions( bool Enabled, FBeautyOptions Options );

   /** Adds a voice or video stream URL address to a live broadcast.

    The \ref OnStreamPublishedDelegate "OnStreamPublished" callback returns the inject status. If this method call is successful, the server pulls the voice or video stream and injects it into a live channel. This is applicable to scenarios where all audience members in the channel can watch a live show and interact with each other.

     @note
     - Contact support@agora.io to enable the CDN streaming function before calling this method.
     - This method applies to the Native SDK v2.4.1 and later.

     The \ref AddInjectStreamUrl method call triggers the following callbacks:
    - The local client:
      - \ref OnStreamInjectedStatusDelegate "OnStreamInjectedStatus" , with the state of the injecting the online stream.
      - \ref OnUserJoinedDelegate "OnUserJoined" (uid: 666), if the method call is successful and the online media stream is injected into the channel.
    - The remote client:
      - \ref OnUserJoinedDelegate "OnUserJoined" (uid: 666), if the method call is successful and the online media stream is injected into the channel.

     @param Url Pointer to the URL address to be added to the ongoing live broadcast. Valid protocols are RTMP, HLS, and FLV.
     - Supported FLV audio codec type: AAC.
     - Supported FLV video codec type: H264 (AVC).
     @param Config Pointer to the FInjectStreamConfig object that contains the configuration of the added voice or video stream.

     @return
     - 0: Success.
     - < 0: Failure.
        - #ERR_INVALID_ARGUMENT (2): The injected URL does not exist. Call this method again to inject the stream and ensure that the URL is valid.
        - #ERR_NOT_READY (3): The user is not in the channel.
        - #ERR_NOT_SUPPORTED (4): The channel profile is not live broadcast. Call the \ref SetChannelProfile method and set the channel profile to live broadcast before calling this method.
        - #ERR_NOT_INITIALIZED (7): The SDK is not initialized. Ensure that the IRtcEngine object is initialized before calling this method.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int AddInjectStreamUrl( const FString& Url, const FInjectStreamConfig& Config );

   /** Starts to relay media streams across channels.
     
      After a successful method call, the SDK triggers the \ref OnChannelMediaRelayStateChangedDelegate "OnChannelMediaRelayStateChanged" and \ref OnChannelMediaRelayEventDelegate "OnChannelMediaRelayEvent" callbacks, and these callbacks return the state and events of the media stream relay.
      - If the \ref OnChannelMediaRelayStateChangedDelegate "OnChannelMediaRelayStateChanged" callback returns #RELAY_STATE_RUNNING (2) and #RELAY_OK (0), and the \ref OnChannelMediaRelayEventDelegate "OnChannelMediaRelayEvent" callback returns #RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL (4), the broadcaster starts sending data to the destination channel.
      - If the \ref OnChannelMediaRelayStateChangedDelegate "OnChannelMediaRelayStateChanged" callback returns #RELAY_STATE_FAILURE (3), an exception occurs during the media stream relay.
     
      @note 
      - Call this method after the \ref JoinChannel method.
      - This method takes effect only when you are a broadcaster in a Live-broadcast channel.
      - After a successful method call, if you want to call this method again, ensure that you call the \ref StopChannelMediaRelay method to quit the current relay.
     
      @param Configuration The configuration of the media stream relay: FChannelMediaRelayConfiguration.
     
      @return
      - 0: Success.
      - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int StartChannelMediaRelay( const FChannelMediaRelayConfiguration& Configuration );

   /** Updates the channels for media stream relay. After a successful \ref StartChannelMediaRelay method call, if you want to relay the media stream to more channels, or leave the current relay channel, you can call the \ref UpdateChannelMediaRelay method.
     
      After a successful method call, the SDK triggers the \ref OnChannelMediaRelayStateChangedDelegate "OnChannelMediaRelayStateChanged" callback with the #RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL (7) state code.
     
      @note
      Call this method after the \ref StartChannelMediaRelay method to update the destination channel.
     
      @param Configuration The media stream relay configuration: FChannelMediaRelayConfiguration.
     
      @return
      - 0: Success.
      - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int UpdateChannelMediaRelay( const FChannelMediaRelayConfiguration& Configuration );

   /** Retrieves the current call ID.

     When a user joins a channel on a client, a @p CallId is generated to identify the call from the client. Feedback methods, such as \ref Rate and \ref Complain, must be called after the call ends to submit feedback to the SDK.

     The \ref Rate and \ref Complain methods require the @p CallId parameter retrieved from the *GetCallId* method during a call. @p CallId is passed as an argument into the \ref Rate and \ref Complain methods after the call ends.

     @param CallId Pointer to the current call ID.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora" )
      int GetCallId( FString& CallId );

   // platform dependent functions

   /** Switches between front and rear cameras.

     @note This method is for Android and iOS only.

     @param Direction Sets the camera to be used:
     - ECAMERA_DIRECTION.CAMERA_REAR: Use the rear camera.
     - ECAMERA_DIRECTION.CAMERA_FRONT: Use the front camera.
     @return
     - 0: Success.
     - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mobile" )
      int SwitchCamera( ECAMERA_DIRECTION Direction );

   /** Sets the default audio playback route.

     This method sets whether the received audio is routed to the earpiece or speakerphone by default before joining a channel.
     If a user does not call this method, the audio is routed to the earpiece by default. If you need to change the default audio route after joining a channel, call the \ref SetEnableSpeakerphone method.

     The default setting for each mode:
     - Voice: Earpiece.
     - Video: Speakerphone. If a user who is in the Communication profile calls the \ref DisableVideo method or if the user calls the \ref MuteLocalVideoStream and \ref MuteAllRemoteVideoStreams methods, the default audio route switches back to the earpiece automatically.
     - Live Broadcast: Speakerphone.
     - Gaming Voice: Speakerphone.

     @note
     - This method is for Android and iOS only.
     - This method only works in audio mode.
     - Call this method before calling the \ref JoinChannel method.
     - Regardless of whether the audio is routed to the speakerphone or earpiece by default, once a headset is plugged in or Bluetooth device is connected, the default audio route changes. The default audio route switches to the earpiece once removing the headset or disconnecting the Bluetooth device.

     @param DefaultToSpeaker Sets the default audio route:
     - true: Speakerphone.
     - false: (Default) Earpiece.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mobile" )
      int SetDefaultAudioRouteToSpeakerphone( bool DefaultToSpeaker );

   /** Enables/Disables the audio playback route to the speakerphone.

      This method sets whether the audio is routed to the speakerphone or earpiece.

      See the default audio route explanation in the \ref SetDefaultAudioRouteToSpeakerphone method and check whether it is necessary to call this method.

      @note
      - This method is for Android and iOS only.
      - Ensure that you have successfully called the \ref JoinChannel method before calling this method.
      - After calling this method, the SDK returns the \ref OnAudioRouteChangedDelegate "OnAudioRouteChanged" callback to indicate the changes.
      - This method does not take effect if a headset is used.

      @param SpeakerOn Sets whether to route the audio to the speakerphone or earpiece:
      - true: Route the audio to the speakerphone.
      - false: Route the audio to the earpiece.

      @return
      - 0: Success.
      - < 0: Failure.
      */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mobile" )
      int SetEnableSpeakerphone( bool SpeakerOn );

   /** Sets the volume of the in-ear monitor.

     @param Volume Sets the volume of the in-ear monitor. The value ranges between 0 and 100 (default).

     @note This method is for Android and iOS only.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mobile" )
      int SetInEarMonitoringVolume( int Volume );

   /** Checks whether the speakerphone is enabled.

     @note This method is for Android and iOS only.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mobile" )
      bool IsSpeakerphoneEnabled();

   /** Sets the audio session’s operational restriction.

     The SDK and the app can both configure the audio session by default. The app may occasionally use other apps or third-party components to manipulate the audio session and restrict the SDK from doing so. This method allows the app to restrict the SDK’s manipulation of the audio session.

     You can call this method at any time to return the control of the audio sessions to the SDK.

     @note
     - This method is for iOS only.
     - This method restricts the SDK’s manipulation of the audio session. Any operation to the audio session relies solely on the app, other apps, or third-party components.

     @param Restriction The operational restriction (bit mask) of the SDK on the audio session. See #EAUDIO_SESSION_OPERATION_RESTRICTION.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|IOS" )
      int SetAudioSessionOperationRestriction( EAUDIO_SESSION_OPERATION_RESTRICTION Restriction );

   /** Shares the whole or part of a screen by specifying the display ID.

    @note This method is for macOS only.

    @param  DisplayId The display ID of the screen to be shared. This parameter specifies which screen you want to share.
    @param  RegionRect (Optional) Sets the relative location of the region to the screen. NIL means sharing the whole screen. See FRectangle. If the specified region overruns the screen, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen.
    @param  CaptureParams Sets the screen sharing encoding parameters. See FScreenCaptureParameters.


    @return
    - 0: Success.
    - < 0: Failure:
       - ERR_INVALID_STATE: the screen sharing state is invalid, probably because another screen or window is being shared. Call \ref StopScreenCapture to stop the current screen sharing.
       - ERR_INVALID_ARGUMENT: the argument is invalid.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mac" )
      int StartScreenCaptureByDisplayId(
         int64 DisplayId,
         const FRectangle& RegionRect,
         const FScreenCaptureParameters& CaptureParams );

   /** Shares the whole or part of a screen by specifying the screen rect.

    @note This method is for Windows only.

    @param  ScreenRect Sets the relative location of the screen to the virtual screen. For information on how to get ScreenRect, see [Share the Screen].
    @param  RegionRect (Optional) Sets the relative location of the region to the screen. NULL means sharing the whole screen. See FRectangle. If the specified region overruns the screen, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen.
    @param  CaptureParams Sets the screen sharing encoding parameters. See FScreenCaptureParameters.

    @return
    - 0: Success.
    - < 0: Failure:
       - ERR_INVALID_STATE: the screen sharing state is invalid, probably because another screen or window is being shared. Call \ref StopScreenCapture to stop the current screen sharing.
       - ERR_INVALID_ARGUMENT: the argument is invalid.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Windows" )
      int StartScreenCaptureByScreenRect(
         const FRectangle& ScreenRect,
         const FRectangle& RegionRect,
         const FScreenCaptureParameters& CaptureParams );

   /** Sets the content hint for screen sharing.

    @note This method is for Windows and macOS only.

    A content hint suggests the type of the content being shared, so that the SDK applies different optimization algorithm to different types of content.

     @param ContentHint Sets the content hint for screen sharing. See EVIDEO_CONTENT_HINT.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mac and Windows" )
   int SetScreenCaptureContentHint( EVIDEO_CONTENT_HINT ContentHint );

   /** Updates the screen sharing parameters.

     @note This method is for Windows and macOS only.

     @param CaptureParams Sets the screen sharing encoding parameters. See FScreenCaptureParameters.

     @return
     - 0: Success.
     - < 0: Failure:
        - ERR_NOT_READY: no screen or windows is being shared.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mac and Windows" )
   int UpdateScreenCaptureParameters( const FScreenCaptureParameters& CaptureParams );


   /** Updates the screen sharing region.

     @note This method is for Windows and macOS only.

     @param  RegionRect Sets the relative location of the region to the screen or window. NULL means sharing the whole screen or window. See FRectangle. If the specified region overruns the screen or window, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen or window.

     @return
     - 0: Success.
     - < 0: Failure:
        - ERR_NOT_READY: no screen or window is being shared.
     */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mac and Windows" )
   int UpdateScreenCaptureRegion( const FRectangle& RegionRect );

   /** Stop screen sharing.

     @note This method is for Windows and macOS only.

     @return
     - 0: Success.
     - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|PlatformDependent|Mac and Windows" )
   int StopScreenCapture();


   ////////////////////////////////////Audio Manager//////////////////////////////////////////////////////////

   /** Returns the set of available audio recording devices
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      TArray<FMediaDevice> GetAudioRecordingDevices();

   /** Returns the set of available audio playback devices
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      TArray<FMediaDevice> GetAudioPlaybackDevices();

   /** Sets the audio recording device using the device ID.

    @param DeviceId Device ID of the audio recording device, retrieved by calling the \ref EnumerateAudioRecordingDevices method.

    @note Plugging or unplugging the audio device does not change the device ID.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int SetCurrentAudioRecordingDevice( const FString& DeviceId );

   /** Sets the audio playback device using the device ID.

   @param DeviceId Device ID of the audio playback device, retrieved by calling the \ref EnumerateAudioPlaybackDevices method.

   @note Plugging or unplugging the audio device does not change the device ID.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int SetCurrentAudioPlaybackDevice( const FString& DeviceId );

   /** Retrieves current audio recording device.

   @param[out] Index The specified device index.
   @param[out] DeviceName Audio device name.
   @param[out] DeviceId Audio device ID.
   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int GetCurrentAudioRecordingDevice( int& Index, FString& DeviceName, FString& DeviceId );

   /** Retrieves current audio playback device.

   @param[out] Index The specified device index.
   @param[out] DeviceName Audio device name.
   @param[out] DeviceId Audio device ID.
   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int GetCurrentAudioPlaybackDevice( int& Index, FString& DeviceName, FString& DeviceId );

   /** Retrieves the total number of audio recording devices.

   @return Number of audio recording devices.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int GetAudioRecordingDeviceCount();

   /** Retrieves the total number of audio playback devices.

   @return Number of audio playback devices.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int GetAudioPlaybackDeviceCount();

   /** Enumerates the audio recording devices.

   Enumerates all audio recording devices in the system.
   Call /ref GetAudioRecordingDevices method to get enumerated devices.
   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int EnumerateAudioRecordingDevices();

   /** Enumerates the audio playback devices.

   Enumerates all audio playback devices in the system. For wireless Bluetooth headset devices with master and slave headsets, the master headset is the playback device.
   Call /ref GetAudioPlaybackDevices method to get enumerated devices.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int EnumerateAudioPlaybackDevices();

   /** Gets the mute state of the application.

    @param[out] Muted Indicates whether the application is muted/unmuted.
    - true: The application is muted.
    - false: The application is not muted.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int IsApplicationMuted( bool& Muted );

   /** Mutes the application.

    @param Muted Sets whether to mute/unmute the application:
    - true: Mute the application.
    - false: Unmute the application.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int SetApplicationMuted( bool Muted );

   /** Sets the volume of the application.

   @param Volume Application volume. The value ranges between 0 (lowest volume) and 255 (highest volume).
   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int SetApplicationVolume( int Volume );

   /** Retrieves the volume of the application.

    @param[out] Volume Reference to the application volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int GetApplicationVolume( int& Volume );

   /** Retrieves the microphone's mute status.

    @param[out] Muted Reference to whether the microphone is muted/unmuted.
    - true: Muted.
    - false: Unmuted.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int IsAudioRecordingDeviceMuted( bool& Muted );

   /** Retrieves the mute status of the audio playback device.

    @param[out] Muted Reference to whether the audio playback device is muted/unmuted.
    - true: Muted.
    - false: Unmuted.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int IsAudioPlaybackDeviceMuted( bool& Muted );

   /** Mutes/Unmutes the microphone.

    @param Muted Sets whether to mute/unmute the microphone:
    - true: Mutes.
    - false: Unmutes.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int SetAudioRecordingDeviceMuted( bool Muted );

   /** Mutes the audio playback device.

    @param Muted Sets whether to mute/unmute the audio playback device:
    - true: Mutes.
    - false: Unmutes.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int SetAudioPlaybackDeviceMuted( bool Muted );

   /** Retrieves the volume of the microphone.

    @param Volume Reference to the microphone volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int GetAudioRecordingDeviceVolume( int& Volume );

   /** Retrieves the volume of the audio playback device.

    @param Volume Reference to the audio playback device volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int GetAudioPlaybackDeviceVolume( int& Volume );

   /** Sets the volume of the microphone.

    @param Volume Sets the volume of the microphone. The value ranges between 0 (lowest volume) and 255 (highest volume).
    @return
    - 0: Success.
    - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int SetAudioRecordingDeviceVolume( int Volume );

   /** Sets the volume of the audio playback device.

    @param Volume Sets the volume of the audio playback device. The value ranges between 0 (lowest volume) and 255 (highest volume).
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int SetAudioPlaybackDeviceVolume( int Volume );

   /** Starts the microphone test.

    This method tests whether the microphone works properly. Once the test starts, the SDK uses the \ref OnAudioVolumeIndicationDelegate "OnAudioVolumeIndication" callback to notify the application with the volume information.

    @param IndicationInterval Interval period (ms) of the \ref OnAudioVolumeIndicationDelegate "OnAudioVolumeIndication" callback cycle.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int StartAudioRecordingDeviceTest( int IndicationInterval /*ms*/ );

   /** Stops the microphone test.

    This method stops the microphone test. You must call this method to stop the test after calling the \ref StartAudioRecordingDeviceTest method.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int StopAudioRecordingDeviceTest();

   /** Starts the audio playback device test.

    This method tests if the playback device works properly. In the test, the SDK plays an audio file specified by the user. If the user can hear the audio, the playback device works properly.

    @param TestAudioFilePath Path to the audio file for the audio playback device test in UTF-8:
    - Supported file formats: wav, mp3, m4a, and aac.
    - Supported file sample rates: 8000, 16000, 32000, 44100, and 48000 Hz.

    @return
    - 0: Success, and you can hear the sound of the specified audio file.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int StartAudioPlaybackDeviceTest( const FString& TestAudioFilePath );

   /** Stops the audio playback device test.

    This method stops testing the audio playback device. You must call this method to stop the test after calling the \ref StartAudioPlaybackDeviceTest method.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int StopAudioPlaybackDeviceTest();

   /** Starts the audio device loopback test.

   This method tests whether the local audio devices are working properly. After calling this method, the microphone captures the local audio and plays it through the speaker. The \ref OnAudioVolumeIndicationDelegate "OnAudioVolumeIndication" callback returns the local audio volume information at the set interval.

   @note This method tests the local audio devices and does not report the network conditions.

   @param IndicationInterval The time interval (ms) at which the \ref OnAudioVolumeIndicationDelegate "OnAudioVolumeIndication" callback returns.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int StartAudioDeviceLoopbackTest( int IndicationInterval /*ms*/ );

   /** Stops the audio device loopback test.

   @note Ensure that you call this method to stop the loopback test after calling the \ref StartAudioDeviceLoopbackTest method.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|AudioManager" )
      int StopAudioDeviceLoopbackTest();

   //////////////////////////////////////VideoManager//////////////////////////////////////////

   /** Returns the set of available video recording devices
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|VideoManager" )
      TArray<FMediaDevice> GetVideoRecordingDevices();

   /** Retrieves the video-capture device that is in use.

    @param[in] Index Video-capture device index.
    @param[out] DeviceName Reference to the video-capture device name.
    @param[out] DeviceId Reference to the video-capture device ID.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|VideoManager" )
      int GetVideoRecordingDevice( int Index, FString& DeviceName, FString& DeviceId );

   /** Sets a device with the device ID.

    @param DeviceId Video-capture device ID. Call the \ref GetVideoRecordingDevice method or \ref GetVideoRecordingDevices to retrieve it.

    @note Plugging or unplugging the device does not change the device ID.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|VideoManager" )
      int SetCurrentVideoRecordingDevice( const FString& DeviceId );

   /** Retrieves the video-capture device that is in use.

    @param[out] Index Video-capture device index.
    @param[out] DeviceName Video-capture device name.
    @param[out] DeviceId Video-capture device ID.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|VideoManager" )
      int GetCurrentVideoRecordingDevice( int& Index, FString& DeviceName, FString& DeviceId );

   /** Retrieves the total number of the indexed video devices in the system.

   @return Total number of the indexed video devices:
   */
   UFUNCTION( BlueprintCallable, Category = "Agora|VideoManager" )
      int GetVideoRecordingDeviceCount();

   /** Enumerates the video devices.

    This method this method enumerates all video devices in the system.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   UFUNCTION( BlueprintCallable, Category = "Agora|VideoManager" )
      int EnumerateVideoRecordingDevices();

   friend class agora::blueprints::AgoraAudioManager;
   friend class agora::blueprints::AgoraVideoManager;

protected:

   /** Factory method. Override this method to use custom agora::blueprints::IVideoFrameObserver class. */
   virtual agora::blueprints::IVideoFrameObserver* createVideoFrameObserver()
      PURE_VIRTUAL( UIAgora::createVideoFrameObserver, { return nullptr; } );

   /** Factory method. Override this method to use custom agora::blueprints::IAudioFrameObserver class. */
   virtual agora::blueprints::IAudioFrameObserver* createAudioFrameObserver()
      PURE_VIRTUAL( UIAgora::createAudioFrameObserver, { return nullptr; } );

protected:

   //todo: destroy in BeginDestroy method?
   TSharedPtr<agora::blueprints::RtcEngineEventHandler> rtcEngineEventHandler = nullptr;

   TSharedPtr<agora::rtc::ue4::AgoraRtcEngine> rtcEngine = nullptr;
   TSharedPtr<agora::media::ue4::AgoraMediaEngine> mediaEngine = nullptr;

   TUniquePtr<agora::blueprints::AgoraAudioManager> audioManager = nullptr;
   TUniquePtr<agora::blueprints::AgoraVideoManager> videoManager = nullptr;

   agora::blueprints::IAudioFrameObserver* audioFrameObserver = nullptr;
   agora::blueprints::IVideoFrameObserver* videoFrameObserver = nullptr;

private:
   /** 
   Forced use. Some \ref rtcEngine methods use structures with pointes fileds.
   Using points in blueprints is inconvenient (You should inherit from UObject). 
   These pointers were replaced with structures and converted values are stored here.
   @see SetLiveTranscoding
   */
   std::unique_ptr< agora::rtc::TranscodingUser[] > users = nullptr;
   /** @ref users */
   std::unique_ptr< agora::rtc::RtcImage > watermark = nullptr;
   /** @ref users */
   std::unique_ptr< agora::rtc::RtcImage > backgroundImage = nullptr;

   /**
   @ref users
   @see startChannelMediaRelay
   @see updateChannelMediaRelay
   */
   std::unique_ptr< agora::rtc::ChannelMediaInfo[] > destInfos = nullptr;
   
   /**
   @ref users
   @see startChannelMediaRelay
   @see updateChannelMediaRelay
   */
   std::unique_ptr< agora::rtc::ChannelMediaInfo > srcInfo = nullptr;

   /**
   Used for handling Agora callbacks.
   @param DeltaTime Game time passed since the last call.
   */
   virtual void Tick( float DeltaTime ) override;

   /** Makes this object tickable for Unreal.*/
   virtual bool IsTickable() const override { return true; }

   /**
   Tickable utill. 
   @return The stat id to use for this tickable.
   */
   virtual TStatId GetStatId() const override { return Super::GetStatID(); }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLocalFrameReceived, UTexture2D*, Frame );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FRemoteFrameReceived, int64, UserId, UTexture2D*, Frame );

/**
Implements UIAgora Interface.
Video frames are submitted here as Texture2D.
Audio frames are not handled here. Agora simply outputs audio to the speakers.
*/
UCLASS( Blueprintable )
class AGORABLUEPRINTABLE_API UAgora : public UIAgora
{
   GENERATED_BODY()

public:
   /** Occurs each time the SDK receives a video frame captured by the local camera.
    *
    * After you successfully initialized Agora, the SDK triggers this callback each time a video frame is received. In this callback,
    * you can get the video data captured by the local camera. You can then pre-process the data according to your scenarios.
    *
    * @note
    * This callback does not support sending processed RGBA video data back to the SDK.
    *
    * @param Frame Video Frame.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|VideoFrame" )
      FLocalFrameReceived OnLocalFrameReceivedDelegate;

   /** Occurs each time the SDK receives a video frame sent by the remote user.
    *
    * After you successfully initialized Agora, the SDK triggers this callback each time a video frame is received. In this callback,
    * you can get the video data sent by the remote user. You can then post-process the data according to your scenarios.
    *
    * @note
    * This callback does not support sending processed RGBA video data back to the SDK.
    *
    * @param UserId ID of the remote user who sends the current video frame.
    * @param videoFrame Frame Video Frame.
    */
   UPROPERTY( BlueprintAssignable, Category = "Agora|VideoFrame" )
      FRemoteFrameReceived OnRemoteFrameReceivedDelegate;

   UAgora();

protected:
   /**
   Audio Frame Observer isn't used here.
   @return nullptr.
   */
   virtual agora::blueprints::IAudioFrameObserver* createAudioFrameObserver() override;
private:
   /**
   Creates Video Frame Observer.
   @return \ref agora::blueprints::VideoFrameObserver.
   */
   virtual agora::blueprints::IVideoFrameObserver* createVideoFrameObserver() override;

   /** Removes all frames form \ref agora::blueprints::VideoFrameObserver. */
   UFUNCTION()
      void OnLeaveChannel( const FRtcStats& Stats );

   /** Removes user frame who left the channel. */
   UFUNCTION()
      void OnUserOffline( int64 userId, EUSER_OFFLINE_REASON_TYPE reason );
};