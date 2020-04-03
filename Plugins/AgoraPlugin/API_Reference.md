
Agora Plugin wraps functionality of
<a href="https://docs.agora.io/en/Video/API%20Reference/cpp/v2.9.1/classagora_1_1media_1_1_i_media_engine.html" target="_blank">Agora C++ API Reference</a>
for use with Unreal Engine

## AgoraRtcEngine

Wrapper around <a href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html" target="_blank">agora::rtc::IRtcEngine</a>

### Member Function Documentation

#### static AgoraRtcEngine* createAgoraRtcEngine();

Replaces 
<a href="https://docs.agora.io/en/Video/API%20Reference/cpp/group__create_agora_rtc_engine.html#ga070cf7554b410c12b28baf0336ee8050" target="_blank">createAgoraRtcEngine</a>
function. Creates an AgoraRtcEngine object and returns the pointer.

#### void setSyncForRelease(bool sync);

Replaces 
<a href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#afe4804c1f53bfee301c0960fda006c47" target="_blank">release</a>
function. Call this to set sync mode( default - false ) before releasing the AgoraRtcEngine object 


#### int initialize(const agora::rtc::RtcEngineContext& rtcEngineContext);
Wraps: 
<a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ac71db65e66942e4e0a0550e95c16890f">initialize</a>

#### int setChannelProfile(agora::rtc::CHANNEL_PROFILE_TYPE profile);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aab53788c74da25080bad61f0525d12ae">setChannelProfile</a>

#### int setClientRole(agora::rtc::CLIENT_ROLE_TYPE role);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a89ca6a15d5a388f3c82038e74bad4040">setClientRole</a>

#### int joinChannel(const char* token, const char* channelId, const char* info, agora::rtc::uid_t uid);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#adc937172e59bd2695ea171553a88188c">joinChannel</a> 

#### int switchChannel(const char* token, const char* channelId);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a3eb5ee494ce124b34609c593719c89ab">switchChannel</a>

#### int leaveChannel();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a51c12d209373650638bfd82e28777081">leaveChannel</a>

#### int renewToken(const char* token);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a8f25b5ff97e2a070a69102e379295739">renewToken</a>

#### int registerLocalUserAccount(const char* appId, const char* userAccount);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a0d44b74ced4005ee86353c13186f870d">registerLocalUserAccount</a>

#### int joinChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a14f8c308c6c57c55653552b939a8527a">joinChannelWithUserAccount</a> 

#### int getUserInfoByUserAccount(const char* userAccount, UserInfo* userInfo);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a4f75984d3c5de5f6e3e4d8bd81e3b409">getUserInfoByUserAccount</a>

#### int getUserInfoByUid(uid_t uid, UserInfo* userInfo);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#abf4572004e6ceb99ce0ff76a75c69d0b">getUserInfoByUid</a>

#### int startEchoTest(int intervalInSeconds);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a842ed126b6e21a39059adaa4caa6d021">startEchoTest</a>

#### int stopEchoTest();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ae779da1c3fe153d73e8dfb2eb59ba9e4">stopEchoTest</a>

#### int enableVideo();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a7d35fc62d74685d25636f04b04051958">enableVideo</a>

#### int disableVideo();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ac8eca0135b3ab7cecb84e2b81b89a85d">disableVideo</a>

#### int setVideoEncoderConfiguration(const VideoEncoderConfiguration& config);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a9bcbdcee0b5c52f96b32baec1922cf2e">setVideoEncoderConfiguration</a>

#### int setCameraCapturerConfiguration(const CameraCapturerConfiguration& config);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aaa9b17c5a938b8331dba774f37f94e65">setCameraCapturerConfiguration</a> 

#### int setupLocalVideo(const VideoCanvas& canvas);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a744003a9c0230684e985e42d14361f28">setupLocalVideo</a> 

#### int setupRemoteVideo(const VideoCanvas& canvas);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ac166814787b0a1d8da5f5c632dd7cdcf">setupRemoteVideo</a> 

#### int startPreview();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aabd5f0d670a6cd26badc316083519512">startPreview</a> 

#### int setRemoteUserPriority(agora::rtc::uid_t uid, agora::rtc::PRIORITY_TYPE userPriority);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aecb5d85e9b3a60947d569b88253da710">setRemoteUserPriority</a>

#### int stopPreview();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ab15f532e7a282050721ddcbb2075f27c">stopPreview</a>

#### int enableAudio();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a996401c7ba33c6ec59527c5d109f548f">enableAudio</a>

#### int enableLocalAudio(bool enabled);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aa61051d91823a69fe6b04b5f541a8080">enableLocalAudio</a>

#### int disableAudio();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a1929f01411e983ed776275fe8e8ad45e">disableAudio</a>

#### int setAudioProfile(agora::rtc::AUDIO_PROFILE_TYPE profile, agora::rtc::AUDIO_SCENARIO_TYPE scenario);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ab0cb52e238b729a15525a5cc12543d9e">setAudioProfile</a>

#### int muteLocalAudioStream(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a08a34d5b85a225390a18467c92a7b6f9">muteLocalAudioStream</a> 

#### int muteAllRemoteAudioStreams(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ac061a3c81eba2d203a7511e59466e6a0">muteAllRemoteAudioStreams</a>

#### int setDefaultMuteAllRemoteAudioStreams(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a95cbd11f936847f107cefd77bb5fa546">setDefaultMuteAllRemoteAudioStreams</a>

#### int muteRemoteAudioStream(agora::rtc::uid_t userId, bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a7e457477ff1ec17b71631d1f8d073bd8">muteRemoteAudioStream</a>

#### int muteLocalVideoStream(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a7707fb7110c72637ee98f659e8b796e9">muteLocalVideoStream</a>

#### int enableLocalVideo(bool enabled);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a1877bb2aa655bbcbed57ffadd6424e51">enableLocalVideo</a>

#### int muteAllRemoteVideoStreams(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a897a09788641f26252be642bb7045ee4">muteAllRemoteVideoStreams</a> 

#### int setDefaultMuteAllRemoteVideoStreams(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a4bf9eb5398a80ec8e6dfa6b6541f1dcf">setDefaultMuteAllRemoteVideoStreams</a> 

#### int muteRemoteVideoStream(agora::rtc::uid_t userId, bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a4020ef90a9877414deec59137acf9ee2">muteRemoteVideoStream</a> 

#### int setRemoteVideoStreamType(agora::rtc::uid_t userId, agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a3929299ead74cf86ff54b182d0b9be23">setRemoteVideoStreamType</a>

#### int setRemoteDefaultVideoStreamType(agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#acc4369a1626f3d16446bb3e6c8adf0af">setRemoteDefaultVideoStreamType</a>

#### int enableAudioVolumeIndication(int interval, int smooth, bool report_vad);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a4b30a8ff1ae50c4c114ae4f909c4ebcb">enableAudioVolumeIndication</a>

#### int startAudioRecording(const char* filePath, agora::rtc::AUDIO_RECORDING_QUALITY_TYPE quality);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a2bcdb3713d087c6318a2e1972c1e8cc6">startAudioRecording</a> 

#### int startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a3c05d82c97a9d63ebda116b9a1e5ca3f">startAudioRecording</a>

#### int stopAudioRecording();
Wraps:  <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#adb392026425663e5b9f90fe90130e5a5">stopAudioRecording</a>

#### int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a6f573cd61d53147ed6a2b7f033091d86">startAudioMixing</a> 

#### int stopAudioMixing();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a2b90cbf4142c913b3efa795482713b08">stopAudioMixing</a>

#### int pauseAudioMixing();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ab86885c38e7ee7a4b37d5bbacafcaa24">pauseAudioMixing</a>

#### int resumeAudioMixing();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a5a9606ad7ca4995e0d37fcf1642fe401">resumeAudioMixing</a>

#### int adjustAudioMixingVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a544aee96b789ac5a57d26b61b7e1a5fa">adjustAudioMixingVolume</a>

#### int adjustAudioMixingPlayoutVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a8677c3f3160927d25d9814a88ab06da6">adjustAudioMixingPlayoutVolume</a>

#### int getAudioMixingPlayoutVolume();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aed9dda5a7b2683776f41f6ba0e1f281c">getAudioMixingPlayoutVolume</a>

#### int adjustAudioMixingPublishVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a9fafbaaf39578810ec9c11360fc7f027">adjustAudioMixingPublishVolume</a>

#### int getAudioMixingPublishVolume();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aa65e55a9a331cfd32b36d8847a9631a4">getAudioMixingPublishVolume</a>

#### int getAudioMixingDuration();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a6a87b6b9135a6f45095dcf6aa62295cb">getAudioMixingDuration</a>

#### int getAudioMixingCurrentPosition();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aae54b86e9e6a7c0ed955b96f011855cb">getAudioMixingCurrentPosition</a>

#### int setAudioMixingPosition(int pos /*in ms*/);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a6c69e2229c438fd587b8f81df34214ad">setAudioMixingPosition</a> 

#### int getEffectsVolume();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a0e9787c57db5b5e8fcc53ef5bb6d24c7">getEffectsVolume</a>

#### int setEffectsVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#add9a7fd856700acd288d47ff3c7da19d">setEffectsVolume</a>

#### int setVolumeOfEffect(int soundId, int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a08287428f277b7bf24d51a86ef61799b">setVolumeOfEffect</a> 

#### int playEffect( int soundId, const char* filePath, int loopCount, double pitch, double pan, int gain, bool publish = false);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a7f4ddb5170b19a471d8c3c721fa19c8d">playEffect</a>

#### int stopEffect(int soundId);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ad74eb7c7799b8762bff2b1e7e7bba8b9">stopEffect</a> 

#### int stopAllEffects();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a888ecfec4fda81831988898420d60e49">stopAllEffects</a>

#### int preloadEffect(int soundId, const char* filePath);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a02d0b23b0b66e8fb0e898eb2811a8e74">preloadEffect</a>

#### int unloadEffect(int soundId);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aa560240d5994be0c1a7853e96077e5f9">unloadEffect</a> 

#### int pauseEffect(int soundId);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a3c820db172c7fb43da58d81b7916d174">pauseEffect</a>

#### int pauseAllEffects();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ad731a94d9db9e2c3390e1443b379095f">pauseAllEffects</a> 

#### int resumeEffect(int soundId);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a6489955af474172afe4f4b44e4edb38a">resumeEffect</a>

#### int resumeAllEffects();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a2fc1b5996df964f8e12ce579e0eb5f98">resumeAllEffects</a> 

#### int enableSoundPositionIndication(bool enabled);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ac3f53f474760a834fef050937c4cf7fa">enableSoundPositionIndication</a>

#### int setRemoteVoicePosition(uid_t uid, double pan, double gain);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ac5c3755a1cca201b2a8066af07a653f6">setRemoteVoicePosition</a>

#### int setLocalVoicePitch(double pitch);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a43616f919e0906279dff5648830ce31a">setLocalVoicePitch</a>

#### int setLocalVoiceEqualization(agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain);
Wraps:  <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a8c75994eb06ab26a1704715ec76e0189">setLocalVoiceEqualization</a>

#### int setLocalVoiceReverb(agora::rtc::AUDIO_REVERB_TYPE reverbKey, int value);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a4d1d1309f97f3c430a1aa2d060bb7316">setLocalVoiceReverb</a>

#### int setLocalVoiceChanger(agora::rtc::VOICE_CHANGER_PRESET voiceChanger);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a99dc3d74202422436d40f6d7aa6e99dc">setLocalVoiceChanger</a>

#### int setLocalVoiceReverbPreset(agora::rtc::AUDIO_REVERB_PRESET reverbPreset);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a51a429a5a848b2ad591220aa6c24a898">setLocalVoiceReverbPreset</a>

#### int setLogFile(const char* filePath);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ae5a8ef2082a0ac196ecc128ee408def3">setLogFile</a>

#### int setLogFilter(unsigned int filter);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#acfc056b4c693d134bece8e7c0f05e69f">setLogFilter</a> 

#### int setLogFileSize(unsigned int fileSizeInKBytes);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a1fa35cd4f874109a26895a95096a873f">setLogFileSize</a> 

#### int setLocalRenderMode(agora::rtc::RENDER_MODE_TYPE renderMode);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a841dbf6f0db5787ace27c62d07afffa8">setLocalRenderMode</a>

#### int setRemoteRenderMode(agora::rtc::uid_t userId, agora::rtc::RENDER_MODE_TYPE renderMode);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aa3aa9078bc2f0f7c003d89f6e52843f2">setRemoteRenderMode</a>

#### int setLocalVideoMirrorMode(agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a67f08a1ee32d9443a04bb9b293156bde">setLocalVideoMirrorMode</a>

#### int enableDualStreamMode(bool enabled);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a72846f5bf13726e7a61497e2fef65972">enableDualStreamMode</a>

#### int setExternalAudioSource(bool enabled, int sampleRate, int channels);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a1dfb925d8ba1a60ca1d9ca04a4d7d65f">setExternalAudioSource</a>

#### int setExternalAudioSink(bool enabled, int sampleRate, int channels);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a790b4896f2769c1edebbb49d8912e38b">setExternalAudioSink</a>

#### int setRecordingAudioFrameParameters( int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a2c4717760b5fbf1bb8c1a3c16ca67fe5">setRecordingAudioFrameParameters</a> 

#### int setPlaybackAudioFrameParameters( int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aa5f2f6eb3db5acaaf8c40818d90694f1">setPlaybackAudioFrameParameters</a>

#### int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a520ebcda51b5eb488339f3a12dfb8013">setMixedAudioFrameParameters</a>

#### int adjustRecordingSignalVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#acf94e9e0122f09d0450475d7c5809036">adjustRecordingSignalVolume</a>

#### int adjustPlaybackSignalVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a98919705c8b2346811f91f9ce5e97a79">adjustPlaybackSignalVolume</a> 

#### int enableWebSdkInteroperability(bool enabled);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a639ef31212b9f340b518d0e59405789a">enableWebSdkInteroperability</a> 

#### int setLocalPublishFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a6f411291eb8b834442b44361f78fa81f">setLocalPublishFallbackOption</a>

#### int setRemoteSubscribeFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#afd251e3f353a31d470ff9e60c3c3c5de">setRemoteSubscribeFallbackOption</a>

#### int switchCamera();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a4797ff769b840d8f44d24ba6f6b275ed">switchCamera</a> 

#### int switchCamera(CAMERA_DIRECTION direction);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aafcd45adf48b140d579eb05c333f4e32">switchCamera</a>

#### int setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a7f4ff70df2b062deb51cca0644f9a81a">setDefaultAudioRouteToSpeakerphone</a> 

#### int setEnableSpeakerphone(bool speakerOn);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a2e818346d3b814449cbc627f469937a6">setEnableSpeakerphone</a>

#### int setInEarMonitoringVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a407fdc268519a4a23a102afec44bf2e6">setInEarMonitoringVolume</a>

#### bool isSpeakerphoneEnabled();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aae7ff33919c92fd27633ba608fff7fc4">isSpeakerphoneEnabled</a>

#### int setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#af6294b13515f2ed72801fd3b11d1283f">setAudioSessionOperationRestriction</a>

#### int enableLoopbackRecording(bool enabled, const char* deviceName = nullptr);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a86e2db9244c0edc395168a1ab6708102">enableLoopbackRecording</a> 

#### int startScreenCaptureByDisplayId(unsigned int displayId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a4fe820ff5b886636494404fc7ed4ee0d">startScreenCaptureByDisplayId</a>

#### int startScreenCaptureByScreenRect(const Rectangle& screenRect, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a41893fe9a0ca49c054bf6dbd7d9d68f5">startScreenCaptureByScreenRect</a> 

#### int startScreenCaptureByWindowId(view_t windowId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#add5ba807256e8e4469a512be14e10e52">startScreenCaptureByWindowId</a>

#### int setScreenCaptureContentHint(VideoContentHint contentHint);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aff9003c492450dbd8c3f3b9835186c95">setScreenCaptureContentHint</a>

#### int updateScreenCaptureParameters(const ScreenCaptureParameters& captureParams);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ad680e114ba3b8a0012454af6867c7498">updateScreenCaptureParameters</a>

#### int updateScreenCaptureRegion(const Rectangle& regionRect);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ae2ab9c3ff28b64c601f938ab45644586">updateScreenCaptureRegion</a>

#### int stopScreenCapture();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a77412ab7c8653289a28212e60bd00673">stopScreenCapture</a> 

#### int startScreenCapture(agora::rtc::IRtcEngine::WindowIDType windowId, int captureFreq, const Rect* rect, int bitrate);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#af71935ad435402f776bcfc2be3cf687f">startScreenCapture</a> 

#### int updateScreenCaptureRegion(const Rect* rect);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a99ce13ce3b9b2c65e5ec35b9861b56e3">updateScreenCaptureRegion</a> 

#### int getCallId(agora::util::AString& callId);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#af67688d89526926718edb26938d65541">getCallId</a>

#### int rate(const char* callId, int rating, const char* description);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a748c30a6339ec9798daa0d1b21585411">rate</a>

#### int complain(const char* callId, const char* description);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ab8031b21d72c846e9d501fbe6ca10678">complain</a>

#### const char* getVersion(int* build);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aa5605279f597cca69f77a062045675d6">getVersion</a>

#### int enableLastmileTest();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a2803623f129eeb92503a7a4e5a09a46d">enableLastmileTest</a>

#### int disableLastmileTest();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a544fb9fda664578b80bbd7dbfffafd53">disableLastmileTest</a>

#### int startLastmileProbeTest(const LastmileProbeConfig& config);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#adb3ab7a20afca02f5a5ab6fafe026f2b">startLastmileProbeTest</a>

#### int stopLastmileProbeTest();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a94f3494035429684a750e1dee7ef1593">stopLastmileProbeTest</a>

#### const char* getErrorDescription(int code);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#af567b0dd7a1a498319549139fdf13f32">getErrorDescription</a>

#### int setEncryptionSecret(const char* secret);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a645ca5e58735b789803d8a1f1a62cc8b">setEncryptionSecret</a>

#### int setEncryptionMode(const char* encryptionMode);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#af9e7de996bd81f0aea4c79a404eac2aa">setEncryptionMode</a>

#### int registerPacketObserver(IPacketObserver* observer);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a95b53a32d598c3d98a51c24f7f9af4b4">registerPacketObserver</a>

#### int createDataStream(int* streamId, bool reliable, bool ordered);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a5a3f0168ca6e2e298e4677e9a8b9550a">createDataStream</a>

#### int sendStreamMessage(int streamId, const char* data, size_t length);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a7006214f7ca3c08d83cc0a4ebcb9febc">sendStreamMessage</a> 

#### int addPublishStreamUrl(const char* url, bool transcodingEnabled);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a5d62a13bd8391af83fb4ce123450f839">addPublishStreamUrl</a>

#### int removePublishStreamUrl(const char* url);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a30e6c64cb616fbd78bedd8c516c320e7">removePublishStreamUrl</a>

#### int setLiveTranscoding(const LiveTranscoding& transcoding);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a0601e4671357dc1ec942cccc5a6a1dde">setLiveTranscoding</a>

#### int addVideoWatermark(const RtcImage& watermark);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a7db71d3de47227f7419202fde0875058">addVideoWatermark</a>

#### int addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a36e51346ec3bd5a7370d7c70d58d9394">addVideoWatermark</a>

#### int clearVideoWatermarks();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aea42a1ea8b83bc807f68526945f40ec6">clearVideoWatermarks</a>

#### int setBeautyEffectOptions(bool enabled, BeautyOptions options);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a5899cc462e5250028c9afada4df98d48">setBeautyEffectOptions</a> 

#### int addInjectStreamUrl(const char* url, const InjectStreamConfig& config);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a42247db589b55d3cfa98d8e1be06d8e6">addInjectStreamUrl</a>

#### int startChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#acb72f911830a6fdb77e0816d7b41dd5c">startChannelMediaRelay</a>

#### int updateChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#afad0d3f3861c770200a884b855276663">updateChannelMediaRelay</a>

#### int stopChannelMediaRelay();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ab4a1c52a83a08f7dacab6de36f4681b8">stopChannelMediaRelay</a>

#### int removeInjectStreamUrl(const char* url);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aff904ee7a5f0a9741d9cead45249f3cf">removeInjectStreamUrl</a>

#### bool registerEventHandler(IRtcEngineEventHandler* eventHandler);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#ae10bc942d2684b474d53b9c0c2d442ab">registerEventHandler</a>

#### bool unregisterEventHandler(IRtcEngineEventHandler* eventHandler);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#aafe546bd6adc0a82847bdcd2f9201823">unregisterEventHandler</a> 

#### agora::rtc::CONNECTION_STATE_TYPE getConnectionState();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a512b149d4dc249c04f9e30bd31767362">getConnectionState</a>

#### int registerMediaMetadataObserver(IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_rtc_engine.html#a84dbf06de1d769b63200d7ec0289cca0">registerMediaMetadataObserver</a> 

## AgoraVideoDeviceManager

Wrapper around 
<a href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_manager.html" target="_blank">agora::rtc::IVideoDeviceManager</a>

### Member Function Documentation

#### static AgoraVideoDeviceManager* Create(AgoraRtcEngine* RtcEngine);
Creates AgoraVideoDeviceManager.

#### VideoDeviceCollection* enumerateVideoDevices();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_manager.html#aef51744162ec544abf2aaf0488ca062d">enumerateVideoDevices</a>

#### int startDeviceTest(agora::rtc::view_t hwnd);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_manager.html#ac148cafcb191841fd4aa7f5b6166b16d">startDeviceTest</a>

#### int stopDeviceTest();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_manager.html#ae3fe9f7ad1ddf4d5cda5e30d14b9d321">stopDeviceTest</a> 

#### int setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_manager.html#aa6b94649288ecc36772db2de0b9cda4f">setDevice</a>

#### int getDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_manager.html#ab032dca18b474de81b768937f281e764">getDevice</a>


## VideoDeviceCollection

Wrapper around 
<a href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_collection.html" target="_blank">agora::rtc::IVideoDeviceCollection</a>

### Member Function Documentation

#### int getCount();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_collection.html#aa16ab5e1a605648d0db7c440688ffb07">getCount</a>

#### int getDevice(int index, char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH], char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_collection.html#a364f926b0506a048e1e3d8fcf1b45c5a">getDevice</a>
		
#### int setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_video_device_collection.html#a9ba9915c60f2c495882fd889855e8e16">setDevice</a>


## AgoraAudioDeviceManager

Wrapper around 
<a href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html" target="_blank">agora::rtc::IAudioDeviceManager </a>

### Member Function Documentation

#### AudioDeviceCollection* enumeratePlaybackDevices();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#aa13c99d575d89e7ceeeb139be723b18a">enumeratePlaybackDevices</a>

#### AudioDeviceCollection* enumerateRecordingDevices();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a1ea4f53d60dc91ea83960885f9ab77ee">enumerateRecordingDevices</a> 

#### int setPlaybackDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a1ee23eae83165a27bcbd88d80158b4f1">setPlaybackDevice</a>

#### int setRecordingDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a723941355030636cd7d183d53cc7ace7">setRecordingDevice</a> 

#### int startPlaybackDeviceTest(const char* testAudioFilePath);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#ae1b2dc82076211b08430e1a2bd023f46">startPlaybackDeviceTest</a> 

#### int stopPlaybackDeviceTest();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a63d1cd6262fcff8bd4f55efba3dc8051">stopPlaybackDeviceTest</a>

#### int setPlaybackDeviceVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#ac14a1238e83303abed2f36e02fcc9366">setPlaybackDeviceVolume</a> 

#### int getPlaybackDeviceVolume(int* volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#aa2adfa033da451580d6de40599f144e8">getPlaybackDeviceVolume</a>

#### int setRecordingDeviceVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#ac24424e86ded2727a532df739ebf8086">setRecordingDeviceVolume</a>

#### int getRecordingDeviceVolume(int* volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#aa891b5504b122208803950b5e9605125">getRecordingDeviceVolume</a> 

#### int setPlaybackDeviceMute(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a769a27af52897bab6cddf5feef112942">setPlaybackDeviceMute</a>

#### int getPlaybackDeviceMute(bool *mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a5b6e580bb5d564b03b77eae73024ebdf">getPlaybackDeviceMute</a>

#### int setRecordingDeviceMute(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#acb215f5d365426280478b0e0e8bccd14">setRecordingDeviceMute</a>

#### int getRecordingDeviceMute(bool* mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a2046033de712dbc3af9d19f0dd9abc2b">getRecordingDeviceMute</a> 

#### int startRecordingDeviceTest(int indicationInterval);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a9e732d31f179a90d388998f5b86ebf06">startRecordingDeviceTest</a>

#### int stopRecordingDeviceTest();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a796e7b8a58eb303f18f04e1e9d12a94b">stopRecordingDeviceTest</a>

#### int getPlaybackDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#aa150b7cc44c76249c50e6228e0dd27db">getPlaybackDevice</a>

#### int getPlaybackDeviceInfo(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH], char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a5dd8dd4493bf0423d741bbe56920517a">getPlaybackDeviceInfo</a> 

#### int getRecordingDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a67ad6439dab0b5043dd715d9ede11693">getRecordingDevice</a> 

#### int getRecordingDeviceInfo(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH], char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#a8497668902057d86f3ed09db64e35620">getRecordingDeviceInfo</a> 

#### int startAudioDeviceLoopbackTest(int indicationInterval);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#ac78c08f3212dc3efa000e197207dec53">startAudioDeviceLoopbackTest</a> 

#### int stopAudioDeviceLoopbackTest();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_manager.html#aad01da1e0bacd3f2fd355483f9e3befb">stopAudioDeviceLoopbackTest</a> 


## AudioDeviceCollection

Wrapper around 
<a href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_collection.html" target="_blank">agora::rtc::IAudioDeviceCollection</a>

### Member Function Documentation

#### int getCount();
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_collection.html#a05427a58e7df6c8d2fbc47a179412d3c">getCount</a> 

#### int getDevice(int index, char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH], char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_collection.html#ae5416ac0d3e7d0b0ec5dca90d0de8208">getDevice</a>

#### int setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_collection.html#a118ee7b6c41e8d6468eab006d7994753">setDevice</a> 

#### int setApplicationVolume(int volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_collection.html#a884619804ef3529815fbefcfbf688891">setApplicationVolume</a>

#### int getApplicationVolume(int& volume);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_collection.html#a9110ddff624236637b8f3cc351273041">getApplicationVolume</a>

#### int setApplicationMute(bool mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_collection.html#a97f19d7c502fb5b1206aa0fb546d808d">setApplicationMute</a> 

#### int isApplicationMute(bool& mute);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1rtc_1_1_i_audio_device_collection.html#af85f1d216ef8a569725e0d093f9e61dc">isApplicationMute</a>


## AgoraMediaEngine

Wrapper around 
<a href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1media_1_1_i_media_engine.html" target="_blank">agora::media::IMediaEngine</a>

### Member Function Documentation

#### static AgoraMediaEngine* Create(agora::rtc::ue4::AgoraRtcEngine* RtcEngine);
Creates AgoraMediaEngine.

#### int registerAudioFrameObserver(agora::media::IAudioFrameObserver* observer);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1media_1_1_i_media_engine.html#ae46ca0d20789787aaab2fb268a524100">registerAudioFrameObserver</a> 

#### int registerVideoFrameObserver(agora::media::IVideoFrameObserver* observer);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1media_1_1_i_media_engine.html#a5eee4dfd1fd46e4a865feba163f3c5de">registerVideoFrameObserver</a>

#### int pushAudioFrame(agora::media::IAudioFrameObserver::AudioFrame* frame);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1media_1_1_i_media_engine.html#a2d3bb76cbc7008960166bb292a193616">pushAudioFrame</a> 

#### int pullAudioFrame(agora::media::IAudioFrameObserver::AudioFrame* frame);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1media_1_1_i_media_engine.html#aaf43fc265eb4707bb59f1bf0cbe01940">pullAudioFrame</a> 

#### int setExternalVideoSource(bool enable, bool useTexture);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1media_1_1_i_media_engine.html#a6716908edc14317f2f6f14ee4b1c01b7">setExternalVideoSource</a>

#### int pushVideoFrame(agora::media::ExternalVideoFrame* frame);
Wraps: <a class="el" href="https://docs.agora.io/en/Video/API%20Reference/cpp/classagora_1_1media_1_1_i_media_engine.html#ae064aedfdb6ac63a981ca77a6b315985">pushVideoFrame</a> 

