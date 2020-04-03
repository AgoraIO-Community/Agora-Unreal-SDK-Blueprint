// Copyright (c) 2019 Agora.io. All rights reserved.


#include "Agora.h"
#include "AgoraBlueprintable.h"
#include "AgoraRtcEngine.h"
#include "../../AgoraPlugin/Public/AgoraMediaEngine.h"

using namespace agora::rtc::ue4;
using namespace agora::media::ue4;

void UIAgora::Initialize( EResult& result, const FString& AddId, UPlainData* OptionalContext )
{
   result = EResult::Success;

   rtcEngine = TSharedPtr< AgoraRtcEngine >( AgoraRtcEngine::createAgoraRtcEngine() );
   if( !rtcEngine )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::Initialize - failed to create Agora Rtc Engine" ) );
      result = EResult::Error;
      return;
   }

   rtcEngineEventHandler = TSharedPtr<agora::blueprints::RtcEngineEventHandler>( new agora::blueprints::RtcEngineEventHandler( this ) );
   if( !rtcEngineEventHandler )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::Initialize - failed to create RtcEngineEventHandler" ) );
      result = EResult::Error;
      return;
   }

   static agora::rtc::RtcEngineContext context;
   context.appId = TCHAR_TO_ANSI( *AddId );
   context.eventHandler = rtcEngineEventHandler.Get();
   if( OptionalContext )
      context.context = OptionalContext->GetPlainData();

   if( rtcEngine->initialize( context ) < 0 )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::Initialize - failed to initialize Agora Rtc Engine, check input parameters" ) );
      result = EResult::Error;
      return;
   }

   mediaEngine = TSharedPtr<AgoraMediaEngine>( AgoraMediaEngine::Create( rtcEngine.Get() ) );
   if( !mediaEngine )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::Initialize - failed to create Media Engine" ) );
      result = EResult::Error;
      return;
   }

   audioFrameObserver = createAudioFrameObserver();
   videoFrameObserver = createVideoFrameObserver();

   if( mediaEngine->registerAudioFrameObserver( audioFrameObserver ) < 0 )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::Initialize - failed to register Audio Frame Observer" ) );
      result = EResult::Error;
      return;
   }

   if( mediaEngine->registerVideoFrameObserver( videoFrameObserver ) < 0 )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::Initialize - failed to register Video Frame Observer" ) );
      result = EResult::Error;
      return;
   }

   audioManager = agora::blueprints::AgoraAudioManager::Create( this );
   if( !audioManager )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::Initialize - failed to create Audio Manager" ) );
      result = EResult::Error;
      return;
   }
   videoManager = agora::blueprints::AgoraVideoManager::Create( this );
   if( !videoManager )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::Initialize - failed to create Video Manager" ) );
      result = EResult::Error;
      return;
   }
}

void UIAgora::BeginDestroy()
{
   Super::BeginDestroy();
   if( mediaEngine )
   {
      mediaEngine->registerVideoFrameObserver( nullptr );
      mediaEngine->registerAudioFrameObserver( nullptr );
   }
   delete videoFrameObserver;
   delete audioFrameObserver;
}

void UIAgora::Tick( float DeltaTime )
{
   if( rtcEngineEventHandler )
      rtcEngineEventHandler->OnTick();

   if( videoFrameObserver )
      videoFrameObserver->OnTick( DeltaTime );
   if( audioFrameObserver )
      audioFrameObserver->OnTick( DeltaTime );
}

int UIAgora::EnableAudio()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->enableAudio();
}

int UIAgora::DisableAudio()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->disableAudio();
}

int UIAgora::JoinChannel( const FString & ChannelId, const FString & Token, const FString & OptionalInfo, int64 OptionalUserId )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->joinChannel( TCHAR_TO_ANSI( *Token ), TCHAR_TO_ANSI( *ChannelId ), TCHAR_TO_ANSI( *OptionalInfo ), OptionalUserId );
}

int UIAgora::LeaveChannel()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->leaveChannel();
}

int UIAgora::StartPreview()
{
   if( !rtcEngine )
      return -1;

   return rtcEngine->startPreview();
}

int UIAgora::StopPreview()
{
   if( !rtcEngine )
      return -1;

   return rtcEngine->stopPreview();
}

int UIAgora::EnableVideo()
{
   if( !rtcEngine )
      return -1;

   return rtcEngine->enableVideo();
}

int UIAgora::DisableVideo()
{
   if( !rtcEngine )
      return -1;

   return rtcEngine->disableVideo();
}

int UIAgora::MuteLocalAudioStream( bool mute )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->muteLocalAudioStream( mute );
}

int UIAgora::MuteLocalVideoStream( bool mute )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->muteLocalVideoStream( mute );
}

int UIAgora::SetEncryptionMode( EENCRYPTION_MODE encriptionMode )
{
   if( !rtcEngine )
      return -1;

   return rtcEngine->setEncryptionMode( convert( encriptionMode ) );
}

int UIAgora::SetEncryptionSecret( const FString& secret )
{
   if( !rtcEngine )
      return -1;

   return rtcEngine->setEncryptionSecret( TCHAR_TO_ANSI( *secret ) );
}

int UIAgora::SetChannelProfile( ECHANNEL_PROFILE_TYPE profile )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setChannelProfile( convert( profile ) );
}

FString UIAgora::GetVersion()
{
   if( !rtcEngine )
   {
      UE_LOG( AgoraEngineLog, Error, TEXT( "UAgoraEngine::getVersion - Failed to get pointer to the library" ) );
      return "";
   }

   int build = 0;
   const char* version = rtcEngine->getVersion( &build );
   return FString( ANSI_TO_TCHAR( version ) );
}

int UIAgora::SetVideoEncoderConfiguration( const FVideoEncoderConfiguration& configuration )
{
   if( !rtcEngine )
      return -1;

   return rtcEngine->setVideoEncoderConfiguration( convert( configuration ) );
}

int UIAgora::StartEchoTest( int intervalInSeconds )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->startEchoTest( intervalInSeconds );
}

int UIAgora::StopEchoTest()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->stopEchoTest();
}

int UIAgora::StopAudioRecording()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->stopAudioRecording();
}

int UIAgora::StopAudioMixing()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->stopAudioMixing();
}

int UIAgora::PauseAudioMixing()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->pauseAudioMixing();
}

int UIAgora::ResumeAudioMixing()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->resumeAudioMixing();
}

int UIAgora::GetAudioMixingPlayoutVolume()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->getAudioMixingPlayoutVolume();
}

int UIAgora::GetAudioMixingPublishVolume()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->getAudioMixingPublishVolume();
}

int UIAgora::GetAudioMixingDuration()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->getAudioMixingDuration();
}

int UIAgora::GetAudioMixingCurrentPosition()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->getAudioMixingCurrentPosition();
}

int UIAgora::GetEffectsVolume()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->getEffectsVolume();
}

int UIAgora::StopAllEffects()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->stopAllEffects();
}

int UIAgora::PauseAllEffects()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->pauseAllEffects();
}

int UIAgora::ResumeAllEffects()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->resumeAllEffects();
}

int UIAgora::EnableLastmileTest()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->enableLastmileTest();
}

int UIAgora::DisableLastmileTest()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->disableLastmileTest();
}

int UIAgora::StopLastmileProbeTest()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->stopLastmileProbeTest();
}

int UIAgora::ClearVideoWatermarks()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->clearVideoWatermarks();
}

int UIAgora::StopChannelMediaRelay()
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->stopChannelMediaRelay();
}

int UIAgora::EnableLocalAudio( bool enabled )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->enableLocalAudio( enabled );
}

int UIAgora::MuteAllRemoteAudioStreams( bool mute )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->muteAllRemoteAudioStreams( mute );
}

int UIAgora::SetDefaultMuteAllRemoteAudioStreams( bool mute )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setDefaultMuteAllRemoteAudioStreams( mute );
}

int UIAgora::EnableLocalVideo( bool enabled )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->enableLocalVideo( enabled );
}

int UIAgora::MuteAllRemoteVideoStreams( bool mute )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->muteAllRemoteVideoStreams( mute );
}

int UIAgora::SetDefaultMuteAllRemoteVideoStreams( bool mute )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setDefaultMuteAllRemoteVideoStreams( mute );
}

int UIAgora::EnableSoundPositionIndication( bool enabled )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->enableSoundPositionIndication( enabled );
}

int UIAgora::EnableDualStreamMode( bool enabled )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->enableDualStreamMode( enabled );
}

int UIAgora::EnableWebSdkInteroperability( bool enabled )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->enableWebSdkInteroperability( enabled );
}

int UIAgora::AdjustAudioMixingVolume( int volume )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->adjustAudioMixingVolume( volume );
}

int UIAgora::AdjustAudioMixingPlayoutVolume( int volume )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->adjustAudioMixingPlayoutVolume( volume );
}

int UIAgora::AdjustAudioMixingPublishVolume( int volume )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->adjustAudioMixingPublishVolume( volume );
}

int UIAgora::SetEffectsVolume( int volume )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setEffectsVolume( volume );
}

int UIAgora::SetVolumeOfEffect( int soundId, int volume )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setVolumeOfEffect( soundId, volume );
}

int UIAgora::StopEffect( int soundId )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->stopEffect( soundId );
}

int UIAgora::UnloadEffect( int soundId )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->unloadEffect( soundId );
}

int UIAgora::PauseEffect( int soundId )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->pauseEffect( soundId );
}

int UIAgora::ResumeEffect( int soundId )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->resumeEffect( soundId );
}

int UIAgora::SetLocalVoicePitch( float pitch )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLocalVoicePitch( pitch );
}

int UIAgora::SetLogFilter( int64 filter )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLogFilter( filter );
}

int UIAgora::SetLogFileSize( int64 fileSizeInKBytes )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLogFileSize( fileSizeInKBytes );
}

int UIAgora::EnableAudioVolumeIndication( int interval, int smooth, bool report_vad )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->enableAudioVolumeIndication( interval, smooth, report_vad );
}

int UIAgora::SetExternalAudioSource( bool enabled, int sampleRate, int channels )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setExternalAudioSource( enabled, sampleRate, channels );
}

int UIAgora::SetExternalAudioSink( bool enabled, int sampleRate, int channels )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setExternalAudioSink( enabled, sampleRate, channels );
}

int UIAgora::SetMixedAudioFrameParameters( int sampleRate, int samplesPerCall )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setMixedAudioFrameParameters( sampleRate, samplesPerCall );
}

int UIAgora::AdjustRecordingSignalVolume( int volume )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->adjustRecordingSignalVolume( volume );
}

int UIAgora::AdjustPlaybackSignalVolume( int volume )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->adjustPlaybackSignalVolume( volume );
}

int UIAgora::SwitchChannel( const FString& token, const FString& channelId )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->switchChannel( TCHAR_TO_ANSI( *token ), TCHAR_TO_ANSI( *channelId ) );
}

int UIAgora::RenewToken( const FString& token )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->renewToken( TCHAR_TO_ANSI( *token ) );
}

int UIAgora::RegisterLocalUserAccount( const FString& appId, const FString& userAccount )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->registerLocalUserAccount( TCHAR_TO_ANSI( *appId ), TCHAR_TO_ANSI( *userAccount ) );
}

int UIAgora::JoinChannelWithUserAccount( const FString& token, const FString& channelId, const FString& userAccount )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->joinChannelWithUserAccount( TCHAR_TO_ANSI( *token ), TCHAR_TO_ANSI( *channelId ), TCHAR_TO_ANSI( *userAccount ) );
}

int UIAgora::StartAudioMixing( const FString& filePath, bool loopback, bool replace, int cycle )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->startAudioMixing( TCHAR_TO_ANSI( *filePath ), loopback, replace, cycle );
}

int UIAgora::PreloadEffect( int soundId, const FString& filePath )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->preloadEffect( soundId, TCHAR_TO_ANSI( *filePath ) );
}

int UIAgora::PlayEffect( int soundId, const FString& filePath, int loopCount, float pitch, float pan, int gain, bool publish )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->playEffect( soundId, TCHAR_TO_ANSI( *filePath ), loopCount, pitch, pan, gain, publish );
}

int UIAgora::SetLogFile( const FString& filePath )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLogFile( TCHAR_TO_ANSI( *filePath ) );
}

int UIAgora::Rate( const FString& callId, int rating, const FString& description )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->rate( TCHAR_TO_ANSI( *callId ), rating, TCHAR_TO_ANSI( *description ) );
}

int UIAgora::Complain( const FString& callId, const FString& description )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->complain( TCHAR_TO_ANSI( *callId ), TCHAR_TO_ANSI( *description ) );
}

FString UIAgora::GetErrorDescription( int code )
{
   if( !rtcEngine )
      return "";
   return  FString( ANSI_TO_TCHAR( rtcEngine->getErrorDescription( code ) ) );
}

int UIAgora::SendStreamMessage( int streamId, const FString& data, int length )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->sendStreamMessage( streamId, TCHAR_TO_ANSI( *data ), length );
}

int UIAgora::AddPublishStreamUrl( const FString& url, bool transcodingEnabled )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->addPublishStreamUrl( TCHAR_TO_ANSI( *url ), transcodingEnabled );
}

int UIAgora::RemovePublishStreamUrl( const FString& url )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->removePublishStreamUrl( TCHAR_TO_ANSI( *url ) );
}

int UIAgora::RemoveInjectStreamUrl( const FString& url )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->removeInjectStreamUrl( TCHAR_TO_ANSI( *url ) );
}

int UIAgora::MuteRemoteAudioStream( int64 userId, bool mute )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->muteRemoteAudioStream( userId, mute );
}

int UIAgora::MuteRemoteVideoStream( int64 userId, bool mute )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->muteRemoteVideoStream( userId, mute );
}

int UIAgora::SetRemoteVoicePosition( int64 uid, float pan, float gain )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setRemoteVoicePosition( uid, pan, gain );
}

int UIAgora::SetCameraCapturerConfiguration( const FCameraCapturerConfiguration& config )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setCameraCapturerConfiguration( convert( config ) );
}

int UIAgora::SetClientRole( ECLIENT_ROLE_TYPE role )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setClientRole( convert( role ) );
}

int UIAgora::SetRemoteUserPriority( int64 uid, EPRIORITY_TYPE userPriority )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setRemoteUserPriority( uid, convert( userPriority ) );
}

int UIAgora::SetAudioProfile( EAUDIO_PROFILE_TYPE profile, EAUDIO_SCENARIO_TYPE scenario )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setAudioProfile( convert( profile ), convert( scenario ) );
}

int UIAgora::SetRemoteVideoStreamType( int64 userId, EREMOTE_VIDEO_STREAM_TYPE streamType )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setRemoteVideoStreamType( userId, convert( streamType ) );
}

int UIAgora::SetRemoteDefaultVideoStreamType( EREMOTE_VIDEO_STREAM_TYPE streamType )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setRemoteDefaultVideoStreamType( convert( streamType ) );
}

int UIAgora::SetLocalVoiceEqualization( EAUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLocalVoiceEqualization( convert( bandFrequency ), bandGain );
}

int UIAgora::SetLocalVoiceReverb( EAUDIO_REVERB_TYPE reverbKey, int value )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLocalVoiceReverb( convert( reverbKey ), value );
}

int UIAgora::SetLocalVoiceChanger( EVOICE_CHANGER_PRESET voiceChanger )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLocalVoiceChanger( convert( voiceChanger ) );
}

int UIAgora::SetLocalVoiceReverbPreset( EAUDIO_REVERB_PRESET reverbPreset )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLocalVoiceReverbPreset( convert( reverbPreset ) );
}

int UIAgora::SetLocalRenderMode( ERENDER_MODE_TYPE renderMode )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLocalRenderMode( convert( renderMode ) );
}

int UIAgora::SetRemoteRenderMode( int64 userId, ERENDER_MODE_TYPE renderMode )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setRemoteRenderMode( userId, convert( renderMode ) );
}

int UIAgora::SetLocalVideoMirrorMode( EVIDEO_MIRROR_MODE_TYPE mirrorMode )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLocalVideoMirrorMode( convert( mirrorMode ) );
}

int UIAgora::SetRecordingAudioFrameParameters( int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setRecordingAudioFrameParameters( sampleRate, channel, convert( mode ), samplesPerCall );
}

int UIAgora::SetPlaybackAudioFrameParameters( int sampleRate, int channel, ERAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setPlaybackAudioFrameParameters( sampleRate, channel, convert( mode ), samplesPerCall );
}

int UIAgora::SetLocalPublishFallbackOption( ESTREAM_FALLBACK_OPTIONS option )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLocalPublishFallbackOption( convert( option ) );
}

int UIAgora::SetRemoteSubscribeFallbackOption( ESTREAM_FALLBACK_OPTIONS option )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setRemoteSubscribeFallbackOption( convert( option ) );
}

int UIAgora::StartAudioRecording( const FString& filePath, int sampleRate, EAUDIO_RECORDING_QUALITY_TYPE quality )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->startAudioRecording( TCHAR_TO_ANSI( *filePath ), sampleRate, convert( quality ) );
}

ECONNECTION_STATE_TYPE UIAgora::GetConnectionState()
{
   if( !rtcEngine )
      return CONNECTION_STATE_FAILED;
   return convert( rtcEngine->getConnectionState() );
}

int UIAgora::GetUserInfoByUserAccount( const FString& userAccount, FAgoraUserInfo& userInfo )
{
   if( !rtcEngine )
      return -1;
   
   agora::rtc::UserInfo uInfo;
   int ret = rtcEngine->getUserInfoByUserAccount( TCHAR_TO_ANSI( *userAccount ), &uInfo );
   userInfo = convert( uInfo );
   return ret;
}

int UIAgora::GetUserInfoByUid( int64 uid, FAgoraUserInfo& userInfo )
{
   if( !rtcEngine )
      return -1;

   agora::rtc::UserInfo uInfo;
   int ret = rtcEngine->getUserInfoByUid( uid, &uInfo );
   userInfo = convert( uInfo );
   return ret;
}

int UIAgora::SetupLocalVideo( const FVideoCanvas& canvas )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setupLocalVideo( convert( canvas ) );
}

int UIAgora::SetupRemoteVideo( const FVideoCanvas& canvas )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setupRemoteVideo( convert( canvas ) );
}

int UIAgora::SetAudioMixingPosition( int pos )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setAudioMixingPosition( pos );
}

int UIAgora::StartLastmileProbeTest( const FLastmileProbeConfig& config )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->startLastmileProbeTest( convert( config ) );
}

int UIAgora::CreateDataStream( int& Id, bool reliable, bool ordered )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->createDataStream( &Id, reliable, ordered );
}

int UIAgora::SetLiveTranscoding( const FLiveTranscoding& transcoding )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setLiveTranscoding( transcoding.convert( users, watermark, backgroundImage ) );
}

int UIAgora::AddVideoWatermark( const FString& watermarkUrl, const FWatermarkOptions& options )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->addVideoWatermark( TCHAR_TO_ANSI( *watermarkUrl ), convert( options ) );
}

int UIAgora::SetBeautyEffectOptions( bool enabled, FBeautyOptions options )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->setBeautyEffectOptions( enabled, convert( options ) );
}

int UIAgora::AddInjectStreamUrl( const FString& url, const FInjectStreamConfig& config )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->addInjectStreamUrl( TCHAR_TO_ANSI( *url ), convert( config ) );
}

int UIAgora::StartChannelMediaRelay( const FChannelMediaRelayConfiguration& configuration )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->startChannelMediaRelay( configuration.convert( srcInfo, destInfos ) );
}

int UIAgora::UpdateChannelMediaRelay( const FChannelMediaRelayConfiguration& configuration )
{
   if( !rtcEngine )
      return -1;
   return rtcEngine->updateChannelMediaRelay( configuration.convert( srcInfo, destInfos ) );
}

int UIAgora::GetCallId( FString& callId )
{
   if( !rtcEngine )
      return -1;
   agora::util::AString str;
   int ret = rtcEngine->getCallId( str );
   callId = FString( ANSI_TO_TCHAR( str.get()->c_str() ) );
   return ret;
}

//platform dependent functions
int UIAgora::SwitchCamera( ECAMERA_DIRECTION direction )
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
   if( !rtcEngine )
      return -1;
   return rtcEngine->switchCamera( convert( direction ) );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::switchCamera - This function is available only on android or iOS device" ) );
   return -1;
#endif
}

int UIAgora::SetDefaultAudioRouteToSpeakerphone( bool defaultToSpeaker )
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
   if( !rtcEngine )
      return -1;
   return rtcEngine->setDefaultAudioRouteToSpeakerphone( defaultToSpeaker );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::setDefaultAudioRouteToSpeakerphone - This function is available only on android or iOS device" ) );
   return -1;
#endif
}

int UIAgora::SetEnableSpeakerphone( bool speakerOn )
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
   if( !rtcEngine )
      return -1;
   return rtcEngine->setEnableSpeakerphone( speakerOn );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::setEnableSpeakerphone - This function is available only on android or iOS device" ) );
   return -1;
#endif
}

int UIAgora::SetInEarMonitoringVolume( int volume )
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
   if( !rtcEngine )
      return -1;
   return rtcEngine->setInEarMonitoringVolume( volume );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::setInEarMonitoringVolume - This function is available only on android or iOS device" ) );
   return -1;
#endif
}

bool UIAgora::IsSpeakerphoneEnabled()
{
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
   if( !rtcEngine )
      return false;
   return rtcEngine->isSpeakerphoneEnabled();
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::isSpeakerphoneEnabled - This function is available only on android or iOS device" ) );
   return false;
#endif
}

int UIAgora::SetAudioSessionOperationRestriction( EAUDIO_SESSION_OPERATION_RESTRICTION restriction )
{
#if (defined(__APPLE__) && TARGET_OS_IOS)
   if( !rtcEngine )
      return -1;
   return rtcEngine->setAudioSessionOperationRestriction( convert( restriction ) );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::setAudioSessionOperationRestriction - This function is available only on iOS devices" ) );
   return -1;
#endif
}

int UIAgora::StartScreenCaptureByDisplayId(
   int64 displayId,
   const FRectangle& regionRect,
   const FScreenCaptureParameters& captureParams )
{
#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
   if( !rtcEngine )
      return -1;
   return rtcEngine->startScreenCaptureByDisplayId( displayId, convert( regionRect ), convert( captureParams ) );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::startScreenCaptureByDisplayId - This function is available only on macOS devices" ) );
   return -1;
#endif
}

int UIAgora::StartScreenCaptureByScreenRect(
   const FRectangle& screenRect,
   const FRectangle& regionRect,
   const FScreenCaptureParameters& captureParams )
{
#if defined(_WIN32)
   if( !rtcEngine )
      return -1;
   return rtcEngine->startScreenCaptureByScreenRect( convert( screenRect ), convert( regionRect ), convert( captureParams ) );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::startScreenCaptureByScreenRect - This function is available only on Windows devices" ) );
   return -1;
#endif
}

int UIAgora::SetScreenCaptureContentHint( EVIDEO_CONTENT_HINT contentHint )
{
#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
   if( !rtcEngine )
      return -1;
   return rtcEngine->setScreenCaptureContentHint( convert( contentHint ) );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::setScreenCaptureContentHint - This function is available only on Mac and Windows devices" ) );
   return -1;
#endif
}

int UIAgora::UpdateScreenCaptureParameters( const FScreenCaptureParameters& captureParams )
{
#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
   if( !rtcEngine )
      return -1;
   return rtcEngine->updateScreenCaptureParameters( convert( captureParams ) );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::updateScreenCaptureParameters - This function is available only on Mac and Windows devices" ) );
   return -1;
#endif

}

int UIAgora::UpdateScreenCaptureRegion( const FRectangle& regionRect )
{
#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
   if( !rtcEngine )
      return -1;
   return rtcEngine->updateScreenCaptureRegion( convert( regionRect ) );
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::updateScreenCaptureRegion - This function is available only on Mac and Windows devices" ) );
   return -1;
#endif

}

int UIAgora::StopScreenCapture()
{
#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
   if( !rtcEngine )
      return -1;
   return rtcEngine->stopScreenCapture();
#else
   UE_LOG( AgoraEngineLog, Error, TEXT( "UIAgora::stopScreenCapture - This function is available only on Mac and Windows devices" ) );
   return -1;
#endif
}

//////////////////////// Audio Manager ////////////////////////////////////////////////////////////

TArray<FMediaDevice> UIAgora::GetAudioRecordingDevices()
{
   if( !audioManager )
      return TArray<FMediaDevice>();
   return audioManager->getRecordingDevices();
}

TArray<FMediaDevice> UIAgora::GetAudioPlaybackDevices()
{
   if( !audioManager )
      return TArray<FMediaDevice>();
   return audioManager->getPlaybackDevices();
}

int UIAgora::SetCurrentAudioRecordingDevice( const FString& DeviceId )
{
   if( !audioManager )
      return -1;

   return audioManager->setCurrentRecordingDevice( DeviceId );
}

int UIAgora::SetCurrentAudioPlaybackDevice( const FString & DeviceId )
{
   if( !audioManager )
      return -1;

   return audioManager->setCurrentPlaybackDevice( DeviceId );
}

int UIAgora::GetCurrentAudioRecordingDevice( int& Index, FString& DeviceName, FString& DeviceId )
{
   if( !audioManager )
      return -1;

   return audioManager->getCurrentRecordingDevice( Index, DeviceName, DeviceId );
}

int UIAgora::GetCurrentAudioPlaybackDevice( int& Index, FString& DeviceName, FString& DeviceId )
{
   if( !audioManager )
      return -1;

   return audioManager->getCurrentPlaybackDevice( Index, DeviceName, DeviceId );
}

int UIAgora::GetAudioRecordingDeviceCount()
{
   if( !audioManager )
      return -1;
   return audioManager->getRecordingDeviceCount();
}

int UIAgora::GetAudioPlaybackDeviceCount()
{
   if( !audioManager )
      return -1;
   return audioManager->getPlaybackDeviceCount();
}

int UIAgora::EnumerateAudioRecordingDevices()
{
   if( !audioManager )
      return -1;
   return audioManager->enumerateRecordingDevices();
}

int UIAgora::EnumerateAudioPlaybackDevices()
{
   if( !audioManager )
      return -1;
   return audioManager->enumeratePlaybackDevices();
}

int UIAgora::IsApplicationMuted( bool & Muted )
{
   if( !audioManager )
      return -1;
   return audioManager->isApplicationMuted( Muted );
}

int UIAgora::SetApplicationMuted( bool Muted )
{
   if( !audioManager )
      return -1;
   return audioManager->setApplicationMuted( Muted );
}

int UIAgora::SetApplicationVolume( int Volume )
{
   if( !audioManager )
      return -1;
   return audioManager->setApplicationVolume( Volume );
}

int UIAgora::GetApplicationVolume( int & Volume )
{
   if( !audioManager )
      return -1;
   return audioManager->getApplicationVolume( Volume );
}

int UIAgora::IsAudioRecordingDeviceMuted( bool & Muted )
{
   if( !audioManager )
      return -1;
   return audioManager->isRecordingDeviceMuted( Muted );
}

int UIAgora::IsAudioPlaybackDeviceMuted( bool & Muted )
{
   if( !audioManager )
      return -1;
   return audioManager->isPlaybackDeviceMuted( Muted );
}

int UIAgora::SetAudioRecordingDeviceMuted( bool Muted )
{
   if( !audioManager )
      return -1;
   return audioManager->setRecordingDeviceMuted( Muted );
}

int UIAgora::SetAudioPlaybackDeviceMuted( bool Muted )
{
   if( !audioManager )
      return -1;
   return audioManager->setPlaybackDeviceMuted( Muted );
}

int UIAgora::GetAudioRecordingDeviceVolume( int & Volume )
{
   if( !audioManager )
      return -1;
   return audioManager->getRecordingDeviceVolume( Volume );
}

int UIAgora::GetAudioPlaybackDeviceVolume( int & Volume )
{
   if( !audioManager )
      return -1;
   return audioManager->getPlaybackDeviceVolume( Volume );
}

int UIAgora::SetAudioRecordingDeviceVolume( int Volume )
{
   if( !audioManager )
      return -1;
   return audioManager->setRecordingDeviceVolume( Volume );
}

int UIAgora::SetAudioPlaybackDeviceVolume( int Volume )
{
   if( !audioManager )
      return -1;
   return audioManager->setPlaybackDeviceVolume( Volume );
}

int UIAgora::StartAudioRecordingDeviceTest( int IndicationInterval )
{
   if( !audioManager )
      return -1;
   return audioManager->startRecordingDeviceTest( IndicationInterval );
}

int UIAgora::StopAudioRecordingDeviceTest()
{
   if( !audioManager )
      return -1;
   return audioManager->stopRecordingDeviceTest();
}

int UIAgora::StartAudioPlaybackDeviceTest( const FString& testAudioFilePath )
{
   if( !audioManager )
      return -1;
   return audioManager->startPlaybackDeviceTest( testAudioFilePath );
}

int UIAgora::StopAudioPlaybackDeviceTest()
{
   if( !audioManager )
      return -1;
   return audioManager->stopPlaybackDeviceTest();
}

int UIAgora::StartAudioDeviceLoopbackTest( int IndicationInterval )
{
   if( !audioManager )
      return -1;
   return audioManager->startAudioDeviceLoopbackTest( IndicationInterval );
}

int UIAgora::StopAudioDeviceLoopbackTest()
{
   if( !audioManager )
      return -1;
   return audioManager->stopAudioDeviceLoopbackTest();
}

/////////////////////////////////////////Video Manager////////////////////////////////////////////////////////////
TArray<FMediaDevice> UIAgora::GetVideoRecordingDevices()
{
   if( !videoManager )
      return TArray<FMediaDevice>();
   return videoManager->getRecordingDevices();
}

int UIAgora::GetVideoRecordingDevice( int Index, FString & DeviceName, FString & DeviceId )
{
   if( !videoManager )
      return -1;
   return videoManager->getRecordingDevice( Index, DeviceName, DeviceId );
}

int UIAgora::SetCurrentVideoRecordingDevice( const FString& DeviceId )
{
   if( !videoManager )
      return -1;
   return videoManager->setCurrentRecordingDevice( DeviceId );
}

int UIAgora::GetCurrentVideoRecordingDevice( int& Index, FString& DeviceName, FString& DeviceId )
{
   if( !videoManager )
      return -1;
   return videoManager->getCurrentRecordingDevice( Index, DeviceName, DeviceId );
}

int UIAgora::GetVideoRecordingDeviceCount()
{
   if( !videoManager )
      return -1;
   return videoManager->getRecordingDeviceCount();
}

int UIAgora::EnumerateVideoRecordingDevices()
{
   if( !videoManager )
      return -1;
   return videoManager->enumerateRecordingDevices();
}

/////////////////////////////////////////////////////////////////////////////////

UAgora::UAgora()
   : UIAgora()
{
   OnLeaveChannelDelegate.AddDynamic( this, &UAgora::OnLeaveChannel );
   OnUserOfflineDelegate.AddDynamic( this, &UAgora::OnUserOffline );
}

agora::blueprints::IVideoFrameObserver* UAgora::createVideoFrameObserver()
{
   return new agora::blueprints::VideoFrameObserver( this );
}


agora::blueprints::IAudioFrameObserver* UAgora::createAudioFrameObserver()
{
   return nullptr;
}

void UAgora::OnLeaveChannel( const FRtcStats& Stats )
{
   if( !videoFrameObserver )
      return;
   agora::blueprints::VideoFrameObserver* frameObserver = ( agora::blueprints::VideoFrameObserver* )( videoFrameObserver );
   if( !frameObserver )
      return;
   frameObserver->clearFrameBuffers();
}

void UAgora::OnUserOffline( int64 userId, EUSER_OFFLINE_REASON_TYPE reason )
{
   if( !videoFrameObserver )
      return;
   agora::blueprints::VideoFrameObserver* frameObserver = ( agora::blueprints::VideoFrameObserver* )( videoFrameObserver );
   if( !frameObserver )
      return;
   frameObserver->removeUserFrameBuffer( userId );
}