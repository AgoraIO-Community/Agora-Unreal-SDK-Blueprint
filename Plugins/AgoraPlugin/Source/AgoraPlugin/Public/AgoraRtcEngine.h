//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/IAgoraRtcEngine.h>
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

namespace agora
{

namespace media
{
namespace ue4
{
class AgoraMediaEngine;
}
}

namespace blueprints
{
class AgoraAudioManager;
class AgoraVideoManager;
}

namespace rtc
{
namespace ue4
{

//TODO: should I add RtcEngineParameters? It seems duplicate IRtcEngine methods

/**
* Wrapper around agora::rtc::IRtcEngine
*/
class AGORAPLUGIN_API AgoraRtcEngine
{
public:
	AgoraRtcEngine() = delete;
	AgoraRtcEngine(const AgoraRtcEngine& other);
	AgoraRtcEngine(AgoraRtcEngine&& other) noexcept;
	AgoraRtcEngine& operator=(const AgoraRtcEngine& other);
	AgoraRtcEngine& operator=(AgoraRtcEngine&& other) noexcept;
	~AgoraRtcEngine();

public:
   /**
   * @brief    Creates the \ref IRtcEngine object and returns the pointer.
   * @return   \arg Success: Pointer to the \ref IRtcEngine object.
   *           \arg Failure: nullptr.
   */
	static AgoraRtcEngine* createAgoraRtcEngine();

   /**
   * @brief                   Initializes the Agora SDK service.
   * @note                    Ensure that you call the \ref createAgoraRtcEngine and \ref initialize methods before calling any other API.
   * @param  rtcEngineContext Pointer to the RTC engine context. See \ref RtcEngineContext.
   * @return                  \arg Success: 0.
   *                          \arg Failure: <0.
   */
	int initialize(const agora::rtc::RtcEngineContext& rtcEngineContext);

	//TODO:?
	void setSyncForRelease(bool sync);

   /**
   * @brief          Sets the channel profile.
   * @brief          The SDK needs to know the application scenario to set the appropriate channel profile to apply different optimization methods.
   * @note           \arg  This method applies only to the Live-broadcast profile.
   *                 \arg  Users in the same channel must use the same channel profile.
   *                 \arg  Before calling this method to set a new channel profile, \ref release the current engine and create a new engine using \ref createAgoraRtcEngine() and \ref initialize.
   *                 \arg  Call this method before a user joins a channel because you cannot configure the channel profile when the channel is in use.
   *                 \arg  In the Communication profile, the Agora SDK supports encoding only in raw data, not in texture.
   * @param profile  Sets the channel profile. See \ref CHANNEL_PROFILE_TYPE.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setChannelProfile(agora::rtc::CHANNEL_PROFILE_TYPE profile);

   /**
   * @brief       Sets the role of the user, such as a host or an audience (default), before joining a channel in a live broadcast.
   * @brief       In the Live Broadcast profile, when a user switches user roles after joining a channel, a successful \ref setClientRole method call triggers the following callbacks:
   *              \arg  The local client: \ref onClientRoleChanged
   *              \arg  The remote client: \ref onUserJoined or \ref onUserOffline (BECOME_AUDIENCE)
   * @brief       This method can be used to switch the user role in a live broadcast after the user joins a channel.
   * @note        This method applies only to the Live-broadcast profile.
   * @param  role Sets the role of the user. See CLIENT_ROLE_TYPE.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int setClientRole(agora::rtc::CLIENT_ROLE_TYPE role);

   /**
   * @brief             Allows a user to join a channel.
   * @brief             Users in the same channel can talk to each other, and multiple users in the same channel can start a group chat. Users with different App IDs cannot call each other.
   * @brief             You must call the \ref leaveChannel method to exit the current call before entering another channel.
   * @brief             A successful \ref joinChannel method call triggers the following callbacks:
   *                    \arg  The local client: \ref onJoinChannelSuccess
   *                    \arg  The remote client: \ref onUserJoined , if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.
   * @brief             When the connection between the client and Agora's server is interrupted due to poor network conditions, the SDK tries reconnecting to the server. When the local client successfully rejoins the channel, the SDK triggers the \ref onRejoinChannelSuccess callback on the local client.
   * @note              A channel does not accept duplicate uids, such as two users with the same uid. If you set uid as 0, the system automatically assigns a uid. If you want to join a channel from different devices, ensure that each device has a different uid.
   * @warning           Ensure that the App ID used for creating the token is the same App ID used by the \ref initialize method for initializing the RTC engine. Otherwise, the CDN live streaming may fail.
   * @param token       Pointer to the token generated by the application server. In most circumstances, a static App ID suffices. For added security, use a Channel Key.
   *                    \arg If the user uses a static App ID, \a token is optional and can be set as NULL.
   *                    \arg If the user uses a Channel Key, Agora issues an additional App Certificate for you to generate a user key based on the algorithm and App Certificate for user authentication on the server.
   * @param channelId   Pointer to the unique channel name for the Agora RTC session in the string format smaller than 64 bytes. Supported characters:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","
   * @param info        (Optional) Pointer to additional information about the channel. This parameter can be set to NULL or contain channel related information. Other users in the channel will not receive this message.
   * @param uid         (Optional) User ID. A 32-bit unsigned integer with a value ranging from 1 to 2^32-1. The uid must be unique. If a uid is not assigned (or set to 0), the SDK assigns and returns a uid in the \ref onJoinChannelSuccess callback. Your application must record and maintain the returned \a uid since the SDK does not do so.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   *                       - \ref ERR_INVALID_ARGUMENT (-2)
   *                       - \ref ERR_NOT_READY (-3)
   *                       - \ref ERR_REFUSED (-5)
   */
	int joinChannel(const char* token, const char* channelId, const char* info, agora::rtc::uid_t uid);

   /**
   * @brief             Switches to a different channel.
   * @brief             This method allows the audience of a Live-broadcast channel to switch to a different channel.
   * @brief             After the user successfully switches to another channel, the \ref onLeaveChannel and \ref onJoinChannelSuccess callbacks are triggered to indicate that the user has left the original channel and joined a new one.
   * @note              This method applies to the audience role in a Live-broadcast channel only.
   * @param token       The token generated at your server:
                        \arg  For low-security requirements: You can use the temporary token generated in Console. For details, see Get a temporary token.
                        \arg  For high-security requirements: Use the token generated at your server. For details, see Get a token.
   * @param channelId   Pointer to the unique channel name for the Agora RTC session in the string format smaller than 64 bytes. Supported characters:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int switchChannel(const char* token, const char* channelId);

   /**
   * @brief    Allows a user to leave a channel, such as hanging up or exiting a call.
   * @brief    After joining a channel, the user must call the leaveChannel method to end the call before joining another channel.
   * @brief    This method returns 0 if the user leaves the channel and releases all resources related to the call.
   * @brief    This method call is asynchronous, and the user has not left the channel when the method call returns. Once the user leaves the channel, the SDK triggers the \ref onLeaveChannel callback.
   * @brief    A successful \ref leaveChannel method call triggers the following callbacks:
   *           \arg  The local client: \ref onLeaveChannel
   *           \arg  The remote client: \ref onUserOffline, if the user leaving the channel is in the Communication channel, or is a BROADCASTER in the Live Broadcast profile.
   * @brief    
   * @note     \arg  If you call the \ref release method immediately after the \a leaveChannel method, the \a leaveChannel process interrupts, and the \ref onLeaveChannel callback is not triggered.
   *           \arg  If you call the \a leaveChannel method during a CDN live streaming, the SDK triggers the \ref removePublishStreamUrl method.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int leaveChannel();

   /**
   * @brief       Gets a new token when the current token expires after a period of time.
   * @brief       The \a token expires after a period of time once the token schema is enabled when:
   *              \arg  The SDK triggers the \ref onTokenPrivilegeWillExpire callback, or
   *              \arg  The \ref onConnectionStateChanged reports CONNECTION_CHANGED_TOKEN_EXPIRED(9).
   * @brief       The application should call this method to get the new \a token. Failure to do so will result in the SDK disconnecting from the server.
   * @param token Pointer to the new token.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int renewToken(const char* token);

   /**
   * @brief             Registers a user account.
   * @brief             Once registered, the user account can be used to identify the local user when the user joins the channel. After the user successfully registers a user account, the SDK triggers the \ref onLocalUserRegistered callback on the local client, reporting the user ID and user account of the local user.
   * @brief             To join a channel with a user account, you can choose either of the following:
   *                    \arg  Call the \ref registerLocalUserAccount method to create a user account, and then the \ref joinChannelWithUserAccount method to join the channel.
   *                    \arg  Call the \ref joinChannelWithUserAccount method to join the channel.
   * @brief             The difference between the two is that for the former, the time elapsed between calling the \ref joinChannelWithUserAccount method and joining the channel is shorter than the latter.
   * @note              \arg  Ensure that you set the userAccount parameter. Otherwise, this method does not take effect.
   *                    \arg  Ensure that the value of the userAccount parameter is unique in the channel.
   *                    \arg  To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account. If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
   * @param appId       The App ID of your project.
   * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int registerLocalUserAccount(const char* appId, const char* userAccount);

   /**
   * @brief             Joins the channel with a user account.
   * @brief             After the user successfully joins the channel, the SDK triggers the following callbacks:
   *                    <ul>
   *                    <li> The local client: \ref onLocalUserRegistered and \ref onJoinChannelSuccess . The remote client: \ref onUserJoined and \ref onUserInfoUpdated , if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.
   *                    </ul>
   * @note              To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account. If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
   * @param token 	   The token generated at your server:
   *                    \arg  For low-security requirements: You can use the temporary token generated at Console. For details, see Get a temporary toke.
   *                    \arg  For high-security requirements: Set it as the token generated at your server. For details, see Get a token.
   * @param channelId   The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
   * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int joinChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount);

   /**
   * @brief             Gets the user information by passing in the user account.
   * @brief             After a remote user joins the channel, the SDK gets the user ID and user account of the remote user, caches them in a mapping table object (userInfo), and triggers the \ref onUserInfoUpdated callback on the local client.
   * @brief             After receiving the \ref onUserInfoUpdated callback, you can call this method to get the user ID of the remote user from the userInfo object by passing in the user account.
   * @param userAccount The user account of the user. Ensure that you set this parameter.
   * @param userInfo    userInfo A userInfo object that identifies the user:
   *                    \arg  Input: A userInfo object.
   *                    \arg  Output: A userInfo object that contains the user account and user ID of the user.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int getUserInfoByUserAccount(const char* userAccount, UserInfo* userInfo);

   /**
   * @brief             Gets the user information by passing in the user ID.
   * @brief             After a remote user joins the channel, the SDK gets the user ID and user account of the remote user, caches them in a mapping table object (userInfo), and triggers the \ref onUserInfoUpdated callback on the local client.
   * @brief             After receiving the \ref onUserInfoUpdated callback, you can call this method to get the user account of the remote user from the userInfo object by passing in the user ID.
   * @param uid         The user ID of the remote user. Ensure that you set this parameter.
   * @param userInfo    userInfo A userInfo object that identifies the user:
   *                    \arg  Input: A userInfo object.
   *                    \arg  Output: A userInfo object that contains the user account and user ID of the user.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int getUserInfoByUid(uid_t uid, UserInfo* userInfo);

   /**
   * @brief                   Starts an audio call test.
   * @brief                   This method starts an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly.
   * @brief                   In the audio call test, you record your voice. If the recording plays back within the set time interval, the audio devices and the network connection are working properly.
   * @note                    \arg  Call this method before joining a channel.
   *                          \arg  After calling this method, call the \ref stopEchoTest method to end the test. Otherwise, the app cannot run the next echo test, or call the \ref joinChannel method.
   *                          \arg  In the Live-broadcast profile, only a host can call this method.
   * @param intervalInSeconds The time interval (s) between when you speak and when the recording plays back.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int startEchoTest(int intervalInSeconds);

   /**
   * @brief    Stops the audio call test.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int stopEchoTest();

   /**
   * @brief    Enables the video module.
   * @brief    Call this method either before joining a channel or during a call. If this method is called before joining a channel, the call starts in the video mode. If this method is called during an audio call, the audio mode switches to the video mode. To disable the video module, call the \ref disableVideo method.
   * @brief    A successful \ref enableVideo method call triggers the \ref onUserEnableVideo (true) callback on the remote client.
   * @note     <ul>
   *           <li> This method affects the internal engine and can be called after the \ref leaveChannel method.
   *           <li> This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
   *           <ul>
   *              <li> \ref enableLocalVideo: Whether to enable the camera to create the local video stream.
   *              <li> \ref muteLocalVideoStream: Whether to publish the local video stream.
   *              <li> \ref muteRemoteVideoStream: Whether to subscribe to and play the remote video stream.
   *              <li> \ref muteAllRemoteVideoStreams: Whether to subscribe to and play all remote video streams.
   *           </ul>
   *           </ul>
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int enableVideo();

   /**
   * @brief    Disables the video module.
   * @brief    This method can be called before joining a channel or during a call. If this method is called before joining a channel, the call starts in audio mode. If this method is called during a video call, the video mode switches to the audio mode. To enable the video module, call the \ref enableVideo method.
   * @brief    A successful \ref disableVideo method call triggers the \ref onUserEnableVideo (false) callback on the remote client.
   * @note     <ul>
   *           <li> This method affects the internal engine and can be called after the \ref leaveChannel method.
   *           <li> This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
   *           <ul>
   *              <li> \ref enableLocalVideo: Whether to enable the camera to create the local video stream.
   *              <li> \ref muteLocalVideoStream: Whether to publish the local video stream.
   *              <li> \ref muteRemoteVideoStream: Whether to subscribe to and play the remote video stream.
   *              <li> \ref muteAllRemoteVideoStreams: Whether to subscribe to and play all remote video streams.
   *           </ul>
   *           </ul>
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int disableVideo();

   /**
   * @brief          Sets the video encoder configuration.
   * @brief          Each video encoder configuration corresponds to a set of video parameters, including the resolution, frame rate, bitrate, and video orientation.
   * @brief          The parameters specified in this method are the maximum values under ideal network conditions. If the video engine cannot render the video using the specified parameters due to poor network conditions, the parameters further down the list are considered until a successful configuration is found.
   * @note           If you do not need to set the video encoder configuration after joining the channel, you can call this method before the \ref enableVideo method to reduce the render time of the first video frame.
   * @param config   Sets the local video encoder configuration. See \ref VideoEncoderConfiguration.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setVideoEncoderConfiguration(const VideoEncoderConfiguration& config);

   /**
   * @brief          Sets the camera capture configuration.
   * @brief          For a video call or live broadcast, generally the SDK controls the camera output parameters. When the default camera capturer settings do not meet special requirements or cause performance problems, we recommend using this method to set the camera capturer configuration:
   *                 <ul>
   *                 <li> If the resolution or frame rate of the captured raw video data are higher than those set by \ref setVideoEncoderConfiguration, processing video frames requires extra CPU and RAM usage and degrades performance. We recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1 to avoid such problems.
   *                 <li> If you do not need local video preview or are willing to sacrifice preview quality, we recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1 to optimize CPU and RAM usage.
   *                 <li> If you want better quality for the local video preview, we recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2.
   *                 </ul>
   * @note           Call this method before enabling the local camera. That said, you can call this method before calling \ref joinChannel, \ref enableVideo, or \ref enableLocalVideo, depending on which method you use to turn on your local camera.
   * @param config   Sets the camera capturer configuration. See \ref CameraCapturerConfiguration.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setCameraCapturerConfiguration(const CameraCapturerConfiguration& config);

   /**
   * @brief          Sets the local video view and configures the video display settings on the local machine.
   * @brief          The application calls this method to bind each video window (view) of the local video streams and configures the video display settings. Call this method after initialization to configure the local video display settings before joining a channel. The binding is still valid after the user leaves the channel, which means that the window still displays. To unbind the view, set the view in \ref VideoCanvas to NULL.
   * @param canvas   Pointer to the local video view and settings. See \ref VideoCanvas.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setupLocalVideo(const VideoCanvas& canvas);

   /**
   * @brief          Sets the remote video view.
   * @brief          This method binds the remote user to the video display window (sets the view for the remote user by the specified uid in \ref VideoCanvas).
   * @brief          The application specifies the uid of the remote video in this method before the remote user joins the channel.
   * @brief          If the remote uid is unknown to the application, set it after the application receives the \ref onUserJoined callback.
   * @brief          If the Video Recording function is enabled, the Video Recording Service joins the channel as a dummy client, causing other clients to also receive the \ref onUserJoined callback. Do not bind the dummy client to the application view because the dummy client does not send any video streams. If your application does not recognize the dummy client, bind the remote user to the view when the SDK triggers the \ref onFirstRemoteVideoDecoded callback.
   * @brief          To unbind the remote user from the view, set the view in \ref VideoCanvas to NULL. Once the remote user leaves the channel, the SDK unbinds the remote user.
   * @param canvas   Pointer to the remote video view and settings. See \ref VideoCanvas.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setupRemoteVideo(const VideoCanvas& canvas);

   /**
   * @brief    Starts the local video preview before joining the channel.
   * @brief    Before calling this method, you must:
   *           <ul>
   *           <li> Call the \ref setupLocalVideo method to set up the local preview window and configure the attributes.
   *           <li> Call the \ref enableVideo method to enable video.
   *           </ul>
   * @note     Once the startPreview method is called to start the local video preview, if you leave the channel by calling the \ref leaveChannel method, the local video preview remains until you call the \ref stopPreview method to disable it.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int startPreview();

   /**
   * @brief                Prioritizes a remote user's stream.
   * @brief                Use this method with the \ref setRemoteSubscribeFallbackOption method. If the fallback function is enabled for a subscribed stream, the SDK ensures the high-priority user gets the best possible stream quality.
   * @note                 The Agora SDK supports setting userPriority as high for one user only.
   * @param uid            The ID of the remote user.
   * @param userPriority   Sets the priority of the remote user. See \ref PRIORITY_TYPE.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int setRemoteUserPriority(agora::rtc::uid_t uid, agora::rtc::PRIORITY_TYPE userPriority);

   /**
   * @brief    Stops the local video preview and disables video.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int stopPreview();

   /**
   * @brief    Enables the audio module.
   * @brief    The audio mode is enabled by default.
   * @note     <ul>
   *           <li> This method affects the internal engine and can be called after the \ref leaveChannel method.
   *           <li> This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
   *           <ul>
   *              <li> \ref enableLocalVideo: Whether to enable the camera to create the local video stream.
   *              <li> \ref muteLocalVideoStream: Whether to publish the local video stream.
   *              <li> \ref muteRemoteVideoStream: Whether to subscribe to and play the remote video stream.
   *              <li> \ref muteAllRemoteVideoStreams: Whether to subscribe to and play all remote video streams.
   *           </ul>
   *           </ul>
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int enableAudio();

   /**
   * @brief          Disables/Re-enables the local audio function.
   * @brief          The audio function is enabled by default. This method disables or re-enables the local audio function, that is, to stop or restart local audio capturing.
   * @brief          This method does not affect receiving or playing the remote audio streams, and enableLocalAudio(false) is applicable to scenarios where the user wants to receive remote audio streams without sending any audio stream to other users in the channel.
   * @brief          The SDK triggers the \ref onMicrophoneEnabled callback once the local audio function is disabled or enabled.
   * @note           <ul>
   *                 <li> Call this method after the \ref joinChannel method.
   *                 <li> This method is different from the \ref muteLocalAudioStream method:
   *                    <ul>
   *                    <li> \ref enableLocalAudio: Disables/Re-enables the local audio capturing and processing. If you disable or re-enable local audio recording using the \a enableLocalAudio method, the local user may hear a pause in the remote audio playback.
   *                    <li> \ref muteLocalAudioStream: Sends/Stops sending the local audio streams.
   *                    </ul>
   *                 <li> After you disable local audio recording using the \a enableLocalAudio(false) method, the system volume switches to the media volume. Re-enabling local audio recording using the \a enableLocalAudio(true) method switches the system volume back to the in-call volume.
   *                 </ul>
   * @param enabled  Sets whether to disable/re-enable the local audio function:
   *                 \arg  true: (Default) Re-enable the local audio function, that is, to start the local audio capturing device (for example, the microphone).
   *                 \arg  false: Disable the local audio function, that is, to stop local audio capturing.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int enableLocalAudio(bool enabled);

   /**
   * @brief    Disables the audio module.
   * @note     \arg  This method affects the internal engine and can be called after the \ref leaveChannel method. You can call this method either before or after joining a channel.
   *           \arg  This method resets the internal engine and takes some time to take effect. We recommend using the \ref enableLocalAudio and \ref muteLocalAudioStream methods to capture, process, and send the local audio streams.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int disableAudio();

   /**
   * @brief          Sets the audio parameters and application scenarios.
   * @note           \arg  The \a setAudioProfile method must be called before the \ref joinChannel method.
   *                 \arg  In the Communication and Live-broadcast profiles, the bitrate may be different from your settings due to network self-adaptation.
   *                 \arg  In scenarios involving music education, we recommend setting profile as \ref AUDIO_PROFILE_MUSIC_HIGH_QUALITY (4) and scenario as \ref AUDIO_SCENARIO_GAME_STREAMING (3).
   * @param profile  Sets the sample rate, bitrate, encoding mode, and the number of channels. See \ref AUDIO_PROFILE_TYPE.
   * @param scenario Sets the audio application scenario. See \ref AUDIO_SCENARIO_TYPE. Under different audio scenarios, the device uses different volume tracks, i.e. either the in-call volume or the media volume. For details, see What is the difference between the in-call volume and the media volume?.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setAudioProfile(agora::rtc::AUDIO_PROFILE_TYPE profile, agora::rtc::AUDIO_SCENARIO_TYPE scenario);

   /**
   * @brief       Stops/Resumes sending the local audio stream.
   * @brief       A successful \ref muteLocalAudioStream method call triggers the \ref onUserMuteAudio callback on the remote client.
   * @note        \arg When \a mute is set as \a true, this method does not disable the microphone, which does not affect any ongoing recording.
   *              \arg If you call \ref setChannelProfile after this method, the SDK resets whether or not to mute the local audio according to the channel profile and user role. Therefore, we recommend calling this method after the \a setChannelProfile method.
   * @param mute  Sets whether to send/stop sending the local audio stream:
   *              \arg  true: Stops sending the local audio stream.
   *              \arg  false: (Default) Sends the local audio stream.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int muteLocalAudioStream(bool mute);

   /**
   * @brief       Stops/Resumes receiving all remote users' audio streams.
   * @param mute  Sets whether to receive/stop receiving all remote users' audio streams.
   *              \arg  true: Stops receiving all remote users' audio streams.
   *              \arg  false: (Default) Receives all remote users' audio streams.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int muteAllRemoteAudioStreams(bool mute);

   /**
   * @brief       Stops/Resumes receiving all remote users' audio streams by default.
   * @param mute  Sets whether to receive/stop receiving all remote users' audio streams by default:
   *              \arg  true: Stops receiving all remote users' audio streams by default.
   *              \arg  false: (Default) Receives all remote users' audio streams by default.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int setDefaultMuteAllRemoteAudioStreams(bool mute);

   /**
   * @brief          Stops/Resumes receiving a specified remote user's audio stream.
   * @note           If you called the \ref muteAllRemoteAudioStreams method and set \a mute as \a true to stop receiving all remote users' audio streams, call the \a muteAllRemoteAudioStreams method and set \a mute as \a false before calling this method. 
   *                 The \a muteAllRemoteAudioStreams method sets all remote audio streams, while the \a muteRemoteAudioStream method sets a specified remote audio stream.
   * @param userId   User ID of the specified remote user sending the audio.
   * @param mute     Sets whether to receive/stop receiving a specified remote user's audio stream:
   *                 \arg  true: Stops receiving the specified remote user's audio stream.
   *                 \arg  false: (Default) Receives the specified remote user's audio stream.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int muteRemoteAudioStream(agora::rtc::uid_t userId, bool mute);

   /**
   * @brief       Stops/Resumes sending the local video stream.
   * @brief       A successful \ref muteLocalVideoStream method call triggers the \ref onUserMuteVideo callback on the remote client.
   * @note        \arg  When set to \a true, this method does not disable the camera which does not affect the retrieval of the local video streams. This method executes faster than the \ref enableLocalVideo method which controls the sending of the local video stream.
   *              \arg  If you call \ref setChannelProfile after this method, the SDK resets whether or not to mute the local video according to the channel profile and user role. Therefore, we recommend calling this method after the \a setChannelProfile method.
   * @param mute  Sets whether to send/stop sending the local video stream:
   *              \arg  true: Stop sending the local video stream.
   *              \arg  false: (Default) Send the local video stream.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int muteLocalVideoStream(bool mute);

   /**
   * @brief          Enables/Disables the local video capture.
   * @brief          This method disables or re-enables the local video capturer, and does not affect receiving the remote video stream.
   * @brief          After you call the \ref enableVideo method, the local video capturer is enabled by default. You can call \ref enableLocalVideo(false) to disable the local video capturer. If you want to re-enable it, call \ref enableLocalVideo(true).
   * @brief          After the local video capturer is successfully disabled or re-enabled, the SDK triggers the \ref onUserEnableLocalVideo callback on the remote client.
   * @note           This method affects the internal engine and can be called after the \ref leaveChannel method.
   * @param enabled  Sets whether to disable/re-enable the local video, including the capturer, renderer, and sender:
   *                 \arg  true: (Default) Re-enable the local video.
   *                 \arg  false: Disable the local video. Once the local video is disabled, the remote users can no longer receive the video stream of this user, while this user can still receive the video streams of the other remote users.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int enableLocalVideo(bool enabled);

   /**
   * @brief       Stops/Resumes receiving all video stream from a specified remote user.
   * @param mute  Sets whether to receive/stop receiving all remote users' video streams:
   *              \arg  true: Stop receiving all remote users' video streams.
   *              \arg  false: (Default) Receive all remote users' video streams.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int muteAllRemoteVideoStreams(bool mute);

   /**
   * @brief       Stops/Resumes receiving all remote users' video streams by default.
   * @param mute  Sets whether to receive/stop receiving all remote users' video streams by default:
   *              \arg  true: Stop receiving all remote users' video streams by default.
   *              \arg  false: (Default) Receive all remote users' video streams by default.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int setDefaultMuteAllRemoteVideoStreams(bool mute);

   /**
   * @brief          Stops/Resumes receiving the video stream from a specified remote user.
   * @note           If you called the \ref muteAllRemoteVideoStreams method and set mute as true to stop receiving all remote video streams, call the \a muteAllRemoteVideoStreams method and set \a mute as \a false before calling this method.
   * @param userId   User ID of the specified remote user.
   * @param mute     Sets whether to stop/resume receiving the video stream from a specified remote user:
   *                 \arg  true: Stop receiving the specified remote user's video stream.
   *                 \arg  false: (Default) Receive the specified remote user's video stream.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int muteRemoteVideoStream(agora::rtc::uid_t userId, bool mute);

   /**
   * @brief             Sets the remote user's video stream type received by the local user when the remote user sends dual streams.
   * @brief             This method allows the application to adjust the corresponding video-stream type based on the size of the video window to reduce the bandwidth and resources.
   *                    \arg  If the remote user enables the dual-stream mode by calling the \ref enableDualStreamMode method, the SDK receives the high-stream video by default.
   *                    \arg  If the dual-stream mode is not enabled, the SDK receives the high-stream video by default.
   * @brief             The method result returns in the \ref onApiCallExecuted callback. The SDK receives the high-stream video by default to reduce the bandwidth. 
   *                    If needed, users may use this method to switch to the low-stream video. By default, the aspect ratio of the low-stream video is the same as the high-stream video. 
   *                    Once the resolution of the high-stream video is set, the system automatically sets the resolution, frame rate, and bitrate of the low-stream video.
   * @param userId      ID of the remote user sending the video stream.
   * @param streamType 	Sets the video-stream type. See \ref REMOTE_VIDEO_STREAM_TYPE.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setRemoteVideoStreamType(agora::rtc::uid_t userId, agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType);

   /**
   * @brief             Sets the default video-stream type for the video received by the local user when the remote user sends dual streams.
   *                    \arg  If the dual-stream mode is enabled by calling the \ref enableDualStreamMode method, the user receives the high-stream video by default. The \a setRemoteDefaultVideoStreamType method allows the application to adjust the corresponding video-stream type according to the size of the video window, reducing the bandwidth and resources.
   *                    \arg  If the dual-stream mode is not enabled, the user receives the high-stream video by default.
   * @brief             The result after calling this method is returned in the \ref onApiCallExecuted callback. The Agora SDK receives the high-stream video by default to reduce the bandwidth. If needed, users can switch to the low-stream video through this method.
   * @param streamType  Sets the default video-stream type. See \ref REMOTE_VIDEO_STREAM_TYPE.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setRemoteDefaultVideoStreamType(agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType);

   /**
   * @brief             Enables the \ref onAudioVolumeIndication callback at a set time interval to report on which users are speaking and the speakers' volume.
   * @brief             Once this method is enabled, the SDK returns the volume indication in the \ref onAudioVolumeIndication callback at the set time interval, whether or not any user is speaking in the channel.
   * @param interval    Sets the time interval between two consecutive volume indications:
   *                    \arg  ≤ 0: Disables the volume indication.
   *                    \arg  > 0: Time interval (ms) between two consecutive volume indications. We recommend setting \a interval > 200 ms. Do not set interval < 10 ms, or the \a onAudioVolumeIndication callback will not be triggered.
   * @param smooth      Smoothing factor sets the sensitivity of the audio volume indicator. The value ranges between 0 and 10. The greater the value, the more sensitive the indicator. The recommended value is 3.
   * @param report_vad  \arg  true: Enable the voice activity detection of the local user. Once it is enabled, the vad parameter of the \a onAudioVolumeIndication callback reports the voice activity status of the local user.
   *                    \arg  false: (Default) Disable the voice activity detection of the local user. Once it is disabled, the vad parameter of the \a onAudioVolumeIndication callback does not report the voice activity status of the local user, except for the scenario where the engine automatically detects the voice activity of the local user.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int enableAudioVolumeIndication(int interval, int smooth, bool report_vad);

   /**
   * @brief             Starts an audio recording on the client.
   * @brief             The SDK allows recording during a call. After successfully calling this method, you can record the audio of all the users in the channel and get an audio recording file. Supported formats of the recording file are as follows:
   *                    <ul>
   *                    <li> .wav: Large file size with high fidelity.
   *                    <li> .aac: Small file size with low fidelity.
   *                    </ul>
   * @note              \arg  Ensure that the directory you use to save the recording file exists and is writable.
   *                    \arg  This method is usually called after the \ref joinChannel method. The recording automatically stops when you call the \ref leaveChannel method.
   *                    \arg  For better recording effects, set quality as \ref AUDIO_RECORDING_QUALITY_MEDIUM or \ref AUDIO_RECORDING_QUALITY_HIGH when sampleRate is 44.1 kHz or 48 kHz.
   * @param filePath    Pointer to the absolute file path of the recording file. The string of the file name is in UTF-8.
   * @param sampleRate  Sample rate (kHz) of the recording file. Supported values are as follows:
   *                    \arg  16
   *                    \arg  (Default) 32
   *                    \arg  44.1
   *                    \arg  48
   * @param quality     Sets the audio recording quality. See \ref AUDIO_RECORDING_QUALITY_TYPE.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality);

   /**
   * @brief    Stops an audio recording on the client.
   * @brief    You can call this method before calling the \ref leaveChannel method else, the recording automatically stops when the \ref leaveChannel method is called.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int stopAudioRecording();

   /**
   * @brief             Starts playing and mixing the music file.
   * @brief             This method mixes the specified local audio file with the audio stream from the microphone, or replaces the microphone's audio stream with the specified local audio file. 
   *                    You can choose whether the other user can hear the local audio playback and specify the number of playback loops. This method also supports online music playback.
   * @brief             When the audio mixing file playback finishes after calling this method, the SDK triggers the \ref onAudioMixingFinished callback.
   * @brief             A successful \ref startAudioMixing method call triggers the \ref onAudioMixingStateChanged (PLAY) callback on the local client.
   * @brief             When the audio mixing file playback finishes, the SDK triggers the \ref onAudioMixingStateChanged (STOPPED) callback on the local client.
   * @note              \arg  Call this method when you are in a channel.
   *                    \arg  If the local audio mixing file does not exist, or if the SDK does not support the file format or cannot access the music file URL, the SDK returns WARN_AUDIO_MIXING_OPEN_ERROR = 701.
   * @param filePath    Pointer to the absolute path of the local or online audio file to mix. Supported audio formats: 3GP, ASF, ADTS, AVI, MP3, MPEG-4, SAMI, and WAVE. For more information, see Supported Media Formats in Media Foundation.
   * @param loopback    Sets which user can hear the audio mixing:
   *                    \arg  true: Only the local user can hear the audio mixing.
   *                    \arg  false: Both users can hear the audio mixing.
   * @param replace     Sets the audio mixing content:
   *                    \arg  true: Only the specified audio file is published; the audio stream received by the microphone is not published.
   *                    \arg  false: The local audio file is mixed with the audio stream from the microphone.
   * @param cycle       Sets the number of playback loops:
   *                    \arg  Positive integer: Number of playback loops.
   *                    \arg  -1: Infinite playback loops.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle);

   /**
   * @brief    Stops playing and mixing the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int stopAudioMixing();

   /**
   * @brief    Pauses playing and mixing the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int pauseAudioMixing();

   /**
   * @brief    Resumes playing and mixing the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int resumeAudioMixing();

   /**
   * @brief          Adjusts the volume during audio mixing.
   * @brief          Call this method when you are in a channel.
   * @note           Calling this method does not affect the volume of audio effect file playback invoked by the \ref playEffect method.
   * @param volume   Audio mixing volume. The value ranges between 0 and 100 (default).
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int adjustAudioMixingVolume(int volume);

   /**
   * @brief          Adjusts the audio mixing volume for local playback.
   * @note           Call this method when you are in a channel.
   * @param volume   Audio mixing volume for local playback. The value ranges between 0 and 100 (default).
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int adjustAudioMixingPlayoutVolume(int volume);

   /**
   * @brief    Retrieves the audio mixing volume for local playback.
   * @brief    This method helps troubleshoot audio volume related issues.
   * @note     Call this method when you are in a channel.
   * @return   \arg  ≥ 0: The audio mixing volume, if this method call succeeds. The value range is [0,100].
   *           \arg  < 0: Failure.
   */
	int getAudioMixingPlayoutVolume();

   /**
   * @brief          Adjusts the audio mixing volume for publishing (for remote users).
   * @note           Call this method when you are in a channel.
   * @param volume   Audio mixing volume for publishing. The value ranges between 0 and 100 (default).
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int adjustAudioMixingPublishVolume(int volume);

   /**
   * @brief    Retrieves the audio mixing volume for publishing.
   * @brief    This method helps troubleshoot audio volume related issues.
   * @note     Call this method when you are in a channel.
   * @return   \arg  ≥ 0: The audio mixing volume for publishing, if this method call succeeds. The value range is [0,100].
   *           \arg  < 0: Failure.
   */
	int getAudioMixingPublishVolume();

   /**
   * @brief    Retrieves the duration (ms) of the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  ≥ 0: The audio mixing duration, if this method call succeeds.
   *           \arg  < 0: Failure.
   */
	int getAudioMixingDuration();

   /**
   * @brief    Retrieves the playback position (ms) of the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  ≥ 0: The current playback position of the audio mixing, if this method call succeeds.
   *           \arg  < 0: Failure.
   */
	int getAudioMixingCurrentPosition();

   /**
   * @brief       Sets the playback position of the music file to a different starting position (the default plays from the beginning).
   * @param pos   The playback starting position (ms) of the music file.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setAudioMixingPosition(int pos /*in ms*/);

   /**
   * @brief    Retrieves the volume of the audio effects.
   * @brief    The value ranges between 0.0 and 100.0.
   * @return   \arg  ≥ 0: Volume of the audio effects, if this method call succeeds.
   *           \arg  < 0: Failure.
   */
	int getEffectsVolume();

   /**
   * @brief          Sets the volume of the audio effects.
   * @param volume   Sets the volume of the audio effects. The value ranges between 0 and 100 (default).
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setEffectsVolume(int volume);

   /**
   * @brief          Sets the volume of a specified audio effect.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @param volume   Sets the volume of the specified audio effect. The value ranges between 0 and 100 (default).
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setVolumeOfEffect(int soundId, int volume);

   /**
   * @brief             Plays a specified local or online audio effect file.
   * @brief             This method allows you to set the loop count, pitch, pan, and gain of the audio effect file, as well as whether the remote user can hear the audio effect.
   * @brief             To play multiple audio effect files simultaneously, call this method multiple times with different soundIds and filePaths. We recommend playing no more than three audio effect files at the same time.
   * @param soundId     ID of the specified audio effect. Each audio effect has a unique ID.
   * @note              \arg  If the audio effect is preloaded into the memory through the \ref preloadEffect method, the value of \a soundID must be the same as that in the \a preloadEffect method.
   *                    \arg  Playing multiple online audio effect files simultaneously is not supported on macOS and Windows.
   * @param filePath    The absolute path to the local audio effect file or the URL of the online audio effect file.
   * @param loopCount   Sets the number of times the audio effect loops:
   *                    \arg  0: Play the audio effect once.
   *                    \arg  1: Play the audio effect twice.
   *                    \arg  -1: Play the audio effect in an indefinite loop until the \ref stopEffect or \ref stopAllEffects method is called.
   * @param pitch       Sets the pitch of the audio effect. The value ranges between 0.5 and 2. The default value is 1 (no change to the pitch). The lower the value, the lower the pitch.
   * @param pan         Sets the spatial position of the audio effect. The value ranges between -1.0 and 1.0:
   *                    \arg  0.0: The audio effect displays ahead.
   *                    \arg  1.0: The audio effect displays to the right.
   *                    \arg  -1.0: The audio effect displays to the left.
   * @param gain        Sets the volume of the audio effect. The value ranges between 0 and 100 (default). The lower the value, the lower the volume of the audio effect.
   * @param publish     Sets whether or not to publish the specified audio effect to the remote stream:
   *                    \arg  true: The locally played audio effect is published to the Agora Cloud and the remote users can hear it.
   *                    \arg  false: The locally played audio effect is not published to the Agora Cloud and the remote users cannot hear it.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int playEffect(
		int soundId,
		const char* filePath,
		int loopCount,
		double pitch,
		double pan,
		int gain,
		bool publish = false);

   /**
   * @brief          Stops playing a specified audio effect.
   * @param soundId  ID of the audio effect to stop playing. Each audio effect has a unique ID.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int stopEffect(int soundId);

   /**
   * @brief    Stops playing all audio effects.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int stopAllEffects();

   /**
   * @brief          Preloads a specified audio effect file into the memory.
   * @note           This method does not support online audio effect files.
   * @brief          To ensure smooth communication, limit the size of the audio effect file. We recommend using this method to preload the audio effect before calling the \ref joinChannel method.
   * @brief          Supported audio formats: mp3, aac, m4a, 3gp, and wav.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @param filePath Pointer to the absolute path of the audio effect file.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int preloadEffect(int soundId, const char* filePath);

   /**
   * @brief          Releases a specified preloaded audio effect from the memory.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int unloadEffect(int soundId);

   /**
   * @brief          Pauses a specified audio effect.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int pauseEffect(int soundId);

   /**
   * @brief    Pauses all audio effects.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int pauseAllEffects();

   /**
   * @brief          Resumes playing a specified audio effect.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int resumeEffect(int soundId);

   /**
   * @brief    Resumes playing all audio effects.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int resumeAllEffects();

   /**
   * @brief          Enables/Disables stereo panning for remote users.
   * @brief          Ensure that you call this method before joinChannel to enable stereo panning for remote users so that the local user can track the position of a remote user by calling \ref setRemoteVoicePosition.
   * @param enabled  Sets whether or not to enable stereo panning for remote users:
   *                 \arg  true: enables stereo panning.
   *                 \arg  false: disables stereo panning.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int enableSoundPositionIndication(bool enabled);

   /**
   * @brief       Sets the sound position and gain of a remote user.
   * @brief       When the local user calls this method to set the sound position of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of space. This method applies to massively multiplayer online games, such as Battle Royale games.
   * @note        \arg  For this method to work, enable stereo panning for remote users by calling the \ref enableSoundPositionIndication method before joining a channel.
                  \arg  This method requires hardware support. For the best sound positioning, we recommend using a stereo speaker.
   * @param uid   The ID of the remote user.
   * @param pan   The sound position of the remote user. The value ranges from -1.0 to 1.0:
   *              \arg  0.0: the remote sound comes from the front.
   *              \arg  -1.0: the remote sound comes from the left.
   *              \arg  1.0: the remote sound comes from the right.
   * @param gain  Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user). The smaller the value, the less the gain.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int setRemoteVoicePosition(uid_t uid, double pan, double gain);

   /**
   * @brief       Changes the voice pitch of the local speaker.
   * @param pitch Sets the voice pitch. The value ranges between 0.5 and 2.0. The lower the value, the lower the voice pitch. The default value is 1.0 (no change to the local voice pitch).
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int setLocalVoicePitch(double pitch);

   /**
   * @brief                Sets the local voice equalization effect.
   * @param bandFrequency  Sets the band frequency. The value ranges between 0 and 9, representing the respective 10-band center frequencies of the voice effects, including 31, 62, 125, 500, 1k, 2k, 4k, 8k, and 16k Hz. See \ref AUDIO_EQUALIZATION_BAND_FREQUENCY.
   * @param bandGain       Sets the gain of each band in dB. The value ranges between -15 and 15.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int setLocalVoiceEqualization(agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain);

   /**
   * @brief             Sets the local voice reverberation.
   * @brief             v2.4.0 adds the \ref setLocalVoiceReverbPreset method, a more user-friendly method for setting the local voice reverberation. You can use this method to set the local reverberation effect, such as pop music, R&B, rock music, and hip-hop.
   * @param reverbKey   Sets the reverberation key. See \ref AUDIO_REVERB_TYPE.
   * @param value       Sets the value of the reverberation key.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setLocalVoiceReverb(agora::rtc::AUDIO_REVERB_TYPE reverbKey, int value);

   /**
   * @brief                Sets the local voice changer option.
   * @note                 Do not use this method together with the \ref setLocalVoiceReverbPreset method, because the method called later overrides the one called earlier.
   * @param voiceChanger   Sets the local voice changer option. See \ref VOICE_CHANGER_PRESET.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int setLocalVoiceChanger(agora::rtc::VOICE_CHANGER_PRESET voiceChanger);

   /**
   * @brief                Sets the preset local voice reverberation effect.
   * @note                 \arg  Do not use this method together with \ref setLocalVoiceReverb.
   *                       \arg  Do not use this method together with the \ref setLocalVoiceChanger method, because the method called later overrides the one called earlier.
   * @param reverbPreset   Sets the preset audio reverberation configuration. See \ref AUDIO_REVERB_PRESET.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int setLocalVoiceReverbPreset(agora::rtc::AUDIO_REVERB_PRESET reverbPreset);

   /**
   * @brief          Specifies an SDK output log file.
   * @brief          The log file records all SDK operations during runtime. If it does not exist, the SDK creates one.
   * @note           \arg  The default log file is located at: C:\\Users\\<user_name>\\AppData\\Local\\Agora\<process_name\>.
                     \arg  Ensure that you call this method immediately after calling the \ref initialize method, otherwise the output log may not be complete.
   * @param filePath File path of the log file. The string of the log file is in UTF-8.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setLogFile(const char* filePath);

   /**
   * @brief          Sets the output log level of the SDK.
   * @brief          You can use one or a combination of the log filter levels. The log level follows the sequence of OFF, CRITICAL, ERROR, WARNING, INFO, and DEBUG. Choose a level to see the logs preceding that level.
   * @brief          If you set the log level to WARNING, you see the logs within levels CRITICAL, ERROR, and WARNING.
   * @param filter   Sets the log filter level. See \ref LOG_FILTER_TYPE.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setLogFilter(unsigned int filter);

   /**
   * @brief                   Sets the log file size (KB).
   * @brief                   The SDK has two log files, each with a default size of 512 KB. If you set \a fileSizeInBytes as 1024 KB, the SDK outputs log files with a total maximum size of 2 MB. If the total size of the log files exceed the set value, the new output log files overwrite the old output log files.
   * @param fileSizeInKBytes  The SDK log file size (KB).
   * @return                  \arg  Success: 0.
   *                          \arg  Failure: <0.
   */
	int setLogFileSize(unsigned int fileSizeInKBytes);

   /**
   * @brief             Sets the local video display mode.
   * @brief             This method can be called multiple times during a call to change the display mode.
   * @param renderMode  Sets the local video display mode. See \ref RENDER_MODE_TYPE.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setLocalRenderMode(agora::rtc::RENDER_MODE_TYPE renderMode);

   /**
   * @brief             Sets the video display mode of a specified remote user.
   * @brief             This method can be called multiple times during a call to change the display mode.
   * @param userId      ID of the remote user.
   * @param renderMode  Sets the video display mode. See \ref RENDER_MODE_TYPE.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setRemoteRenderMode(agora::rtc::uid_t userId, agora::rtc::RENDER_MODE_TYPE renderMode);

   /**
   * @brief             Sets the local video mirror mode.
   * @brief             You must call this method before calling the \ref startPreview method, otherwise the mirror mode will not work.
   * @note              The SDK enables the mirror mode by default.
   * @param mirrorMode  Sets the local video mirror mode. See \ref VIDEO_MIRROR_MODE_TYPE.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setLocalVideoMirrorMode(agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode);

   /**
   * @brief          Sets the stream mode to the single-stream (default) or dual-stream mode. (Live broadcast only.)
   * @brief          If the dual-stream mode is enabled, the receiver can choose to receive the high stream (high-resolution and high-bitrate video stream), or the low stream (low-resolution and low-bitrate video stream).
   * @param enabled  Sets the stream mode:
   *                 \arg  true: Dual-stream mode.
   *                 \arg  false: (Default) Single-stream mode.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int enableDualStreamMode(bool enabled);

   /**
   * @brief             Sets the external audio source. Please call this method before \ref joinChannel.
   * @param enabled     Sets whether to enable/disable the external audio source:
   *                    \arg  true: Enables the external audio source.
   *                    \arg  false: (Default) Disables the external audio source.
   * @param sampleRate  Sets the sample rate (Hz) of the external audio source, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
   * @param channels    Sets the number of audio channels of the external audio source:
   *                    \arg  1: Mono.
   *                    \arg  2: Stereo.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setExternalAudioSource(bool enabled, int sampleRate, int channels);

   /**
   * @brief             Sets the external audio sink. This method applies to scenarios where you want to use external audio data for playback. After enabling the external audio sink, you can call the \ref pullAudioFrame method to pull the remote audio data, process it, and play it with the audio effects that you want.
   * @note              Once you enable the external audio sink, the app will not retrieve any audio data from the \ref onPlaybackAudioFrame callback.
   * @param enabled     \arg  true: Enables the external audio sink.
   *                    \arg  false: (Default) Disables the external audio sink.
   * @param sampleRate  Sets the sample rate (Hz) of the external audio sink, which can be set as 8000, 16000, 32000, 44100 or 48000.
   * @param channels    Sets the number of audio channels of the external audio sink:
   *                    \arg  1: Mono.
   *                    \arg  2: Stereo.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setExternalAudioSink(bool enabled, int sampleRate, int channels);

   /**
   * @brief                Sets the audio recording format for the \ref onRecordAudioFrame callback.
   * @param sampleRate     Sets the sample rate (\a samplesPerSec) returned in the \a onRecordAudioFrame callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
   * @param channel        Sets the number of audio channels (\a channels) returned in the \a onRecordAudioFrame callback:
   *                       \arg  1: Mono.
   *                       \arg  2: Stereo.
   * @param mode           Sets the use mode (see \ref RAW_AUDIO_FRAME_OP_MODE_TYPE) of the \a onRecordAudioFrame callback.
   * @param samplesPerCall Sets the sample points (\a samples) returned in the \a onRecordAudioFrame callback. \a samplesPerCall is usually set as 1024 for stream pushing.
   * @brief                samplesPerCall = (int)(samplesPerSec × sampleInterval × numChannels), where sampleInterval ≥ 0.01 in seconds.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int setRecordingAudioFrameParameters(
		int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);

   /**
   * @brief                Sets the audio playback format for the \ref onPlaybackAudioFrame callback.
   * @param sampleRate     Sets the sample rate (samplesPerSec) returned in the \a onPlaybackAudioFrame callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
   * @param channel        Sets the number of channels (\a channels) returned in the \a onPlaybackAudioFrame callback:
   *                       \arg  1: Mono.
   *                       \arg  2: Stereo.
   * @param mode           Sets the use mode (see \ref RAW_AUDIO_FRAME_OP_MODE_TYPE) of the onPlaybackAudioFrame callback.
   * @param samplesPerCall Sets the sample points (\a samples) returned in the \a onPlaybackAudioFrame callback. \a samplesPerCall is usually set as 1024 for stream pushing.
   * @brief                samplesPerCall = (int)(samplesPerSec × sampleInterval × numChannels), where sampleInterval ≥ 0.01 in seconds.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int setPlaybackAudioFrameParameters(
		int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);

   /**
   * @brief                Sets the mixed audio format for the \ref onMixedAudioFrame callback.
   * @param sampleRate     Sets the sample rate (\a samplesPerSec) returned in the \a onMixedAudioFrame callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
   * @param samplesPerCall Sets the sample points (\a samples) returned in the \a onMixedAudioFrame callback. samplesPerCall is usually set as 1024 for stream pushing.
   * @brief                samplesPerCall = (int)(samplesPerSec × sampleInterval × numChannels), where sampleInterval ≥ 0.01 in seconds.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);

   /**
   * @brief          Adjusts the recording volume.
   * @param volume   Recording volume. The value ranges between 0 and 400:
   *                 \arg  0: Mute.
   *                 \arg  100: Original volume.
   *                 \arg  400: (Maximum) Four times the original volume with signal clipping protection.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int adjustRecordingSignalVolume(int volume);

   /**
   * @brief          Adjusts the playback volume of the voice.
   * @param volume   The playback volume of the voice. The value ranges between 0 and 400:
   *                 \arg  0: Mute.
   *                 \arg  100: Original volume.
   *                 \arg  400: (Maximum) Four times the original volume with signal clipping protection.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int adjustPlaybackSignalVolume(int volume);

   /**
   * @brief          Enables interoperability with the Agora Web SDK.
   * @note           \arg  This method applies only to the Live-broadcast profile. In the Communication profile, interoperability with the Agora Web SDK is enabled by default.
   *                 \arg  If the channel has Web SDK users, ensure that you call this method, or the video of the Native user will be a black screen for the Web user.
   * @param enabled  Sets whether to enable/disable interoperability with the Agora Web SDK:
   *                 \arg  true: Enable.
   *                 \arg  false: (Default) Disable.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int enableWebSdkInteroperability(bool enabled);

   /**
   * @brief          Sets the fallback option for the locally published video stream based on the network conditions.
   * @brief          If *option* is set as \a STREAM_FALLBACK_OPTION_AUDIO_ONLY (2), the SDK will:
   *                 \arg  Disable the upstream video but enable audio only when the network conditions deteriorate and cannot support both video and audio.
   *                 \arg  Re-enable the video when the network conditions improve.
   * @brief          When the locally published video stream falls back to audio only or when the audio-only stream switches back to the video, the SDK triggers the \ref onLocalPublishFallbackToAudioOnly callback.
   * @note           Agora does not recommend using this method for CDN live streaming, because the remote CDN live user will have a noticeable lag when the locally published video stream falls back to audio only.
   * @param option   Sets the fallback option for the locally published video stream:
   *                 \arg  \ref STREAM_FALLBACK_OPTION_DISABLED (0): (Default) No fallback behavior for the locally published video stream when the uplink network condition is poor. The stream quality is not guaranteed.
   *                 \arg  \ref STREAM_FALLBACK_OPTION_AUDIO_ONLY (2): The locally published video stream falls back to audio only when the uplink network condition is poor.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setLocalPublishFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option);

   /**
   * @brief          Sets the fallback option for the remotely subscribed video stream based on the network conditions.
   * @brief          The default setting for @p option is \ref STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW, where the remotely subscribed video stream falls back to the low-stream video (low resolution and low bitrate) under poor downlink network conditions.
   * @brief          If *option* is set as \ref STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK automatically switches the video from a high-stream to a low-stream, or disables the video when the downlink network conditions cannot support both audio and video to guarantee the quality of the audio. The SDK monitors the network quality and restores the video stream when the network conditions improve.
   * @brief          When the remotely subscribed video stream falls back to audio only or when the audio-only stream switches back to the video stream, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly "onRemoteSubscribeFallbackToAudioOnly" callback.
   * @param  option  Sets the fallback option for the remotely subscribed video stream. See \ref STREAM_FALLBACK_OPTIONS.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setRemoteSubscribeFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option);

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
   /**
   * @brief    Switches between front and rear cameras.
   * @note     This method is for Android and iOS only.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int switchCamera();

   /**
   * @brief             Switches between front and rear cameras.
   * @note              This method is for Android and iOS only.
   * @param direction   Sets the camera to be used:
   *                    \arg  CAMERA_DIRECTION.CAMERA_REAR: Use the rear camera.
   *                    \arg  CAMERA_DIRECTION.CAMERA_FRONT: Use the front camera.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int switchCamera(CAMERA_DIRECTION direction);

   /**
   * @brief                   Sets the default audio playback route.
   * @brief                   This method sets whether the received audio is routed to the earpiece or speakerphone by default before joining a channel. If a user does not call this method, the audio is routed to the earpiece by default. If you need to change the default audio route after joining a channel, call the  \ref setEnableSpeakerphone method.
   * @brief                   The default setting for each mode:
   *                          <ul>
   *                          <li> Voice: Earpiece.
   *                          <li> Video: Speakerphone. If a user who is in the Communication profile calls the \ref disableVideo method or if the user calls the \ref muteLocalVideoStream and \ref muteAllRemoteVideoStreams methods, the default audio route switches back to the earpiece automatically.
   *                          <li> Live Broadcast: Speakerphone.
   *                          <li> Gaming Voice: Speakerphone.
   *                          </ul>
   * @note                    \arg  This method is for Android and iOS only.
   *                          \arg  This method only works in audio mode.
   *                          \arg  Call this method before calling the \ref joinChannel method.
   *                          \arg  Regardless of whether the audio is routed to the speakerphone or earpiece by default, once a headset is plugged in or Bluetooth device is connected, the default audio route changes. The default audio route switches to the earpiece once removing the headset or disconnecting the Bluetooth device.
   * @param defaultToSpeaker  Sets the default audio route:
   *                          -  true: Speakerphone.
   *                          -  false: (Default) Earpiece.
   * @return                  \arg  Success: 0.
   *                          \arg  Failure: <0.
   */
	int setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker);

   /**
   * @brief             Enables/Disables the audio playback route to the speakerphone.
   * @brief             This method sets whether the audio is routed to the speakerphone or earpiece.
   * @brief             See the default audio route explanation in the \ref setDefaultAudioRouteToSpeakerphone method and check whether it is necessary to call this method.
   * @note              \arg  This method is for Android and iOS only.
   *                    \arg  Ensure that you have successfully called the \ref joinChannel method before calling this method.
   *                    \arg  After calling this method, the SDK returns the \ref onAudioRouteChanged callback to indicate the changes.
   *                    \arg  This method does not take effect if a headset is used.
   * @param speakerOn   Sets whether to route the audio to the speakerphone or earpiece:
   *                    \arg  true: Route the audio to the speakerphone.
   *                    \arg  false: Route the audio to the earpiece.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setEnableSpeakerphone(bool speakerOn);

   /**
   * @brief          Sets the volume of the in-ear monitor.
   * @param volume   Sets the volume of the in-ear monitor. The value ranges between 0 and 100 (default).
   * @note           This method is for Android and iOS only.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setInEarMonitoringVolume(int volume);

   /**
   * @brief          Checks whether the speakerphone is enabled.
   * @note           This method is for Android and iOS only.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	bool isSpeakerphoneEnabled();
#endif

#if (defined(__APPLE__) && TARGET_OS_IOS)
   /**
   * @brief             Sets the audio session’s operational restriction.
   * @brief             The SDK and the app can both configure the audio session by default. The app may occasionally use other apps or third-party components to manipulate the audio session and restrict the SDK from doing so. This method allows the app to restrict the SDK’s manipulation of the audio session.
   * @brief             You can call this method at any time to return the control of the audio sessions to the SDK.
   * @note              \arg  This method is for iOS only.
   *                    \arg  This method restricts the SDK’s manipulation of the audio session. Any operation to the audio session relies solely on the app, other apps, or third-party components.
   * @param restriction The operational restriction (bit mask) of the SDK on the audio session. See \ref UDIO_SESSION_OPERATION_RESTRICTION.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction);
#endif

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
   /**
   * @brief             Enables loopback recording.
   * @brief             If you enable loopback recording, the output of the sound card is mixed into the audio stream sent to the other end.
   * @param enabled     Sets whether to enable/disable loopback recording.
   *                    -  true: Enable loopback recording.
   *                    -  false: (Default) Disable loopback recording.
   * @param deviceName  Pointer to the device name of the sound card. The default value is NULL (the default sound card).
   * @note              \arg  This method is for macOS and Windows only.
   *                    \arg  macOS does not support loopback recording of the default sound card. If you need to use this method, please use a virtual sound card and pass its name to the deviceName parameter. Agora has tested and recommends using soundflower.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int enableLoopbackRecording(bool enabled, const char* deviceName = nullptr);
#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
   /**
   * @brief                Shares the whole or part of a screen by specifying the display ID.
   * @note                 This method is for macOS only.
   * @param displayId      The display ID of the screen to be shared. This parameter specifies which screen you want to share.
   * @param regionRect     (Optional) Sets the relative location of the region to the screen. NIL means sharing the whole screen. See \ref Rectangle. If the specified region overruns the screen, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen.
   * @param captureParams  Sets the screen sharing encoding parameters. See \ref ScreenCaptureParameters.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0:
   *                          -  \ref ERR_INVALID_STATE: the screen sharing state is invalid, probably because another screen or window is being shared. Call \ref stopScreenCapture to stop the current screen sharing.
   *                          -  \ref ERR_INVALID_ARGUMENT: the argument is invalid.
   */
	int startScreenCaptureByDisplayId(
		unsigned int displayId,
		const Rectangle& regionRect,
		const ScreenCaptureParameters& captureParams);
#endif

#if defined(_WIN32)
   /**
   * @brief                Shares the whole or part of a screen by specifying the screen rect.
   * @param screenRect     Sets the relative location of the screen to the virtual screen. For information on how to get screenRect, see Share the Screen.
   * @param regionRect     (Optional) Sets the relative location of the region to the screen. NULL means sharing the whole screen. See \ref Rectangle. If the specified region overruns the screen, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen.
   * @param captureParams  Sets the screen sharing encoding parameters. See \ref ScreenCaptureParameters.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0:
   *                          -  \ref  ERR_INVALID_STATE: the screen sharing state is invalid, probably because another screen or window is being shared. Call \ref stopScreenCapture to stop the current screen sharing.
   *                          -  \ref  ERR_INVALID_ARGUMENT: the argument is invalid.
   */
	int startScreenCaptureByScreenRect(
		const Rectangle& screenRect,
		const Rectangle& regionRect,
		const ScreenCaptureParameters& captureParams);
#endif

   /**
   * @brief                Shares the whole or part of a window by specifying the window ID.
   * @param windowId       The ID of the window to be shared. For information on how to get the windowId, see Share the Screen.
   * @param regionRect     (Optional) The relative location of the region to the window. NULL/NIL means sharing the whole window. See \ref Rectangle. If the specified region overruns the window, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole window.
   * @param captureParams  Window sharing encoding parameters. See \ref ScreenCaptureParameters.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0:
   *                          -  \ref ERR_INVALID_STATE: the window sharing state is invalid, probably because another screen or window is being shared. Call \ref stopScreenCapture to stop sharing the current window.
   *                          -  \ref ERR_INVALID_ARGUMENT: the argument is invalid.
   */
	int startScreenCaptureByWindowId(
		view_t windowId,
		const Rectangle& regionRect,
		const ScreenCaptureParameters& captureParams);

   /**
   * @brief             Sets the content hint for screen sharing.
   * @brief             A content hint suggests the type of the content being shared, so that the SDK applies different optimization algorithm to different types of content.
   * @param contentHint Sets the content hint for screen sharing. See VideoContentHint.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setScreenCaptureContentHint(VideoContentHint contentHint);

   /**
   * @brief                Updates the screen sharing parameters.
   * @param captureParams  Sets the screen sharing encoding parameters. See \ref ScreenCaptureParameters.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0:
   *                          -  \ref ERR_NOT_READY: no screen or windows is being shared.
   */
	int updateScreenCaptureParameters(const ScreenCaptureParameters& captureParams);

   /**
   * @brief             Updates the screen sharing region.
   * @param regionRect  Sets the relative location of the region to the screen or window. NULL means sharing the whole screen or window. See \ref Rectangle. If the specified region overruns the screen or window, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen or window.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0:
   *                          -  \ref ERR_NOT_READY: no screen or window is being shared.
   */
	int updateScreenCaptureRegion(const Rectangle& regionRect);

   /**
   * @brief    Stop screen sharing.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int stopScreenCapture();

#endif

   /**
   * @brief          Retrieves the current call ID.
   * @brief          When a user joins a channel on a client, a *callId* is generated to identify the call from the client. Feedback methods, such as \ref rate and \ref complain, must be called after the call ends to submit feedback to the SDK.
   * @brief          The \ref rate and \ref complain methods require the *callId* parameter retrieved from the \a getCallId method during a call. *callId* is passed as an argument into the \ref rate and \ref complain methods after the call ends.
   * @param callId   Pointer to the current call ID.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int getCallId(agora::util::AString& callId);

   /**
   * @brief             Allows a user to rate a call after the call ends.
   * @param callId      Pointer to the ID of the call, retrieved from the \ref getCallId method.
   * @param rating      Rating of the call. The value is between 1 (lowest score) and 5 (highest score). If you set a value out of this range, the \ref ERR_INVALID_ARGUMENT (2) error returns.
   * @param description (Optional) Pointer to the description of the rating, with a string length of less than 800 bytes.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int rate(const char* callId, int rating, const char* description);

   /**
   * @brief             Allows a user to complain about the call quality after a call ends.
   * @param callId      Pointer to the ID of the call, retrieved from the \ref getCallId method.
   * @param description (Optional) Pointer to the description of the complaint, with a string length of less than 800 bytes.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int complain(const char* callId, const char* description);

   /**
   * @brief       Retrieves the SDK version number.
   * @param build Pointer to the build number.
   * @return      The version of the current SDK in the string format. For example, 2.3.1.
   */
	const char* getVersion(int* build);

   /**
   * @brief    Enables the network connection quality test.
   * @brief    This method tests the quality of the users' network connections and is disabled by default.
   * @brief    Before a user joins a channel or before an audience switches to a host, call this method to check the uplink network quality.
   * @brief    This method consumes additional network traffic, and hence may affect communication quality.
   * @brief    Call the \ref disableLastmileTest method to disable this test after receiving the \ref onLastmileQuality callback, and before joining a channel.
   * @note     \arg  Do not call any other methods before receiving the onLastmileQuality callback. Otherwise, the callback may be interrupted by other methods, and hence may not be triggered.
   *           \arg  A host should not call this method after joining a channel (when in a call).
   *           \arg  If you call this method to test the last-mile quality, the SDK consumes the bandwidth of a video stream, whose bitrate corresponds to the bitrate you set in the setVideoEncoderConfiguration method. After you join the channel, whether you have called the disableLastmileTest method or not, the SDK automatically stops consuming the bandwidth.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int enableLastmileTest();

   /**
   * @brief    Disables the network connection quality test.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int disableLastmileTest();

   /**
   * @brief          Starts the last-mile network probe test.
   * @brief          This method starts the last-mile network probe test before joining a channel to get the uplink and downlink last-mile network statistics, including the bandwidth, packet loss, jitter, and round-trip time (RTT).
   * @brief          Call this method to check the uplink network quality before users join a channel or before an audience switches to a host. Once this method is enabled, the SDK returns the following callbacks:
   *                 <ul>
   *                 <li> \ref onLastmileQuality: the SDK triggers this callback within two seconds depending on the network conditions. This callback rates the network conditions and is more closely linked to the user experience.
   *                 <li> \ref onLastmileProbeResult: the SDK triggers this callback within 30 seconds depending on the network conditions. This callback returns the real-time statistics of the network conditions and is more objective.
   *                 </ul>
   * @note           \arg  This method consumes extra network traffic and may affect communication quality. We do not recommend calling this method together with enableLastmileTest.
   *                 \arg  Do not call other methods before receiving the onLastmileQuality and onLastmileProbeResult callbacks. Otherwise, the callbacks may be interrupted.
   *                 \arg  In the Live-broadcast profile, a host should not call this method after joining a channel.
   * @param config   Sets the configurations of the last-mile network probe test. See \ref LastmileProbeConfig.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int startLastmileProbeTest(const LastmileProbeConfig& config);

   /**
   * @brief    Stops the last-mile network probe test.
   */
	int stopLastmileProbeTest();

   /**
   * @brief    Retrieves the warning or error description.
   * @return   code \ref WARN_CODE_TYPE or \ref ERROR_CODE_TYPE returned in the \ref onWarning or \ref onError callback.
   */
	const char* getErrorDescription(int code);

   /**
   * @brief          Enables built-in encryption with an encryption password before users join a channel.
   * @brief          All users in a channel must use the same encryption password. The encryption password is automatically cleared once a user leaves the channel.
   * @brief          If an encryption password is not specified, the encryption functionality will be disabled.
   * @note           \arg  Do not use this method for CDN live streaming.
   *                 \arg  For optimal transmission, ensure that the encrypted data size does not exceed the original data size + 16 bytes. 16 bytes is the maximum padding size for AES encryption.
   * @param secret   Pointer to the encryption password.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int setEncryptionSecret(const char* secret);

   /**
   * @brief                Sets the built-in encryption mode.
   * @brief                The Agora SDK supports built-in encryption, which is set to the *aes-128-xts* mode by default. Call this method to use other encryption modes.
   * @brief                All users in the same channel must use the same encryption mode and password.
   * @brief                Refer to the information related to the AES encryption algorithm on the differences between the encryption modes.
   * @note                 Call the setEncryptionSecret method to enable the built-in encryption function before calling this method.
   * @param encryptionMode \arg  Pointer to the set encryption mode:
   *                       \arg  "aes-128-xts": (Default) 128-bit AES encryption, XTS mode.
   *                       \arg  "aes-128-ecb": 128-bit AES encryption, ECB mode.
   *                       \arg  "aes-256-xts": 256-bit AES encryption, XTS mode.
   *                       \arg  "": When encryptionMode is set as NULL, the encryption mode is set as "aes-128-xts" by default.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int setEncryptionMode(const char* encryptionMode);

   /**
   * @brief          Registers a packet observer.
   * @brief          The Agora SDK allows your application to register a packet observer to receive callbacks for voice or video packet transmission.
   * @note           \arg  The size of the packet sent to the network after processing should not exceed 1200 bytes, otherwise, the packet may fail to be sent.
   *                 \arg  Ensure that both receivers and senders call this method, otherwise, you may meet undefined behaviors such as no voice and black screen.
   *                 \arg  When you use CDN live streaming, recording or storage functions, Agora doesn't recommend calling this method.
   * @param observer Pointer to the registered packet observer. See \ref IPacketObserver.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int registerPacketObserver(IPacketObserver* observer);

   /**
   * @brief          Creates a data stream.
   * @brief          Each user can create up to five data streams during the lifecycle of the RtcEngine.
   * @note           Set both the reliable and ordered parameters to true or false. Do not set one as true and the other as false.
   * @param streamId Pointer to the ID of the created data stream.
   * @param reliable Sets whether or not the recipients are guaranteed to receive the data stream from the sender within five seconds:
   *                 -  true: The recipients receive the data stream from the sender within five seconds. If the recipient does not receive the data stream within five seconds, an error is reported to the application.
   *                 -  false: There is no guarantee that the recipients receive the data stream within five seconds and no error message is reported for any delay or missing data stream.
   * @param ordered  Sets whether or not the recipients receive the data stream in the sent order:
   *                 -  true: The recipients receive the data stream in the sent order.
   *                 -  false: The recipients do not receive the data stream in the sent order.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int createDataStream(int* streamId, bool reliable, bool ordered);

   /**
   * @brief          Sends data stream messages to all users in a channel.
   * @brief          The SDK has the following restrictions on this method:
   *                 -  Up to 30 packets can be sent per second in a channel with each packet having a maximum size of 1 kB.
   *                 -  Each client can send up to 6 kB of data per second.
   *                 -  Each user can have up to five data streams simultaneously.
   * @brief          A successful \ref sendStreamMessage method call triggers the \ref onStreamMessage callback on the remote client, from which the remote user gets the stream message.
   * @brief          A failed \ref sendStreamMessage method call triggers the \ref onStreamMessage callback on the remote client.
   * @note           This method applies only to the Communication profile or to the hosts in the Live-broadcast profile. If an audience in the Live-broadcast profile calls this method, the audience may be switched to a host.
   * @param streamId ID of the sent data stream, returned in the \ref createDataStream method.
   * @param data     Pointer to the sent data.
   * @param length   Length of the sent data.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int sendStreamMessage(int streamId, const char* data, size_t length);

   /**
   * @brief                      Publishes the local stream to a specified CDN live RTMP address. (CDN live only.)
   * @brief                      The SDK returns the result of this method call in the \ref onStreamPublished callback.
   * @brief                      The *addPublishStreamUrl* method call triggers the \ref onRtmpStreamingStateChanged callback on the local client to report the state of adding a local stream to the CDN.
   * @note                       \arg  Ensure that the user joins the channel before calling this method.
   *                             \arg  Ensure that you enable the RTMP Converter service before using this function. See \ref Prerequisites.
   *                             \arg  This method adds only one stream RTMP URL address each time it is called.
   *                             \arg  This method applies to Live Broadcast only.
   * @param url                  The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes. The RTMP URL address must not contain special characters, such as Chinese language characters.
   * @param transcodingEnabled   Sets whether transcoding is enabled/disabled:
   *                             true: Enable transcoding. To \ref transcode the audio or video streams when publishing them to CDN live, often used for combining the audio and video streams of multiple hosts in CDN live. If you set this parameter as true, ensure that you call the \ref setLiveTranscoding method before this method.
   *                             false: Disable transcoding.
   * @return                     \arg  Success: 0.
   *                             \arg  Failure: <0:
   *                                - \ref ERR_INVALID_ARGUMENT (2): The RTMP URL address is NULL or has a string length of 0.
   *                                - \ref ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the stream.
   */
	int addPublishStreamUrl(const char* url, bool transcodingEnabled);

   /**
   * @brief       Removes an RTMP stream from the CDN. (CDN live only.)
   * @brief       This method removes the RTMP URL address (added by the \ref addPublishStreamUrl method) from a CDN live stream. The SDK returns the result of this method call in the \ref onStreamUnpublished callback.
   * @brief       The \ref removePublishStreamUrl method call triggers the \ref onRtmpStreamingStateChanged callback on the local client to report the state of removing an RTMP stream from the CDN.
   * @note        \arg  This method removes only one RTMP URL address each time it is called.
   *              \arg  The RTMP URL address must not contain special characters, such as Chinese language characters.
   *              \arg  This method applies to Live Broadcast only.
   * @param url   The RTMP URL address to be removed. The maximum length of this parameter is 1024 bytes.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int removePublishStreamUrl(const char* url);

   /**
   * @brief             Sets the video layout and audio settings for CDN live. (CDN live only.)
   * @brief             The SDK triggers the \ref onTranscodingUpdated callback when you call the setLiveTranscoding method to update the transcoding setting.
   * @note              \arg  This method applies to Live Broadcast only.
   *                    \arg  Ensure that you enable the RTMP Converter service before using this function. See \ref Prerequisites.
   *                    \arg  If you call the *setLiveTranscoding* method to update the transcoding setting for the first time, the SDK does not trigger the *onTranscodingUpdated* callback.
   * @param transcoding Sets the CDN live audio/video transcoding settings. See \ref LiveTranscoding.
   * @return            \arg  Success: 0.
   *                    \arg  Failure: <0.
   */
	int setLiveTranscoding(const LiveTranscoding& transcoding);

   /**
   * @brief                Adds a watermark image to the local video.
   * @brief                This method adds a PNG watermark image to the local video in a live broadcast. Once the watermark image is added, all the audience in the channel (CDN audience included), and the recording device can see and capture it. Agora supports adding only one watermark image onto the local video, and the newly watermark image replaces the previous one.
   * @brief                The watermark position depends on the settings in the \ref setVideoEncoderConfiguration method:
   *                       <ul>
   *                       <li> If the orientation mode of the encoding video is \ref ORIENTATION_MODE_FIXED_LANDSCAPE, or the landscape mode in \ref ORIENTATION_MODE_ADAPTIVE, the watermark uses the landscape orientation.
   *                       <li> If the orientation mode of the encoding video is \ref ORIENTATION_MODE_FIXED_PORTRAIT, or the portrait mode in \ref ORIENTATION_MODE_ADAPTIVE, the watermark uses the portrait orientation.
   *                       <li> When setting the watermark position, the region must be less than the dimensions set in the *setVideoEncoderConfiguration* method. Otherwise, the watermark image will be cropped.
   *                       </ul>
   * @note                 \arg  Ensure that you have called the \ref enableVideo method to enable the video module before calling this method.
   *                       \arg  If you only want to add a watermark image to the local video for the audience in the CDN live broadcast channel to see and capture, you can call this method or the \ref setLiveTranscoding method.
   *                       \arg  This method supports adding a watermark image in the PNG file format only. Supported pixel formats of the PNG image are RGBA, RGB, Palette, Gray, and Alpha_gray.
   *                       \arg  If the dimensions of the PNG image differ from your settings in this method, the image will be cropped or zoomed to conform to your settings.
   *                       \arg  If you have enabled the local video preview by calling the \ref startPreview method, you can use the *visibleInPreview* member in the \ref WatermarkOptions class to set whether or not the watermark is visible in preview.
   *                       \arg  If you have mirrored the local video by calling the \ref setLocalVideoMirrorMode method, the watermark image in preview is also mirrored.
   * @param watermarkUrl   The local file path of the watermark image to be added. This method supports adding a watermark image from the local absolute or relative file path.
   * @param options        Pointer to the watermark's options to be added. See \ref WatermarkOptions for more infomation.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options);

   /**
   * @brief    Removes the watermark image from the video stream added by the \ref addVideoWatermark method.
   * @return   \arg  Success: 0.
   *           \arg  Failure: <0.
   */
	int clearVideoWatermarks();

   /**
   * @brief          Enables/Disables image enhancement and sets the options.
   * @note           Supports Android and iOS only!
   * @param enabled  Sets whether or not to enable image enhancement:
   *                 -  true: enables image enhancement.
   *                 -  false: disables image enhancement.
   * @param options  Sets the image enhancement option. See \ref BeautyOptions.
   */
	int setBeautyEffectOptions(bool enabled, BeautyOptions options);

   /**
   * @brief          Adds a voice or video stream URL address to a live broadcast.
   * @brief          The \ref onStreamPublished callback returns the inject status. If this method call is successful, the server pulls the voice or video stream and injects it into a live channel. This is applicable to scenarios where all audience members in the channel can watch a live show and interact with each other.
   * @brief          The *addInjectStreamUrl* method call triggers the following callbacks:
   *                 <ul>
   *                 <li> The local client:
   *                    <ul>
   *                    <li> \ref onStreamInjectedStatus, with the state of the injecting the online stream.
   *                    <li> \ref onUserJoined (uid: 666), if the method call is successful and the online media stream is injected into the channel.
   *                    </ul>
   *                 <li> The remote client:
   *                    <ul>
   *                    <li> onUserJoined (uid: 666), if the method call is successful and the online media stream is injected into the channel.
   *                    </ul>
   *                 </ul>
   * @note           \arg  Ensure that you enable the RTMP Converter service before using this function. See \ref Prerequisites.
   *                 \arg  This method applies to the Native SDK v2.4.1 and later.
   * @param url      Pointer to the URL address to be added to the ongoing live broadcast. Valid protocols are RTMP, HLS, and FLV.
   *                    \arg  Supported FLV audio codec type: AAC.
   *                    \arg  Supported FLV video codec type: H264 (AVC).
   * @param config   Pointer to the \ref InjectStreamConfig object that contains the configuration of the added voice or video stream.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0:
   *                    -  \ref ERR_INVALID_ARGUMENT (2): The injected URL does not exist. Call this method again to inject the stream and ensure that the URL is valid.
   *                    -  \ref ERR_NOT_READY (3): The user is not in the channel.
   *                    -  \ref ERR_NOT_SUPPORTED (4): The channel profile is not live broadcast. Call the \ref setChannelProfile method and set the channel profile to live broadcast before calling this method.
   *                    -  \ref ERR_NOT_INITIALIZED (7): The SDK is not initialized. Ensure that the \ref IRtcEngine object is initialized before calling this method.
   */
	int addInjectStreamUrl(const char* url, const InjectStreamConfig& config);

   /**
   * @brief                Starts to relay media streams across channels.
   * @brief                After a successful method call, the SDK triggers the \ref onChannelMediaRelayStateChanged and \ref onChannelMediaRelayEvent callbacks, and these callbacks return the state and events of the media stream relay.
   *                       <ul>
   *                       <li> If the \ref onChannelMediaRelayStateChanged callback returns \ref RELAY_STATE_RUNNING (2) and \ref RELAY_OK (0), and the \ref onChannelMediaRelayEvent callback returns \ref RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL (4), the broadcaster starts sending data to the destination channel.
   *                       <li> If the \ref onChannelMediaRelayStateChanged callback returns \ref RELAY_STATE_FAILURE (3), an exception occurs during the media stream relay.
   *                       </ul>
   * @note                 \arg  Call this method after the \ref joinChannel method.
   *                       \arg  This method takes effect only when you are a broadcaster in a Live-broadcast channel.
   *                       \arg  After a successful method call, if you want to call this method again, ensure that you call the \ref stopChannelMediaRelay method to quit the current relay.
   * @param configuration  The configuration of the media stream relay: \ref ChannelMediaRelayConfiguration.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int startChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration);

   /**
   * @brief                Updates the channels for media stream relay. After a successful \ref startChannelMediaRelay method call, if you want to relay the media stream to more channels, or leave the current relay channel, you can call the \ref updateChannelMediaRelay method.
   * @brief                After a successful method call, the SDK triggers the \ref onChannelMediaRelayEvent callback with the \ref RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL (7) state code.
   * @note                 Call this method after the \ref startChannelMediaRelay method to update the destination channel.
   * param  configuration  The media stream relay configuration: \ref ChannelMediaRelayConfiguration.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
	int updateChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration);

   /**
   * @brief       Stops the media stream relay.
   * @brief       Once the relay stops, the broadcaster quits all the destination channels.
   * @brief       After a successful method call, the SDK triggers the \ref onChannelMediaRelayStateChanged callback. If the callback returns \ref RELAY_STATE_IDLE (0) and \ref RELAY_OK (0), the broadcaster successfully stops the relay.
   * @note        If the method call fails, the SDK triggers the \ref onChannelMediaRelayStateChanged callback with the \ref RELAY_ERROR_SERVER_NO_RESPONSE (2) or \ref RELAY_ERROR_SERVER_CONNECTION_LOST (8) state code. You can leave the channel by calling the \ref leaveChannel method, and the media stream relay automatically stops.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int stopChannelMediaRelay();

   /**
   * @brief       Removes the voice or video stream URL address from a live broadcast.
   * @brief       This method removes the URL address (added by the \ref addInjectStreamUrl method) from the live broadcast.
   * @note        If this method is called successfully, the SDK triggers the \ref onUserOffline callback and returns a stream uid of 666.
   * @param url   Pointer to the URL address of the added stream to be removed.
   * @return      \arg  Success: 0.
   *              \arg  Failure: <0.
   */
	int removeInjectStreamUrl(const char* url);

	bool registerEventHandler(IRtcEngineEventHandler* eventHandler);

	bool unregisterEventHandler(IRtcEngineEventHandler* eventHandler);

   /**
   * @brief    Gets the current connection state of the SDK.
   * @return   \ref  CONNECTION_STATE_TYPE.
   */
	agora::rtc::CONNECTION_STATE_TYPE getConnectionState();

   /**
   * @brief          Registers the metadata observer.
   * @brief          Registers the metadata observer. You need to implement the \ref IMetadataObserver class and specify the metadata type in this method. A successful call of this method triggers the \ref getMaxMetadataSize callback. This method enables you to add synchronized metadata in the video stream for more diversified live broadcast interactions, such as sending shopping links, digital coupons, and online quizzes.
   * @note           \arg  Call this method before the joinChannel method.
   *                 \arg  This method applies to the Live-broadcast channel profile.
   * @param observer The \ref IMetadataObserver class. See the definition of \ref IMetadataObserver for details.
   * @param type     See \ref METADATA_TYPE. The SDK supports VIDEO_METADATA (0) only for now.
   * @return         \arg  Success: 0.
   *                 \arg  Failure: <0.
   */
	int registerMediaMetadataObserver(IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type);

public:
	friend class agora::media::ue4::AgoraMediaEngine;
   friend class agora::blueprints::AgoraVideoManager;
   friend class agora::blueprints::AgoraAudioManager;
	friend class AgoraVideoDeviceManager;
	friend class AgoraAudioDeviceManager;
	friend class AgoraLiveEngine;
private:
   /**
   * @brief       Releases all \ref IRtcEngine resources.
   * @param sync  \arg  true: (Synchronous call) The result returns after the \ref IRtcEngine 
   *                    resources are released. The application should not call this method in the SDK 
   *                    generated callbacks. Otherwise, the SDK must wait for the callbacks to return to 
   *                    recover the associated \ref IRtcEngine resources, resulting in a deadlock. 
   *                    The SDK automatically detects the deadlock and converts this method into an  
   *                    asynchronous call, causing the test to take additional time.
   *              \arg  false: (Asynchronous call) The result returns immediately, even when the \ref 
   *                    IRtcEngine resources have not been released. The SDK releases all resources.
   * @note        Do not immediately uninstall the SDK's dynamic library after the call, or it may cause a 
   *              crash due to the SDK clean-up thread not quitting.
   */
	void release(bool sync = false);

private:
	AgoraRtcEngine(agora::rtc::IRtcEngine* rtcEngine);

private:
	agora::rtc::IRtcEngine* m_rtcEngine = nullptr;
	bool m_sync = false;
};

}
}
}