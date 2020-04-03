#include "UECompatibility.h"

FRtcStats::FRtcStats()
   : duration( 0 )
   , TxBytes( 0 )
   , RxBytes( 0 )
   , TxAudioBytes( 0 )
   , TxVideoBytes( 0 )
   , RxAudioBytes( 0 )
   , RxVideoBytes( 0 )
   , TxKBitRate( 0 )
   , RxKBitRate( 0 )
   , RxAudioKBitRate( 0 )
   , TxAudioKBitRate( 0 )
   , RxVideoKBitRate( 0 )
   , TxVideoKBitRate( 0 )
   , LastmileDelay( 0 )
   , TxPacketLossRate( 0 )
   , RxPacketLossRate( 0 )
   , UserCount( 0 )
   , cpuAppUsage( 0 )
   , cpuTotalUsage( 0 )
{}

FRtcStats::FRtcStats( const agora::rtc::RtcStats& stats )
   : duration( stats.duration )
   , TxBytes( stats.txBytes )
   , RxBytes( stats.rxBytes )
   , TxAudioBytes( stats.txAudioBytes )
   , TxVideoBytes( stats.txVideoBytes )
   , RxAudioBytes( stats.rxAudioBytes )
   , RxVideoBytes( stats.rxVideoBytes )
   , TxKBitRate( stats.txKBitRate )
   , RxKBitRate( stats.rxKBitRate )
   , RxAudioKBitRate( stats.rxAudioKBitRate )
   , TxAudioKBitRate( stats.txAudioKBitRate )
   , RxVideoKBitRate( stats.rxVideoKBitRate )
   , TxVideoKBitRate( stats.txVideoKBitRate )
   , LastmileDelay( stats.lastmileDelay )
   , TxPacketLossRate( stats.txPacketLossRate )
   , RxPacketLossRate( stats.rxPacketLossRate )
   , UserCount( stats.userCount )
   , cpuAppUsage( stats.cpuAppUsage )
   , cpuTotalUsage( stats.cpuTotalUsage )
{}

FRtcStats & FRtcStats::operator=( const agora::rtc::RtcStats& stats )
{
   duration = stats.duration;
   TxBytes = stats.txBytes;
   RxBytes = stats.rxBytes;
   TxAudioBytes = stats.txAudioBytes;
   TxVideoBytes = stats.txVideoBytes;
   RxAudioBytes = stats.rxAudioBytes;
   RxVideoBytes = stats.rxVideoBytes;
   TxKBitRate = stats.txKBitRate;
   RxKBitRate = stats.rxKBitRate;
   RxAudioKBitRate = stats.rxAudioKBitRate;
   TxAudioKBitRate = stats.txAudioKBitRate;
   RxVideoKBitRate = stats.rxVideoKBitRate;
   TxVideoKBitRate = stats.txVideoKBitRate;
   LastmileDelay = stats.lastmileDelay;
   TxPacketLossRate = stats.txPacketLossRate;
   RxPacketLossRate = stats.rxPacketLossRate;
   UserCount = stats.userCount;
   cpuAppUsage = stats.cpuAppUsage;
   cpuTotalUsage = stats.cpuTotalUsage;
   return *this;
}

FRtcStats::operator agora::rtc::RtcStats()
{
   agora::rtc::RtcStats statistics;
   statistics.duration = duration;
   statistics.txBytes = TxBytes;
   statistics.rxBytes = RxBytes;
   statistics.txAudioBytes = TxAudioBytes;
   statistics.txVideoBytes = TxVideoBytes;
   statistics.rxAudioBytes = RxAudioBytes;
   statistics.rxVideoBytes = RxVideoBytes;
   statistics.txKBitRate = TxKBitRate;
   statistics.rxKBitRate = RxKBitRate;
   statistics.rxAudioKBitRate = RxAudioKBitRate;
   statistics.txAudioKBitRate = TxAudioKBitRate;
   statistics.rxVideoKBitRate = RxVideoKBitRate;
   statistics.txVideoKBitRate = TxVideoKBitRate;
   statistics.lastmileDelay = LastmileDelay;
   statistics.txPacketLossRate = TxPacketLossRate;
   statistics.rxPacketLossRate = RxPacketLossRate;
   statistics.userCount = UserCount;
   statistics.cpuAppUsage = cpuAppUsage;
   statistics.cpuTotalUsage = cpuTotalUsage;
   return statistics;
}

EVIDEO_FRAME_TYPE convert( agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE frameType )
{
   switch( frameType )
   {
      case agora::media::IVideoFrameObserver::FRAME_TYPE_YUV420: return FRAME_TYPE_YUV420;
      case agora::media::IVideoFrameObserver::FRAME_TYPE_YUV422: return FRAME_TYPE_YUV422;
      case agora::media::IVideoFrameObserver::FRAME_TYPE_RGBA:   return FRAME_TYPE_RGBA;
      default: return FRAME_TYPE_NONE;
   }
}

agora::rtc::CHANNEL_PROFILE_TYPE convert( ECHANNEL_PROFILE_TYPE profileType )
{
   switch( profileType )
   {
      case CHANNEL_PROFILE_COMMUNICATION:       return agora::rtc::CHANNEL_PROFILE_COMMUNICATION;
      case CHANNEL_PROFILE_LIVE_BROADCASTING:   return agora::rtc::CHANNEL_PROFILE_LIVE_BROADCASTING;
      case CHANNEL_PROFILE_GAME:                return agora::rtc::CHANNEL_PROFILE_GAME;
      default: return agora::rtc::CHANNEL_PROFILE_COMMUNICATION;
   }
}

const char* convert( EENCRYPTION_MODE encryptionMode )
{
   switch( encryptionMode )
   {
      case ENCRYPTION_MODE_AES_128_XTC: return "aes-128-xts";
      case ENCRYPTION_MODE_AES_128_ECB: return "aes-128-ecb";
      case ENCRYPTION_MODE_AES_256_XTS: return "aes-256-xts";
      default: return "";
   }
}

EUSER_OFFLINE_REASON_TYPE convert( agora::rtc::USER_OFFLINE_REASON_TYPE reasonType )
{
   switch( reasonType )
   {
      case agora::rtc::USER_OFFLINE_QUIT:            return USER_OFFLINE_QUIT;
      case agora::rtc::USER_OFFLINE_DROPPED:         return USER_OFFLINE_DROPPED;
      case agora::rtc::USER_OFFLINE_BECOME_AUDIENCE: return USER_OFFLINE_BECOME_AUDIENCE;
      default: return USER_OFFLINE_NONE;
   }
}

agora::rtc::VideoEncoderConfiguration convert( const FVideoEncoderConfiguration& configuration )
{
   agora::rtc::VideoEncoderConfiguration conf;
   conf.dimensions.width = configuration.Dimensions.Width;
   conf.dimensions.height = configuration.Dimensions.Height;
   conf.frameRate = convert( configuration.FrameRate );
   conf.minFrameRate = configuration.MinFrameRate;
   conf.bitrate = configuration.Bitrate;
   conf.minBitrate = configuration.MinBitrate;
   conf.orientationMode = convert( configuration.OrientationMode );
   conf.degradationPreference = convert( configuration.DegradationPreference );
   return conf;
}

agora::rtc::CameraCapturerConfiguration convert( const FCameraCapturerConfiguration& configuration )
{
   agora::rtc::CameraCapturerConfiguration conf;
   conf.preference = convert( configuration.Preference );
   return conf;
}

agora::rtc::CAPTURER_OUTPUT_PREFERENCE convert( ECAPTURER_OUTPUT_PREFERENCE capturerOutputPreference )
{
   switch( capturerOutputPreference )
   {
      case CAPTURER_OUTPUT_PREFERENCE_AUTO: return agora::rtc::CAPTURER_OUTPUT_PREFERENCE_AUTO;
      case CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE: return agora::rtc::CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE;
      case CAPTURER_OUTPUT_PREFERENCE_PREVIEW: return agora::rtc::CAPTURER_OUTPUT_PREFERENCE_PREVIEW;
      default: return agora::rtc::CAPTURER_OUTPUT_PREFERENCE_AUTO;
   }
}

agora::rtc::AUDIO_PROFILE_TYPE convert( EAUDIO_PROFILE_TYPE audioProfileType )
{
   switch( audioProfileType )
   {
      case AUDIO_PROFILE_DEFAULT: return agora::rtc::AUDIO_PROFILE_DEFAULT;
      case AUDIO_PROFILE_SPEECH_STANDARD: return agora::rtc::AUDIO_PROFILE_SPEECH_STANDARD;
      case AUDIO_PROFILE_MUSIC_STANDARD: return agora::rtc::AUDIO_PROFILE_MUSIC_STANDARD;
      case AUDIO_PROFILE_MUSIC_STANDARD_STEREO: return agora::rtc::AUDIO_PROFILE_MUSIC_STANDARD_STEREO;
      case AUDIO_PROFILE_MUSIC_HIGH_QUALITY: return agora::rtc::AUDIO_PROFILE_MUSIC_HIGH_QUALITY;
      case AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO: return agora::rtc::AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO;
      case AUDIO_PROFILE_IOT: return agora::rtc::AUDIO_PROFILE_IOT;
      case AUDIO_PROFILE_NUM: return agora::rtc::AUDIO_PROFILE_NUM;
      default: return agora::rtc::AUDIO_PROFILE_DEFAULT;
   }
}

agora::rtc::AUDIO_SCENARIO_TYPE convert( EAUDIO_SCENARIO_TYPE audioScenarioType )
{
   switch( audioScenarioType )
   {
      case AUDIO_SCENARIO_DEFAULT: return agora::rtc::AUDIO_SCENARIO_DEFAULT;
      case AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT: return agora::rtc::AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT;
      case AUDIO_SCENARIO_EDUCATION: return agora::rtc::AUDIO_SCENARIO_EDUCATION;
      case AUDIO_SCENARIO_GAME_STREAMING: return agora::rtc::AUDIO_SCENARIO_GAME_STREAMING;
      case AUDIO_SCENARIO_SHOWROOM: return agora::rtc::AUDIO_SCENARIO_SHOWROOM;
      case AUDIO_SCENARIO_CHATROOM_GAMING: return agora::rtc::AUDIO_SCENARIO_CHATROOM_GAMING;
      case AUDIO_SCENARIO_IOT: return agora::rtc::AUDIO_SCENARIO_IOT;
      case AUDIO_SCENARIO_NUM: return agora::rtc::AUDIO_SCENARIO_NUM;
      default: return agora::rtc::AUDIO_SCENARIO_DEFAULT;
   }
}

agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY convert( EAUDIO_EQUALIZATION_BAND_FREQUENCY audioEqualizationBandFrequency )
{
   switch( audioEqualizationBandFrequency )
   {
      case AUDIO_EQUALIZATION_BAND_31: return agora::rtc::AUDIO_EQUALIZATION_BAND_31;
      case AUDIO_EQUALIZATION_BAND_62: return agora::rtc::AUDIO_EQUALIZATION_BAND_62;
      case AUDIO_EQUALIZATION_BAND_125: return agora::rtc::AUDIO_EQUALIZATION_BAND_125;
      case AUDIO_EQUALIZATION_BAND_250: return agora::rtc::AUDIO_EQUALIZATION_BAND_250;
      case AUDIO_EQUALIZATION_BAND_500: return agora::rtc::AUDIO_EQUALIZATION_BAND_500;
      case AUDIO_EQUALIZATION_BAND_1K: return agora::rtc::AUDIO_EQUALIZATION_BAND_1K;
      case AUDIO_EQUALIZATION_BAND_2K: return agora::rtc::AUDIO_EQUALIZATION_BAND_2K;
      case AUDIO_EQUALIZATION_BAND_4K: return agora::rtc::AUDIO_EQUALIZATION_BAND_4K;
      case AUDIO_EQUALIZATION_BAND_8K: return agora::rtc::AUDIO_EQUALIZATION_BAND_8K;
      case AUDIO_EQUALIZATION_BAND_16K: return agora::rtc::AUDIO_EQUALIZATION_BAND_16K;
      default: return agora::rtc::AUDIO_EQUALIZATION_BAND_31;
   }
}

agora::rtc::AUDIO_REVERB_TYPE convert( EAUDIO_REVERB_TYPE audioReverbType )
{
   switch( audioReverbType )
   {
      case AUDIO_REVERB_DRY_LEVEL: return agora::rtc::AUDIO_REVERB_DRY_LEVEL;
      case AUDIO_REVERB_WET_LEVEL: return agora::rtc::AUDIO_REVERB_WET_LEVEL;
      case AUDIO_REVERB_ROOM_SIZE: return agora::rtc::AUDIO_REVERB_ROOM_SIZE;
      case AUDIO_REVERB_WET_DELAY: return agora::rtc::AUDIO_REVERB_WET_DELAY;
      case AUDIO_REVERB_STRENGTH: return agora::rtc::AUDIO_REVERB_STRENGTH;
      default: return agora::rtc::AUDIO_REVERB_DRY_LEVEL;
   }
}

agora::rtc::AUDIO_REVERB_PRESET convert( EAUDIO_REVERB_PRESET audioReverbPreset )
{
   switch( audioReverbPreset )
   {
      case AUDIO_REVERB_OFF: return agora::rtc::AUDIO_REVERB_OFF;
      case AUDIO_REVERB_POPULAR: return agora::rtc::AUDIO_REVERB_POPULAR;
      case AUDIO_REVERB_RNB: return agora::rtc::AUDIO_REVERB_RNB;
      case AUDIO_REVERB_ROCK: return agora::rtc::AUDIO_REVERB_ROCK;
      case AUDIO_REVERB_HIPHOP: return agora::rtc::AUDIO_REVERB_HIPHOP;
      case AUDIO_REVERB_VOCAL_CONCERT: return agora::rtc::AUDIO_REVERB_VOCAL_CONCERT;
      case AUDIO_REVERB_KTV: return agora::rtc::AUDIO_REVERB_KTV;
      case AUDIO_REVERB_STUDIO: return agora::rtc::AUDIO_REVERB_STUDIO;
      default: return agora::rtc::AUDIO_REVERB_OFF;
   }
}

ECLIENT_ROLE_TYPE convert( agora::rtc::CLIENT_ROLE_TYPE clientRoleType )
{
   switch( clientRoleType )
   {
      case agora::rtc::CLIENT_ROLE_BROADCASTER: return CLIENT_ROLE_BROADCASTER;
      case agora::rtc::CLIENT_ROLE_AUDIENCE: return CLIENT_ROLE_AUDIENCE;
      default: return CLIENT_ROLE_BROADCASTER;
   }
}

agora::rtc::CLIENT_ROLE_TYPE convert( ECLIENT_ROLE_TYPE clientRoleType )
{
   switch( clientRoleType )
   {
      case CLIENT_ROLE_BROADCASTER: return agora::rtc::CLIENT_ROLE_BROADCASTER;
      case CLIENT_ROLE_AUDIENCE: return agora::rtc::CLIENT_ROLE_AUDIENCE;
      default: return agora::rtc::CLIENT_ROLE_BROADCASTER;
   }
}

agora::rtc::PRIORITY_TYPE convert( EPRIORITY_TYPE priorityType )
{
   switch( priorityType )
   {
      case PRIORITY_HIGH: return agora::rtc::PRIORITY_HIGH;
      case PRIORITY_NORMAL: return agora::rtc::PRIORITY_NORMAL;
      default: return agora::rtc::PRIORITY_NORMAL;
   }
}

agora::rtc::RENDER_MODE_TYPE convert( ERENDER_MODE_TYPE renderModeType )
{
   switch( renderModeType )
   {
      case RENDER_MODE_HIDDEN: return agora::rtc::RENDER_MODE_HIDDEN;
      case RENDER_MODE_FIT: return agora::rtc::RENDER_MODE_FIT;
      case RENDER_MODE_ADAPTIVE: return agora::rtc::RENDER_MODE_ADAPTIVE;
      default: return agora::rtc::RENDER_MODE_FIT;
   }
}

agora::rtc::REMOTE_VIDEO_STREAM_TYPE convert( EREMOTE_VIDEO_STREAM_TYPE remoteVideoStreamType )
{
   switch( remoteVideoStreamType )
   {
      case REMOTE_VIDEO_STREAM_HIGH: return agora::rtc::REMOTE_VIDEO_STREAM_HIGH;
      case REMOTE_VIDEO_STREAM_LOW: return agora::rtc::REMOTE_VIDEO_STREAM_LOW;
      default: return agora::rtc::REMOTE_VIDEO_STREAM_HIGH;
   }
}

agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE convert( ERAW_AUDIO_FRAME_OP_MODE_TYPE rawAudioFrameOpModeType )
{
   switch( rawAudioFrameOpModeType )
   {
      case RAW_AUDIO_FRAME_OP_MODE_READ_ONLY: return agora::rtc::RAW_AUDIO_FRAME_OP_MODE_READ_ONLY;
      case RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY: return agora::rtc::RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY;
      case RAW_AUDIO_FRAME_OP_MODE_READ_WRITE: return agora::rtc::RAW_AUDIO_FRAME_OP_MODE_READ_WRITE;
      default: return agora::rtc::RAW_AUDIO_FRAME_OP_MODE_READ_ONLY;
   }
}

agora::rtc::STREAM_FALLBACK_OPTIONS convert( ESTREAM_FALLBACK_OPTIONS streamFallbackOptions )
{
   switch( streamFallbackOptions )
   {
      case STREAM_FALLBACK_OPTION_DISABLED: return agora::rtc::STREAM_FALLBACK_OPTION_DISABLED;
      case STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW: return agora::rtc::STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW;
      case STREAM_FALLBACK_OPTION_AUDIO_ONLY: return agora::rtc::STREAM_FALLBACK_OPTION_AUDIO_ONLY;
      default: return agora::rtc::STREAM_FALLBACK_OPTION_DISABLED;
   }
}

agora::rtc::VOICE_CHANGER_PRESET convert( EVOICE_CHANGER_PRESET voiceChangerPreset )
{
   switch( voiceChangerPreset )
   {
      case VOICE_CHANGER_OFF: return agora::rtc::VOICE_CHANGER_OFF;
      case VOICE_CHANGER_OLDMAN: return agora::rtc::VOICE_CHANGER_OLDMAN;
      case VOICE_CHANGER_BABYBOY: return agora::rtc::VOICE_CHANGER_BABYBOY;
      case VOICE_CHANGER_BABYGIRL: return agora::rtc::VOICE_CHANGER_BABYGIRL;
      case VOICE_CHANGER_ZHUBAJIE: return agora::rtc::VOICE_CHANGER_ZHUBAJIE;
      case VOICE_CHANGER_ETHEREAL: return agora::rtc::VOICE_CHANGER_ETHEREAL;
      case VOICE_CHANGER_HULK: return agora::rtc::VOICE_CHANGER_HULK;
      default: return agora::rtc::VOICE_CHANGER_OFF;
   }
}

agora::rtc::VIDEO_MIRROR_MODE_TYPE convert( EVIDEO_MIRROR_MODE_TYPE videoMirrorModeType )
{
   switch( videoMirrorModeType )
   {
      case VIDEO_MIRROR_MODE_AUTO: return agora::rtc::VIDEO_MIRROR_MODE_AUTO;
      case VIDEO_MIRROR_MODE_ENABLED: return agora::rtc::VIDEO_MIRROR_MODE_ENABLED;
      case VIDEO_MIRROR_MODE_DISABLED: return agora::rtc::VIDEO_MIRROR_MODE_DISABLED;
      default: return agora::rtc::VIDEO_MIRROR_MODE_AUTO;
   }
}

agora::rtc::AUDIO_RECORDING_QUALITY_TYPE convert( EAUDIO_RECORDING_QUALITY_TYPE audioRecordingQualityType )
{
   switch( audioRecordingQualityType )
   {
      case AUDIO_RECORDING_QUALITY_LOW: return agora::rtc::AUDIO_RECORDING_QUALITY_LOW;
      case AUDIO_RECORDING_QUALITY_MEDIUM: return agora::rtc::AUDIO_RECORDING_QUALITY_MEDIUM;
      case AUDIO_RECORDING_QUALITY_HIGH: return agora::rtc::AUDIO_RECORDING_QUALITY_HIGH;
      default: return agora::rtc::AUDIO_RECORDING_QUALITY_MEDIUM;
   }
}

ECONNECTION_STATE_TYPE convert( agora::rtc::CONNECTION_STATE_TYPE connectionStateType )
{
   switch( connectionStateType )
   {
      case agora::rtc::CONNECTION_STATE_DISCONNECTED: return CONNECTION_STATE_DISCONNECTED;
      case agora::rtc::CONNECTION_STATE_CONNECTING: return CONNECTION_STATE_CONNECTING;
      case agora::rtc::CONNECTION_STATE_CONNECTED: return CONNECTION_STATE_CONNECTED;
      case agora::rtc::CONNECTION_STATE_RECONNECTING: return CONNECTION_STATE_RECONNECTING;
      case agora::rtc::CONNECTION_STATE_FAILED: return CONNECTION_STATE_FAILED;
      default: return CONNECTION_STATE_FAILED;
   }
}

agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LEVEL convert( ELIGHTENING_CONTRAST_LEVEL lighteningContrastLevel )
{
   switch( lighteningContrastLevel )
   {
      case LIGHTENING_CONTRAST_LOW: return agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LOW;
      case LIGHTENING_CONTRAST_NORMAL: return agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_NORMAL;
      case LIGHTENING_CONTRAST_HIGH: return agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_HIGH;
      default: return agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_NORMAL;
   }
}

agora::rtc::BeautyOptions convert( const FBeautyOptions& beautyOptions )
{
   agora::rtc::BeautyOptions beautyOpt;
   beautyOpt.lighteningLevel = beautyOptions.LighteningLevel;
   beautyOpt.lighteningContrastLevel = convert( beautyOptions.LighteningContrastLevel );
   beautyOpt.smoothnessLevel = beautyOptions.SmoothnessLevel;
   beautyOpt.rednessLevel = beautyOptions.RednessLevel;
   return beautyOpt;
}

agora::rtc::ChannelMediaInfo convert( const FChannelMediaInfo& channelMediaInfo )
{
   agora::rtc::ChannelMediaInfo chMediaInfo;
   chMediaInfo.channelName = TCHAR_TO_ANSI( *channelMediaInfo.ChannelName );
   chMediaInfo.token = TCHAR_TO_ANSI( *channelMediaInfo.Token );
   chMediaInfo.uid = channelMediaInfo.Uid;
   return chMediaInfo;
}

agora::rtc::AUDIO_SAMPLE_RATE_TYPE convert( EAUDIO_SAMPLE_RATE_TYPE audioSampleRateType )
{
   switch( audioSampleRateType )
   {
      case AUDIO_SAMPLE_RATE_32000: return agora::rtc::AUDIO_SAMPLE_RATE_32000;
      case AUDIO_SAMPLE_RATE_44100: return agora::rtc::AUDIO_SAMPLE_RATE_44100;
      case AUDIO_SAMPLE_RATE_48000: return agora::rtc::AUDIO_SAMPLE_RATE_48000;
      default: return agora::rtc::AUDIO_SAMPLE_RATE_44100;
   }
}

agora::rtc::InjectStreamConfig convert( const FInjectStreamConfig& injectStreamConfig )
{
   agora::rtc::InjectStreamConfig injStreamConfig;
   injStreamConfig.audioBitrate = injectStreamConfig.AudioBitrate;
   injStreamConfig.audioChannels = injectStreamConfig.AudioChannels;
   injStreamConfig.audioSampleRate = convert( injectStreamConfig.AudioSampleRate );
   injStreamConfig.height = injectStreamConfig.Height;
   injStreamConfig.videoBitrate = injectStreamConfig.VideoBitrate;
   injStreamConfig.videoFramerate = injectStreamConfig.VideoFramerate;
   injStreamConfig.videoGop = injectStreamConfig.VideoGop;
   injStreamConfig.width = injectStreamConfig.width;
   return injStreamConfig;
}

agora::rtc::LastmileProbeConfig convert( const FLastmileProbeConfig& lastmileProbeConfig )
{
   agora::rtc::LastmileProbeConfig lastmProbeConfig;
   lastmProbeConfig.expectedDownlinkBitrate = lastmileProbeConfig.ExpectedDownlinkBitrate;
   lastmProbeConfig.expectedUplinkBitrate = lastmileProbeConfig.ExpectedUplinkBitrate;
   lastmProbeConfig.probeDownlink = lastmileProbeConfig.ProbeDownlink;
   lastmProbeConfig.probeUplink = lastmileProbeConfig.ProbeUplink;
   return lastmProbeConfig;
}

agora::rtc::VIDEO_CODEC_PROFILE_TYPE convert( EVIDEO_CODEC_PROFILE_TYPE videoCodecProfileType )
{
   switch( videoCodecProfileType )
   {
      case VIDEO_CODEC_PROFILE_BASELINE: return agora::rtc::VIDEO_CODEC_PROFILE_BASELINE;
      case VIDEO_CODEC_PROFILE_MAIN: return agora::rtc::VIDEO_CODEC_PROFILE_MAIN;
      case VIDEO_CODEC_PROFILE_HIGH: return agora::rtc::VIDEO_CODEC_PROFILE_HIGH;
      default: return agora::rtc::VIDEO_CODEC_PROFILE_MAIN;
   }
}

agora::rtc::AUDIO_CODEC_PROFILE_TYPE convert( EAUDIO_CODEC_PROFILE_TYPE audioCodecProfileType )
{
   switch( audioCodecProfileType )
   {
      case AUDIO_CODEC_PROFILE_LC_AAC: return agora::rtc::AUDIO_CODEC_PROFILE_LC_AAC;
      case AUDIO_CODEC_PROFILE_HE_AAC: return agora::rtc::AUDIO_CODEC_PROFILE_HE_AAC;
      default: return agora::rtc::AUDIO_CODEC_PROFILE_LC_AAC;
   }
}

agora::rtc::RtcImage convert( const FRtcImage& rtcImage )
{
   agora::rtc::RtcImage rtcImg;
   rtcImg.height = rtcImage.Height;
   rtcImg.url = TCHAR_TO_ANSI( *rtcImage.Url );
   rtcImg.width = rtcImage.Width;
   rtcImg.x = rtcImage.X;
   rtcImg.y = rtcImage.Y;
   return rtcImg;
}

agora::rtc::TranscodingUser convert( const FAgoraTranscodingUser& transcodingUser )
{
   agora::rtc::TranscodingUser transUser;
   transUser.alpha = transcodingUser.Alpha;
   transUser.audioChannel = transcodingUser.AudioChannel;
   transUser.height = transcodingUser.Height;
   transUser.uid = transcodingUser.Uid;
   transUser.width = transcodingUser.Width;
   transUser.x = transcodingUser.X;
   transUser.y = transcodingUser.Y;
   transUser.zOrder = transcodingUser.ZOrder;
   return transUser;
}

agora::rtc::LiveTranscoding FLiveTranscoding::convert( std::unique_ptr< agora::rtc::TranscodingUser[] >& users,
                                                       std::unique_ptr< agora::rtc::RtcImage >& watermark,
                                                       std::unique_ptr< agora::rtc::RtcImage >& backgroundImage ) const
{
   users.reset( new agora::rtc::TranscodingUser[TranscodingUsers.Num()] );

   for( int i( 0 ); i < TranscodingUsers.Num(); i++ )
   {
      users[i] = ::convert( TranscodingUsers[i] );
   }

   watermark.reset( new agora::rtc::RtcImage( ::convert( Watermark ) ) );
   backgroundImage.reset( new agora::rtc::RtcImage( ::convert( BackgroundImage ) ) );

   agora::rtc::LiveTranscoding liveTrans;
   liveTrans.audioBitrate = AudioBitrate;
   liveTrans.audioChannels = AudioChannels;
   liveTrans.audioCodecProfile = ::convert( AudioCodecProfile );
   liveTrans.audioSampleRate = ::convert( AudioSampleRate );
   liveTrans.backgroundColor = BackgroundColor;
   liveTrans.backgroundImage = backgroundImage.get();
   liveTrans.height = Height;
   liveTrans.lowLatency = LowLatency;
   liveTrans.metadata = TCHAR_TO_ANSI( *Metadata );
   liveTrans.transcodingExtraInfo = TCHAR_TO_ANSI( *TranscodingExtraInfo );
   liveTrans.transcodingUsers = users.get();
   liveTrans.userCount = TranscodingUsers.Num();
   liveTrans.videoBitrate = VideoBitrate;
   liveTrans.videoCodecProfile = ::convert( VideoCodecProfile );
   liveTrans.videoFramerate = VideoFramerate;
   liveTrans.videoGop = VideoGop;
   liveTrans.watermark = watermark.get();
   liveTrans.width = Width;
   return liveTrans;
}

agora::rtc::ChannelMediaRelayConfiguration FChannelMediaRelayConfiguration::convert( 
   std::unique_ptr< agora::rtc::ChannelMediaInfo >& srcInfo,
   std::unique_ptr< agora::rtc::ChannelMediaInfo[] >& destInfos ) const
{
   srcInfo.reset( new agora::rtc::ChannelMediaInfo( ::convert( SrcInfo ) ) );
   destInfos.reset( new agora::rtc::ChannelMediaInfo[DestInfos.Num()] );
   for( int i( 0 ); i < DestInfos.Num(); i++ )
   {
      destInfos[i] = ::convert( DestInfos[i] );
   }

   agora::rtc::ChannelMediaRelayConfiguration chMediaRelayConfiguration;
   chMediaRelayConfiguration.destCount = DestInfos.Num();
   chMediaRelayConfiguration.destInfos = destInfos.get();
   chMediaRelayConfiguration.srcInfo = srcInfo.get();

   return chMediaRelayConfiguration;
}

FAgoraUserInfo convert( const agora::rtc::UserInfo& userInfo )
{
   FAgoraUserInfo uInfo;
   uInfo.Uid = userInfo.uid;
   uInfo.UserAccount = ANSI_TO_TCHAR( userInfo.userAccount );
   return uInfo;
}

agora::rtc::VideoCanvas convert( const FVideoCanvas& videoCanvas )
{
   agora::rtc::VideoCanvas videoCanv;
   videoCanv.renderMode = videoCanvas.RenderMode;
   videoCanv.uid = videoCanvas.Uid;
   if( videoCanvas.Priv != nullptr )
      videoCanv.priv = videoCanvas.Priv->GetPlainData();
   if( videoCanvas.View )
      videoCanv.view = videoCanvas.View->GetPlainData();
   return videoCanv;
}

agora::rtc::WatermarkOptions convert( const FWatermarkOptions& watermarkOptions )
{
   agora::rtc::WatermarkOptions watermarkOpt;
   watermarkOpt.positionInLandscapeMode = agora::rtc::Rectangle( watermarkOptions.PositionInLandscapeMode.X,
                                                                 watermarkOptions.PositionInLandscapeMode.Y,
                                                                 watermarkOptions.PositionInLandscapeMode.Width,
                                                                 watermarkOptions.PositionInLandscapeMode.Height );
   watermarkOpt.positionInPortraitMode = agora::rtc::Rectangle( watermarkOptions.PositionInPortraitMode.X,
                                                                watermarkOptions.PositionInPortraitMode.Y,
                                                                watermarkOptions.PositionInPortraitMode.Width,
                                                                watermarkOptions.PositionInPortraitMode.Height );
   watermarkOpt.visibleInPreview = watermarkOptions.VisibleInPreview;
   return watermarkOpt;
}

agora::rtc::FRAME_RATE convert( EFRAME_RATE frameRate )
{
   switch( frameRate )
   {
      case FRAME_RATE_FPS_1:  return agora::rtc::FRAME_RATE_FPS_1;
      case FRAME_RATE_FPS_7:  return agora::rtc::FRAME_RATE_FPS_7;
      case FRAME_RATE_FPS_10: return agora::rtc::FRAME_RATE_FPS_10;
      case FRAME_RATE_FPS_15: return agora::rtc::FRAME_RATE_FPS_15;
      case FRAME_RATE_FPS_24: return agora::rtc::FRAME_RATE_FPS_24;
      case FRAME_RATE_FPS_30: return agora::rtc::FRAME_RATE_FPS_30;
      case FRAME_RATE_FPS_60: return agora::rtc::FRAME_RATE_FPS_60;
      default: return agora::rtc::FRAME_RATE_FPS_15;
   }
}

agora::rtc::ORIENTATION_MODE convert( EORIENTATION_MODE orientationMode )
{
   switch( orientationMode )
   {
      case ORIENTATION_MODE_ADAPTIVE: return agora::rtc::ORIENTATION_MODE_ADAPTIVE;
      case ORIENTATION_MODE_FIXED_LANDSCAPE: return agora::rtc::ORIENTATION_MODE_FIXED_LANDSCAPE;
      case ORIENTATION_MODE_FIXED_PORTRAIT: return agora::rtc::ORIENTATION_MODE_FIXED_PORTRAIT;
      default: return agora::rtc::ORIENTATION_MODE_ADAPTIVE;
   }
}

agora::rtc::DEGRADATION_PREFERENCE convert( EDEGRADATION_PREFERENCE degradationPreference )
{
   switch( degradationPreference )
   {
      case MAINTAIN_QUALITY: return agora::rtc::MAINTAIN_QUALITY;
      case MAINTAIN_FRAMERATE: return agora::rtc::MAINTAIN_FRAMERATE;
      case MAINTAIN_BALANCED: return agora::rtc::MAINTAIN_BALANCED;
      default: return agora::rtc::MAINTAIN_QUALITY;
   }
}

agora::rtc::VideoDimensions convert( const FVideoDimensions& dimensions )
{
   return agora::rtc::VideoDimensions( dimensions.Width, dimensions.Height );
}

agora::rtc::ScreenCaptureParameters convert( const FScreenCaptureParameters& parameters )
{
   return agora::rtc::ScreenCaptureParameters( 
      convert( parameters.Dimensions ), 
      parameters.FrameRate, 
      parameters.Bitrate, 
      parameters.captureMouseCursor );
}

agora::rtc::Rectangle convert( const FRectangle& rectangle )
{
   agora::rtc::Rectangle rect;
   rect.x = rectangle.X;
   rect.y = rectangle.Y;
   rect.width = rectangle.Width;
   rect.height = rectangle.Height;
   return rect;
}

agora::rtc::VideoContentHint convert( EVIDEO_CONTENT_HINT contentHint )
{
   switch( contentHint )
   {
      case CONTENT_HINT_NONE: return agora::rtc::CONTENT_HINT_NONE;
      case CONTENT_HINT_MOTION: return agora::rtc::CONTENT_HINT_MOTION;
      case CONTENT_HINT_DETAILS: return agora::rtc::CONTENT_HINT_DETAILS;
      default: return agora::rtc::CONTENT_HINT_NONE;
   }
}

FAudioVolumeInfo convert( const agora::rtc::AudioVolumeInfo& volumeInfo )
{
   FAudioVolumeInfo info;
   info.Uid = volumeInfo.uid;
   info.Vad = volumeInfo.vad;
   info.Volume = volumeInfo.volume;
   return info;
}

ELASTMILE_PROBE_RESULT_STATE convert( agora::rtc::LASTMILE_PROBE_RESULT_STATE  lastmileProbeResultState )
{
   switch( lastmileProbeResultState )
   {
      case agora::rtc::LASTMILE_PROBE_RESULT_COMPLETE: return LASTMILE_PROBE_RESULT_COMPLETE;
      case agora::rtc::LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE: return LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE;
      case agora::rtc::LASTMILE_PROBE_RESULT_UNAVAILABLE: return LASTMILE_PROBE_RESULT_UNAVAILABLE;
      default: return LASTMILE_PROBE_RESULT_UNAVAILABLE;
   }
};

FLastmileProbeOneWayResult convert( const agora::rtc::LastmileProbeOneWayResult& lastmileProbeOneWayResult )
{
   FLastmileProbeOneWayResult lastmileProbeOneWayRes;
   lastmileProbeOneWayRes.PacketLossRate = lastmileProbeOneWayResult.packetLossRate;
   lastmileProbeOneWayRes.Jitter = lastmileProbeOneWayResult.jitter;
   lastmileProbeOneWayRes.AvailableBandwidth = lastmileProbeOneWayResult.availableBandwidth;
   return lastmileProbeOneWayRes;
};

FLastmileProbeResult convert( const agora::rtc::LastmileProbeResult&  lastmileProbeResultStruct )
{
   FLastmileProbeResult lastmileProbeResult;
   lastmileProbeResult.DownlinkReport = convert( lastmileProbeResultStruct.downlinkReport );
   lastmileProbeResult.Rtt = lastmileProbeResultStruct.rtt;
   lastmileProbeResult.State = convert( lastmileProbeResultStruct.state );
   lastmileProbeResult.UplinkReport = convert( lastmileProbeResultStruct.uplinkReport );
   return lastmileProbeResult;
}


EQUALITY_ADAPT_INDICATION convert( agora::rtc::QUALITY_ADAPT_INDICATION qualityAdaptIndication )
{
   switch( qualityAdaptIndication )
   {
      case agora::rtc::ADAPT_NONE: return ADAPT_NONE;
      case agora::rtc::ADAPT_UP_BANDWIDTH: return ADAPT_UP_BANDWIDTH;
      case agora::rtc::ADAPT_DOWN_BANDWIDTH: return ADAPT_DOWN_BANDWIDTH;
      default: return ADAPT_NONE;
   }
};

EVIDEO_CODEC_TYPE convert( agora::rtc::VIDEO_CODEC_TYPE videoCodecType )
{
   switch( videoCodecType )
   {
      case agora::rtc::VIDEO_CODEC_VP8: return VIDEO_CODEC_VP8;
      case  agora::rtc::VIDEO_CODEC_H264: return VIDEO_CODEC_H264;
      case agora::rtc::VIDEO_CODEC_EVP: return VIDEO_CODEC_EVP;
      case agora::rtc::VIDEO_CODEC_E264: return  VIDEO_CODEC_E264;
      default: return VIDEO_CODEC_VP8;
   }
};


FLocalVideoStats convert( const agora::rtc::LocalVideoStats& localVideoStats )
{
   FLocalVideoStats locVideoStats;
   locVideoStats.CodecType = convert( localVideoStats.codecType );
   locVideoStats.EncodedBitrate = localVideoStats.encodedBitrate;
   locVideoStats.EncodedFrameCount = localVideoStats.encodedFrameCount;
   locVideoStats.EncodedFrameHeight = localVideoStats.encodedFrameHeight;
   locVideoStats.EncodedFrameWidth = localVideoStats.encodedFrameWidth;
   locVideoStats.EncoderOutputFrameRate = localVideoStats.encoderOutputFrameRate;
   locVideoStats.QualityAdaptIndication = convert( localVideoStats.qualityAdaptIndication );
   locVideoStats.RendererOutputFrameRate = localVideoStats.rendererOutputFrameRate;
   locVideoStats.SentBitrate = localVideoStats.sentBitrate;
   locVideoStats.SentFrameRate = localVideoStats.sentFrameRate;
   locVideoStats.TargetBitrate = localVideoStats.targetBitrate;
   locVideoStats.TargetFrameRate = localVideoStats.targetFrameRate;
   return locVideoStats;
}

EREMOTE_VIDEO_STREAM_TYPE convert( agora::rtc::REMOTE_VIDEO_STREAM_TYPE remoteVideoStreamType )
{
   switch( remoteVideoStreamType )
   {
      case agora::rtc::REMOTE_VIDEO_STREAM_HIGH: return REMOTE_VIDEO_STREAM_HIGH;
      case agora::rtc::REMOTE_VIDEO_STREAM_LOW: return REMOTE_VIDEO_STREAM_LOW;
      default:  return REMOTE_VIDEO_STREAM_HIGH;
   }
};

FRemoteVideoStats convert( const agora::rtc::RemoteVideoStats& remoteVideoStats )
{
   FRemoteVideoStats remVideoStats;
   remVideoStats.DecoderOutputFrameRate = remoteVideoStats.decoderOutputFrameRate;
   remVideoStats.Delay = remoteVideoStats.delay;
   remVideoStats.FrozenRate = remoteVideoStats.frozenRate;
   remVideoStats.Height = remoteVideoStats.height;
   remVideoStats.PacketLossRate = remoteVideoStats.packetLossRate;
   remVideoStats.ReceivedBitrate = remoteVideoStats.receivedBitrate;
   remVideoStats.RendererOutputFrameRate = remoteVideoStats.rendererOutputFrameRate;
   remVideoStats.RxStreamType = convert( remoteVideoStats.rxStreamType );
   remVideoStats.TotalFrozenTime = remoteVideoStats.totalFrozenTime;
   remVideoStats.Uid = remoteVideoStats.uid;
   remVideoStats.Width = remoteVideoStats.width;
   return remVideoStats;
}

FLocalAudioStats convert( const agora::rtc::LocalAudioStats& localAudioStats )
{
   FLocalAudioStats locAudioStats;
   locAudioStats.NumChannels = localAudioStats.numChannels;
   locAudioStats.SentBitrate = localAudioStats.sentBitrate;
   locAudioStats.SentSampleRate = localAudioStats.sentSampleRate;
   return locAudioStats;
}

FRemoteAudioStats convert( const agora::rtc::RemoteAudioStats& localAudioStats )
{
   FRemoteAudioStats remAudioStats;
   remAudioStats.AudioLossRate = localAudioStats.audioLossRate;
   remAudioStats.FrozenRate = localAudioStats.frozenRate;
   remAudioStats.JitterBufferDelay = localAudioStats.jitterBufferDelay;
   remAudioStats.NetworkTransportDelay = localAudioStats.networkTransportDelay;
   remAudioStats.NumChannels = localAudioStats.numChannels;
   remAudioStats.Quality = localAudioStats.quality;
   remAudioStats.ReceivedBitrate = localAudioStats.receivedBitrate;
   remAudioStats.ReceivedSampleRate = localAudioStats.receivedSampleRate;
   remAudioStats.TotalFrozenTime = localAudioStats.totalFrozenTime;
   remAudioStats.Uid = localAudioStats.uid;
   return remAudioStats;
}

ELOCAL_AUDIO_STREAM_ERROR convert( agora::rtc::LOCAL_AUDIO_STREAM_ERROR localAudioStreamError )
{
   switch( localAudioStreamError )
   {
      case agora::rtc::LOCAL_AUDIO_STREAM_ERROR_OK: return LOCAL_AUDIO_STREAM_ERROR_OK;
      case agora::rtc::LOCAL_AUDIO_STREAM_ERROR_FAILURE: return  LOCAL_AUDIO_STREAM_ERROR_FAILURE;
      case agora::rtc::LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION: return  LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION;
      case agora::rtc::LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY: return  LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY;
      case agora::rtc::LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE: return  LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE;
      case agora::rtc::LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE: return  LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE;
      default: return LOCAL_AUDIO_STREAM_ERROR_OK;
   }
}

ELOCAL_AUDIO_STREAM_STATE convert( agora::rtc::LOCAL_AUDIO_STREAM_STATE localAudioStreamState )
{
   switch( localAudioStreamState )
   {
      case agora::rtc::LOCAL_AUDIO_STREAM_STATE_STOPPED: return  LOCAL_AUDIO_STREAM_STATE_STOPPED;
      case agora::rtc::LOCAL_AUDIO_STREAM_STATE_RECORDING: return  LOCAL_AUDIO_STREAM_STATE_RECORDING;
      case agora::rtc::LOCAL_AUDIO_STREAM_STATE_ENCODING: return  LOCAL_AUDIO_STREAM_STATE_ENCODING;
      case agora::rtc::LOCAL_AUDIO_STREAM_STATE_FAILED: return  LOCAL_AUDIO_STREAM_STATE_FAILED;
      default: return  LOCAL_AUDIO_STREAM_STATE_STOPPED;
   }
}

EREMOTE_AUDIO_STATE convert( agora::rtc::REMOTE_AUDIO_STATE remoteAudioState )
{
   switch( remoteAudioState )
   {
      case agora::rtc::REMOTE_AUDIO_STATE_STOPPED: return REMOTE_AUDIO_STATE_STOPPED;
      case agora::rtc::REMOTE_AUDIO_STATE_STARTING: return REMOTE_AUDIO_STATE_STARTING;
      case agora::rtc::REMOTE_AUDIO_STATE_DECODING: return REMOTE_AUDIO_STATE_DECODING;
      case agora::rtc::REMOTE_AUDIO_STATE_FROZEN: return  REMOTE_AUDIO_STATE_FROZEN;
      case agora::rtc::REMOTE_AUDIO_STATE_FAILED: return  REMOTE_AUDIO_STATE_FAILED;
      default: return REMOTE_AUDIO_STATE_STOPPED;
   }
}

EREMOTE_AUDIO_STATE_REASON convert( agora::rtc::REMOTE_AUDIO_STATE_REASON remoteAudioStateReason )
{
   switch( remoteAudioStateReason )
   {
      case agora::rtc::REMOTE_AUDIO_REASON_INTERNAL: return REMOTE_AUDIO_REASON_INTERNAL;
      case agora::rtc::REMOTE_AUDIO_REASON_NETWORK_CONGESTION: return REMOTE_AUDIO_REASON_NETWORK_CONGESTION;
      case agora::rtc::REMOTE_AUDIO_REASON_NETWORK_RECOVERY: return REMOTE_AUDIO_REASON_NETWORK_RECOVERY;
      case agora::rtc::REMOTE_AUDIO_REASON_LOCAL_MUTED: return REMOTE_AUDIO_REASON_LOCAL_MUTED;
      case agora::rtc::REMOTE_AUDIO_REASON_LOCAL_UNMUTED: return REMOTE_AUDIO_REASON_LOCAL_UNMUTED;
      case agora::rtc::REMOTE_AUDIO_REASON_REMOTE_MUTED: return REMOTE_AUDIO_REASON_REMOTE_MUTED;
      case agora::rtc::REMOTE_AUDIO_REASON_REMOTE_UNMUTED: return REMOTE_AUDIO_REASON_REMOTE_UNMUTED;
      case agora::rtc::REMOTE_AUDIO_REASON_REMOTE_OFFLINE: return REMOTE_AUDIO_REASON_REMOTE_OFFLINE;
      default: return REMOTE_AUDIO_REASON_INTERNAL;
   }
}

EMEDIA_DEVICE_TYPE convert( agora::rtc::MEDIA_DEVICE_TYPE mediaDeviceType )
{
   switch( mediaDeviceType )
   {
      case agora::rtc::UNKNOWN_AUDIO_DEVICE:  return UNKNOWN_AUDIO_DEVICE;
      case agora::rtc::AUDIO_PLAYOUT_DEVICE:  return   AUDIO_PLAYOUT_DEVICE;
      case agora::rtc::AUDIO_RECORDING_DEVICE:  return   AUDIO_RECORDING_DEVICE;
      case agora::rtc::VIDEO_RENDER_DEVICE:    return  VIDEO_RENDER_DEVICE;
      case agora::rtc::VIDEO_CAPTURE_DEVICE:    return   VIDEO_CAPTURE_DEVICE;
      case agora::rtc::AUDIO_APPLICATION_PLAYOUT_DEVICE:   return  AUDIO_APPLICATION_PLAYOUT_DEVICE;
      default:  return UNKNOWN_AUDIO_DEVICE;
   }
}

EAUDIO_MIXING_STATE_TYPE convert( agora::rtc::AUDIO_MIXING_STATE_TYPE audioMixingStateType )
{
   switch( audioMixingStateType )
   {
      case agora::rtc::AUDIO_MIXING_STATE_PLAYING: return AUDIO_MIXING_STATE_PLAYING;
      case agora::rtc::AUDIO_MIXING_STATE_PAUSED: return AUDIO_MIXING_STATE_PAUSED;
      case agora::rtc::AUDIO_MIXING_STATE_STOPPED: return AUDIO_MIXING_STATE_STOPPED;
      case agora::rtc::AUDIO_MIXING_STATE_FAILED: return AUDIO_MIXING_STATE_FAILED;
      default: return AUDIO_MIXING_STATE_FAILED;
   }
}

EAUDIO_MIXING_ERROR_TYPE convert( agora::rtc::AUDIO_MIXING_ERROR_TYPE audioMixingErrorType )
{
   switch( audioMixingErrorType )
   {
      case agora::rtc::AUDIO_MIXING_ERROR_CAN_NOT_OPEN: return  AUDIO_MIXING_ERROR_CAN_NOT_OPEN;
      case agora::rtc::AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL: return AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL;
      case agora::rtc::AUDIO_MIXING_ERROR_INTERRUPTED_EOF: return  AUDIO_MIXING_ERROR_INTERRUPTED_EOF;
      case agora::rtc::AUDIO_MIXING_ERROR_OK: return AUDIO_MIXING_ERROR_OK;
      default: return AUDIO_MIXING_ERROR_OK;
   }
}

ELOCAL_VIDEO_STREAM_STATE convert( agora::rtc::LOCAL_VIDEO_STREAM_STATE localVideoStreamState )
{
   switch( localVideoStreamState )
   {
      case agora::rtc::LOCAL_VIDEO_STREAM_STATE_STOPPED: return LOCAL_VIDEO_STREAM_STATE_STOPPED;
      case agora::rtc::LOCAL_VIDEO_STREAM_STATE_CAPTURING: return LOCAL_VIDEO_STREAM_STATE_CAPTURING;
      case agora::rtc::LOCAL_VIDEO_STREAM_STATE_ENCODING: return LOCAL_VIDEO_STREAM_STATE_ENCODING;
      case agora::rtc::LOCAL_VIDEO_STREAM_STATE_FAILED: return  LOCAL_VIDEO_STREAM_STATE_FAILED;
      default: return LOCAL_VIDEO_STREAM_STATE_STOPPED;
   }
}

ELOCAL_VIDEO_STREAM_ERROR convert( agora::rtc::LOCAL_VIDEO_STREAM_ERROR localVideoStreamError )
{
   switch( localVideoStreamError )
   {
      case agora::rtc::LOCAL_VIDEO_STREAM_ERROR_OK: return  LOCAL_VIDEO_STREAM_ERROR_OK;
      case agora::rtc::LOCAL_VIDEO_STREAM_ERROR_FAILURE: return  LOCAL_VIDEO_STREAM_ERROR_FAILURE;
      case agora::rtc::LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION: return  LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION;
      case agora::rtc::LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY: return   LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY;
      case agora::rtc::LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE: return   LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE;
      case agora::rtc::LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE: return  LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE;
      default: return  LOCAL_VIDEO_STREAM_ERROR_OK;
   }
}

EREMOTE_VIDEO_STATE convert( agora::rtc::REMOTE_VIDEO_STATE remoteVideoState )
{
   switch( remoteVideoState )
   {
      case agora::rtc::REMOTE_VIDEO_STATE_STOPPED: return REMOTE_VIDEO_STATE_STOPPED;
      case agora::rtc::REMOTE_VIDEO_STATE_STARTING: return REMOTE_VIDEO_STATE_STARTING;
      case agora::rtc::REMOTE_VIDEO_STATE_DECODING: return REMOTE_VIDEO_STATE_DECODING;
      case agora::rtc::REMOTE_VIDEO_STATE_FROZEN: return REMOTE_VIDEO_STATE_FROZEN;
      case agora::rtc::REMOTE_VIDEO_STATE_FAILED: return  REMOTE_VIDEO_STATE_FAILED;
      default: return REMOTE_VIDEO_STATE_STOPPED;
   }
}

EREMOTE_VIDEO_STATE_REASON convert( agora::rtc::REMOTE_VIDEO_STATE_REASON remoteVideoStateReason )
{
   switch( remoteVideoStateReason )
   {
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_INTERNAL: return REMOTE_VIDEO_STATE_REASON_INTERNAL;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION: return REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY: return REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED: return REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED: return REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED: return REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED: return REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE: return REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK: return REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK;
      case agora::rtc::REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY: return REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY;
      default: return REMOTE_VIDEO_STATE_REASON_INTERNAL;
   }
}

ECHANNEL_MEDIA_RELAY_STATE convert( agora::rtc::CHANNEL_MEDIA_RELAY_STATE channelMediaRelayState )
{
   switch( channelMediaRelayState )
   {
      case agora::rtc::RELAY_STATE_IDLE: return RELAY_STATE_IDLE;
      case agora::rtc::RELAY_STATE_CONNECTING: return RELAY_STATE_CONNECTING;
      case agora::rtc::RELAY_STATE_RUNNING: return RELAY_STATE_RUNNING;
      case agora::rtc::RELAY_STATE_FAILURE: return RELAY_STATE_FAILURE;
      default: return RELAY_STATE_IDLE;
   }
};

ECHANNEL_MEDIA_RELAY_ERROR convert( agora::rtc::CHANNEL_MEDIA_RELAY_ERROR channelMediaRelayError )
{
   switch( channelMediaRelayError )
   {
      case agora::rtc::RELAY_OK: return RELAY_OK;
      case agora::rtc::RELAY_ERROR_SERVER_ERROR_RESPONSE: return RELAY_ERROR_SERVER_ERROR_RESPONSE;
      case agora::rtc::RELAY_ERROR_SERVER_NO_RESPONSE: return RELAY_ERROR_SERVER_NO_RESPONSE;
      case agora::rtc::RELAY_ERROR_NO_RESOURCE_AVAILABLE: return RELAY_ERROR_NO_RESOURCE_AVAILABLE;
      case agora::rtc::RELAY_ERROR_FAILED_JOIN_SRC: return RELAY_ERROR_FAILED_JOIN_SRC;
      case agora::rtc::RELAY_ERROR_FAILED_JOIN_DEST: return RELAY_ERROR_FAILED_JOIN_DEST;
      case agora::rtc::RELAY_ERROR_FAILED_PACKET_RECEIVED_FROM_SRC: return RELAY_ERROR_FAILED_PACKET_RECEIVED_FROM_SRC;
      case agora::rtc::RELAY_ERROR_FAILED_PACKET_SENT_TO_DEST: return RELAY_ERROR_FAILED_PACKET_SENT_TO_DEST;
      case agora::rtc::RELAY_ERROR_SERVER_CONNECTION_LOST: return RELAY_ERROR_SERVER_CONNECTION_LOST;
      case agora::rtc::RELAY_ERROR_INTERNAL_ERROR: return RELAY_ERROR_INTERNAL_ERROR;
      case agora::rtc::RELAY_ERROR_SRC_TOKEN_EXPIRED: return RELAY_ERROR_SRC_TOKEN_EXPIRED;
      case agora::rtc::RELAY_ERROR_DEST_TOKEN_EXPIRED: return RELAY_ERROR_DEST_TOKEN_EXPIRED;
      default: return RELAY_OK;
   }
};


ECHANNEL_MEDIA_RELAY_EVENT convert( agora::rtc::CHANNEL_MEDIA_RELAY_EVENT channelMediaRelayEvent )
{
   switch( channelMediaRelayEvent )
   {
      case agora::rtc::RELAY_EVENT_NETWORK_DISCONNECTED: return RELAY_EVENT_NETWORK_DISCONNECTED;
      case agora::rtc::RELAY_EVENT_NETWORK_CONNECTED: return RELAY_EVENT_NETWORK_CONNECTED;
      case agora::rtc::RELAY_EVENT_PACKET_JOINED_SRC_CHANNEL: return  RELAY_EVENT_PACKET_JOINED_SRC_CHANNEL;
      case agora::rtc::RELAY_EVENT_PACKET_JOINED_DEST_CHANNEL: return  RELAY_EVENT_PACKET_JOINED_DEST_CHANNEL;
      case agora::rtc::RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL: return RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL;
      case agora::rtc::RELAY_EVENT_PACKET_RECEIVED_VIDEO_FROM_SRC: return RELAY_EVENT_PACKET_RECEIVED_VIDEO_FROM_SRC;
      case agora::rtc::RELAY_EVENT_PACKET_RECEIVED_AUDIO_FROM_SRC: return RELAY_EVENT_PACKET_RECEIVED_AUDIO_FROM_SRC;
      case agora::rtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL: return  RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL;
      case agora::rtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_REFUSED: return RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_REFUSED;
      case agora::rtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_NOT_CHANGE: return RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_NOT_CHANGE;
      case agora::rtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL: return RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL;
      case agora::rtc::RELAY_EVENT_VIDEO_PROFILE_UPDATE: return RELAY_EVENT_VIDEO_PROFILE_UPDATE;
      default: return RELAY_EVENT_NETWORK_DISCONNECTED;
   }
};


ERTMP_STREAM_PUBLISH_STATE convert( agora::rtc::RTMP_STREAM_PUBLISH_STATE rtmpStreamPublishState )
{
   switch( rtmpStreamPublishState )
   {
      case agora::rtc::RTMP_STREAM_PUBLISH_STATE_IDLE: return RTMP_STREAM_PUBLISH_STATE_IDLE;
      case agora::rtc::RTMP_STREAM_PUBLISH_STATE_CONNECTING: return RTMP_STREAM_PUBLISH_STATE_CONNECTING;
      case agora::rtc::RTMP_STREAM_PUBLISH_STATE_RUNNING: return RTMP_STREAM_PUBLISH_STATE_RUNNING;
      case agora::rtc::RTMP_STREAM_PUBLISH_STATE_RECOVERING: return RTMP_STREAM_PUBLISH_STATE_RECOVERING;
      case agora::rtc::RTMP_STREAM_PUBLISH_STATE_FAILURE: return RTMP_STREAM_PUBLISH_STATE_FAILURE;
      default: return RTMP_STREAM_PUBLISH_STATE_IDLE;
   }
};

ERTMP_STREAM_PUBLISH_ERROR convert( agora::rtc::RTMP_STREAM_PUBLISH_ERROR rtmpStreamPublishError )
{
   switch( rtmpStreamPublishError )
   {
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_OK: return RTMP_STREAM_PUBLISH_ERROR_OK;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT: return RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED: return RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT: return RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR: return RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR: return RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN: return RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT: return RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED: return RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND: return RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND;
      case agora::rtc::RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED: return RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED;
      default: return RTMP_STREAM_PUBLISH_ERROR_OK;
   }
};

EAUDIO_ROUTE_TYPE convert( agora::rtc::AUDIO_ROUTE_TYPE audioRouteType )
{
   switch( audioRouteType )
   {
      case agora::rtc::AUDIO_ROUTE_DEFAULT: return AUDIO_ROUTE_DEFAULT;
      case agora::rtc::AUDIO_ROUTE_HEADSET: return AUDIO_ROUTE_HEADSET;
      case agora::rtc::AUDIO_ROUTE_EARPIECE: return AUDIO_ROUTE_EARPIECE;
      case agora::rtc::AUDIO_ROUTE_HEADSET_NO_MIC: return AUDIO_ROUTE_HEADSET_NO_MIC;
      case agora::rtc::AUDIO_ROUTE_SPEAKERPHONE: return AUDIO_ROUTE_SPEAKERPHONE;
      case agora::rtc::AUDIO_ROUTE_LOUDSPEAKER: return AUDIO_ROUTE_LOUDSPEAKER;
      case agora::rtc::AUDIO_ROUTE_BLUETOOTH: return AUDIO_ROUTE_BLUETOOTH;
      default: return AUDIO_ROUTE_DEFAULT;
   }
};

ECONNECTION_CHANGED_REASON_TYPE convert( agora::rtc::CONNECTION_CHANGED_REASON_TYPE connectionChangedReasonType )
{
   switch( connectionChangedReasonType )
   {
      case agora::rtc::CONNECTION_CHANGED_CONNECTING: return CONNECTION_CHANGED_CONNECTING;
      case agora::rtc::CONNECTION_CHANGED_JOIN_SUCCESS: return CONNECTION_CHANGED_JOIN_SUCCESS;
      case agora::rtc::CONNECTION_CHANGED_INTERRUPTED: return CONNECTION_CHANGED_INTERRUPTED;
      case agora::rtc::CONNECTION_CHANGED_BANNED_BY_SERVER: return CONNECTION_CHANGED_BANNED_BY_SERVER;
      case agora::rtc::CONNECTION_CHANGED_JOIN_FAILED: return CONNECTION_CHANGED_JOIN_FAILED;
      case agora::rtc::CONNECTION_CHANGED_LEAVE_CHANNEL: return CONNECTION_CHANGED_LEAVE_CHANNEL;
      case agora::rtc::CONNECTION_CHANGED_INVALID_APP_ID: return CONNECTION_CHANGED_INVALID_APP_ID;
      case agora::rtc::CONNECTION_CHANGED_INVALID_CHANNEL_NAME: return CONNECTION_CHANGED_INVALID_CHANNEL_NAME;
      case agora::rtc::CONNECTION_CHANGED_INVALID_TOKEN: return CONNECTION_CHANGED_INVALID_TOKEN;
      case agora::rtc::CONNECTION_CHANGED_TOKEN_EXPIRED: return CONNECTION_CHANGED_TOKEN_EXPIRED;
      case agora::rtc::CONNECTION_CHANGED_REJECTED_BY_SERVER: return CONNECTION_CHANGED_REJECTED_BY_SERVER;
      case agora::rtc::CONNECTION_CHANGED_SETTING_PROXY_SERVER: return CONNECTION_CHANGED_SETTING_PROXY_SERVER;
      case agora::rtc::CONNECTION_CHANGED_RENEW_TOKEN: return CONNECTION_CHANGED_RENEW_TOKEN;
      case agora::rtc::CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED: return CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED;
      case agora::rtc::CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT: return CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT;
      default: return CONNECTION_CHANGED_CONNECTING;
   }
};

ENETWORK_TYPE convert( agora::rtc::NETWORK_TYPE networkType )
{
   switch( networkType )
   {
      case agora::rtc::NETWORK_TYPE_UNKNOWN: return NETWORK_TYPE_UNKNOWN;
      case agora::rtc::NETWORK_TYPE_DISCONNECTED: return NETWORK_TYPE_DISCONNECTED;
      case agora::rtc::NETWORK_TYPE_LAN: return NETWORK_TYPE_LAN;
      case agora::rtc::NETWORK_TYPE_WIFI: return NETWORK_TYPE_WIFI;
      case agora::rtc::NETWORK_TYPE_MOBILE_2G: return NETWORK_TYPE_MOBILE_2G;
      case agora::rtc::NETWORK_TYPE_MOBILE_3G: return NETWORK_TYPE_MOBILE_3G;
      case agora::rtc::NETWORK_TYPE_MOBILE_4G: return NETWORK_TYPE_MOBILE_4G;
      default: return NETWORK_TYPE_UNKNOWN;
   }
};


#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
agora::rtc::CAMERA_DIRECTION convert( ECAMERA_DIRECTION cameraDirection )
{
   switch( cameraDirection )
   {
      case CAMERA_REAR: return agora::rtc::CAMERA_REAR;
      case CAMERA_FRONT: return agora::rtc::CAMERA_FRONT;
      default: return agora::rtc::CAMERA_FRONT;
   }
}
#endif

#if (defined(__APPLE__) && TARGET_OS_IOS)
agora::rtc::AUDIO_SESSION_OPERATION_RESTRICTION convert( EAUDIO_SESSION_OPERATION_RESTRICTION operationRestriction )
{
   switch( operationRestriction )
   {
      case AUDIO_SESSION_OPERATION_RESTRICTION_NONE: return agora::rtc::AUDIO_SESSION_OPERATION_RESTRICTION_NONE;
      case AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY: return agora::rtc::AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY;
      case AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION: return agora::rtc::AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION;
      case AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION: return agora::rtc::AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION;
      case AUDIO_SESSION_OPERATION_RESTRICTION_ALL: return agora::rtc::AUDIO_SESSION_OPERATION_RESTRICTION_ALL;
      default: return agora::rtc::AUDIO_SESSION_OPERATION_RESTRICTION_NONE;
   }
}
#endif

