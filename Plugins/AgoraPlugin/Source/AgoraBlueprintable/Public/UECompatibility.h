#pragma once
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include <Agora/IAgoraMediaEngine.h>
#include <Agora/IAgoraRtcEngine.h>
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include <memory>

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UECompatibility.generated.h"

/** \file UECompatibility.h
   Contains wrapped enums, classes, structs and conversion functions.
*/

/** Wrapper around void*.
UPlainData class is implemented to use as parent class for custom inheritors where you can handle void*.
Allows using void* in blueprints.
*/
UCLASS( BlueprintType )
class AGORABLUEPRINTABLE_API UPlainData : public UObject
{
   GENERATED_BODY()
public:
   /** Setter */
   void SetPlainData( void* data ) { m_plainData = data; }
   
   /** Getter */
   void* GetPlainData() { return m_plainData; }
   virtual ~UPlainData() = default;
protected:
   /** Plain data that will be used by agora native sdk.*/
   void* m_plainData;
};

/** Properties of the audio volume information.

 An array containing the user ID and volume information for each speaker.
 */
USTRUCT( BlueprintType )
struct FAudioVolumeInfo
{
   GENERATED_BODY();
public:

   /** User ID of the speaker. The uid of the local user is 0.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo" )
   int64 Uid;

   /** The volume of the speaker. The volume ranges between 0 (lowest volume) and 255 (highest volume).
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo" )
   int64 Volume;
   
   /** Voice activity status of the local user.
    * - 0: The local user is not speaking.
    * - 1: The local user is speaking.
    *
    * @note
    * - The `Vad` parameter cannot report the voice activity status of the remote users. In the remote users' callback, `Vad` = 0.
    * - Ensure that you set `report_vad`(true) in the \ref UIAgora::EnableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" method to enable the voice activity detection of the local user.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|AudioVolumeInfo" )
   int64 Vad;
};

/**  Video dimensions. */
USTRUCT( BlueprintType )
struct FVideoDimensions
{
   GENERATED_BODY();
public:
   /** Width (pixels) of the video. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoDimensions" )
      int Width;

   /** Height (pixels) of the video. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoDimensions" )
      int Height;

   FVideoDimensions()
      : Width( 640 ), Height( 480 )
   {}
   FVideoDimensions( int w, int h )
      : Width( w ), Height( h )
   {}
   operator agora::rtc::VideoDimensions()
   {
      return agora::rtc::VideoDimensions( Width, Height );
   }
};

/** Screen sharing encoding parameters.*/
USTRUCT( BlueprintType )
struct FScreenCaptureParameters
{
   GENERATED_BODY();
public:
   /** The maximum encoding dimensions of the shared region in terms of width &times; height.

   The default value is 1920 &times; 1080 pixels, that is, 2073600 pixels. Agora uses the value of this parameter to calculate the charges.

   If the aspect ratio is different between the encoding dimensions and screen dimensions, Agora applies the following algorithms for encoding. Suppose the encoding dimensions are 1920 x 1080:

   - If the value of the screen dimensions is lower than that of the encoding dimensions, for example, 1000 &times; 1000, the SDK uses 1000 &times; 1000 for encoding.
   - If the value of the screen dimensions is higher than that of the encoding dimensions, for example, 2000 &times; 1500, the SDK uses the maximum value under 1920 &times; 1080 with the aspect ratio of the screen dimension (4:3) for encoding, that is, 1440 &times; 1080.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters" )
   FVideoDimensions Dimensions;

   /** The frame rate (fps) of the shared region.

   The default value is 5. We do not recommend setting this to a value greater than 15.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters" )
      int FrameRate;

   /** The bitrate (Kbps) of the shared region.

   The default value is 0 (the SDK works out a bitrate according to the dimensions of the current screen).
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters" )
      int Bitrate;

   /** Sets whether or not to capture the mouse for screen sharing:

   - true: (Default) Capture the mouse.
   - false: Do not capture the mouse.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ScreenCaptureParameters" )
      bool captureMouseCursor;

   FScreenCaptureParameters() : Dimensions( 1920, 1080 ), FrameRate( 5 ), Bitrate( agora::rtc::STANDARD_BITRATE ), captureMouseCursor( true ) {}
   FScreenCaptureParameters( const FVideoDimensions& d, int f, int b, bool c ) : Dimensions( d ), FrameRate( f ), Bitrate( b ), captureMouseCursor( c ) {}
   FScreenCaptureParameters( int width, int height, int f, int b, bool c ) : Dimensions( width, height ), FrameRate( f ), Bitrate( b ), captureMouseCursor( c ) {}
};

/** Function result success indicator. */
UENUM( BlueprintType )
enum class EResult : uint8
{
   /** Function filished successfully */
   Success,
   /** In process error occured */
   Error
};


/** Video frame rates. */
UENUM( BlueprintType )
enum EFRAME_RATE
{
   /** 1: 1 fps */
   FRAME_RATE_FPS_1 = agora::rtc::FRAME_RATE_FPS_1,
   /** 7: 7 fps */
   FRAME_RATE_FPS_7 = agora::rtc::FRAME_RATE_FPS_7,
   /** 10: 10 fps */
   FRAME_RATE_FPS_10 = agora::rtc::FRAME_RATE_FPS_10,
   /** 15: 15 fps */
   FRAME_RATE_FPS_15 = agora::rtc::FRAME_RATE_FPS_15,
   /** 24: 24 fps */
   FRAME_RATE_FPS_24 = agora::rtc::FRAME_RATE_FPS_24,
   /** 30: 30 fps */
   FRAME_RATE_FPS_30 = agora::rtc::FRAME_RATE_FPS_30,
   /** 60: 60 fps (Windows and macOS only) */
   FRAME_RATE_FPS_60 = agora::rtc::FRAME_RATE_FPS_60,
};

/** Video output orientation modes.*/
UENUM( BlueprintType )
enum EORIENTATION_MODE
{
   /** 0: (Default) Adaptive mode.

    The video encoder adapts to the orientation mode of the video input device.

    - If the width of the captured video from the SDK is greater than the height, the encoder sends the video in landscape mode. The encoder also sends the rotational information of the video, and the receiver uses the rotational information to rotate the received video.
    - When you use a custom video source, the output video from the encoder inherits the orientation of the original video. If the original video is in portrait mode, the output video from the encoder is also in portrait mode. The encoder also sends the rotational information of the video to the receiver.
    */
   ORIENTATION_MODE_ADAPTIVE = agora::rtc::ORIENTATION_MODE_ADAPTIVE,
   /** 1: Landscape mode.

    The video encoder always sends the video in landscape mode. The video encoder rotates the original video before sending it and the rotational infomation is 0. This mode applies to scenarios involving CDN live streaming.
    */
   ORIENTATION_MODE_FIXED_LANDSCAPE = agora::rtc::ORIENTATION_MODE_FIXED_LANDSCAPE,
   /** 2: Portrait mode.

    The video encoder always sends the video in portrait mode. The video encoder rotates the original video before sending it and the rotational infomation is 0. This mode applies to scenarios involving CDN live streaming.
    */
   ORIENTATION_MODE_FIXED_PORTRAIT = agora::rtc::ORIENTATION_MODE_FIXED_PORTRAIT,
};

/** Video degradation preferences when the bandwidth is a constraint. */
UENUM( BlueprintType )
enum EDEGRADATION_PREFERENCE
{
   /** 0: (Default) Degrade the frame rate in order to maintain the video quality. */
   MAINTAIN_QUALITY = agora::rtc::MAINTAIN_QUALITY,
   /** 1: Degrade the video quality in order to maintain the frame rate. */
   MAINTAIN_FRAMERATE = agora::rtc::MAINTAIN_FRAMERATE,
   /** 2: (For future use) Maintain a balance between the frame rate and video quality. */
   MAINTAIN_BALANCED = agora::rtc::MAINTAIN_BALANCED,
};

/** Video encoder configurations. */
USTRUCT( BlueprintType )
struct FVideoEncoderConfiguration
{
   GENERATED_BODY();
public:

   /** The video frame dimensions (px) used to specify the video quality and measured by the total number of pixels along a frame's width and height: VideoDimensions. The default value is 640 x 480.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration" )
      FVideoDimensions Dimensions = FVideoDimensions( 640, 480 );

   /** The frame rate of the video: #EFRAME_RATE. The default value is 15.

   Note that we do not recommend setting this to a value greater than 30.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration" )
      TEnumAsByte<EFRAME_RATE> FrameRate = FRAME_RATE_FPS_15;

   /** The minimum frame rate of the video. The default value is -1.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration" )
      int MinFrameRate = -1;

   /** The video encoding bitrate (Kbps).

     Choose one of the following options:

     - #STANDARD_BITRATE: (Recommended) The standard bitrate.
        - The Communication profile: the encoding bitrate equals the base bitrate.
        - The Live-broadcast profile: the encoding bitrate is twice the base bitrate.
     - #COMPATIBLE_BITRATE: The compatible bitrate: the bitrate stays the same regardless of the profile.

     The Communication profile prioritizes smoothness, while the Live-broadcast profile prioritizes video quality (requiring a higher bitrate). We recommend setting the bitrate mode as #STANDARD_BITRATE to address this difference.

     The following table lists the recommended video encoder configurations, where the base bitrate applies to the Communication profile. Set your bitrate based on this table. If you set a bitrate beyond the proper range, the SDK automatically sets it to within the range.

     | Resolution             | Frame Rate (fps) | Base Bitrate (Kbps, for Communication) | Live Bitrate (Kbps, for Live Broadcast)|
     |------------------------|------------------|----------------------------------------|----------------------------------------|
     | 160 &times; 120        | 15               | 65                                     | 130                                    |
     | 120 &times; 120        | 15               | 50                                     | 100                                    |
     | 320 &times; 180        | 15               | 140                                    | 280                                    |
     | 180 &times; 180        | 15               | 100                                    | 200                                    |
     | 240 &times; 180        | 15               | 120                                    | 240                                    |
     | 320 &times; 240        | 15               | 200                                    | 400                                    |
     | 240 &times; 240        | 15               | 140                                    | 280                                    |
     | 424 &times; 240        | 15               | 220                                    | 440                                    |
     | 640 &times; 360        | 15               | 400                                    | 800                                    |
     | 360 &times; 360        | 15               | 260                                    | 520                                    |
     | 640 &times; 360        | 30               | 600                                    | 1200                                   |
     | 360 &times; 360        | 30               | 400                                    | 800                                    |
     | 480 &times; 360        | 15               | 320                                    | 640                                    |
     | 480 &times; 360        | 30               | 490                                    | 980                                    |
     | 640 &times; 480        | 15               | 500                                    | 1000                                   |
     | 480 &times; 480        | 15               | 400                                    | 800                                    |
     | 640 &times; 480        | 30               | 750                                    | 1500                                   |
     | 480 &times; 480        | 30               | 600                                    | 1200                                   |
     | 848 &times; 480        | 15               | 610                                    | 1220                                   |
     | 848 &times; 480        | 30               | 930                                    | 1860                                   |
     | 640 &times; 480        | 10               | 400                                    | 800                                    |
     | 1280 &times; 720       | 15               | 1130                                   | 2260                                   |
     | 1280 &times; 720       | 30               | 1710                                   | 3420                                   |
     | 960 &times; 720        | 15               | 910                                    | 1820                                   |
     | 960 &times; 720        | 30               | 1380                                   | 2760                                   |
     | 1920 &times; 1080      | 15               | 2080                                   | 4160                                   |
     | 1920 &times; 1080      | 30               | 3150                                   | 6300                                   |
     | 1920 &times; 1080      | 60               | 4780                                   | 6500                                   |
     | 2560 &times; 1440      | 30               | 4850                                   | 6500                                   |
     | 2560 &times; 1440      | 60               | 6500                                   | 6500                                   |
     | 3840 &times; 2160      | 30               | 6500                                   | 6500                                   |
     | 3840 &times; 2160      | 60               | 6500                                   | 6500                                   |

   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration" )
      int Bitrate = agora::rtc::STANDARD_BITRATE;

   /** The minimum encoding bitrate (Kbps).

    The SDK automatically adjusts the encoding bitrate to adapt to the network conditions. Using a value greater than the default value forces the video encoder to output high-quality images but may cause more packet loss and hence sacrifice the smoothness of the video transmission. That said, unless you have special requirements for image quality, Agora does not recommend changing this value.

    @note This parameter applies only to the Live-broadcast profile.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration" )
      int MinBitrate = agora::rtc::DEFAULT_MIN_BITRATE;

   /** The video orientation mode of the video: #EORIENTATION_MODE.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration" )
      TEnumAsByte<EORIENTATION_MODE> OrientationMode = ORIENTATION_MODE_ADAPTIVE;

   /** The video encoding degradation preference under limited bandwidth: #EDEGRADATION_PREFERENCE.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoEncoderConfiguration" )
      TEnumAsByte <EDEGRADATION_PREFERENCE> DegradationPreference = MAINTAIN_QUALITY;

   FVideoEncoderConfiguration() {}

   FVideoEncoderConfiguration(
      const FVideoDimensions& d, EFRAME_RATE f,
      int b, EORIENTATION_MODE m )
      : Dimensions( d ), FrameRate( f ), Bitrate( b ), OrientationMode( m )
   {}
   FVideoEncoderConfiguration(
      int width, int height, EFRAME_RATE f,
      int b, EORIENTATION_MODE m )
      : Dimensions( width, height ), FrameRate( f ), Bitrate( b ), OrientationMode( m )
   {}
};

/** Camera capturer configuration.*/
UENUM( BlueprintType )
enum ECAPTURER_OUTPUT_PREFERENCE
{
   /** 0: (Default) self-adapts the camera output parameters to the system performance and network conditions to balance CPU consumption and video preview quality.
   */
   CAPTURER_OUTPUT_PREFERENCE_AUTO = agora::rtc::CAPTURER_OUTPUT_PREFERENCE_AUTO,
   /** 1: Prioritizes the system performance. The SDK chooses the dimension and frame rate of the local camera capture closest to those set by \ref UIAgora::SetVideoEncoderConfiguration "SetVideoEncoderConfiguration".
   */
   CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = agora::rtc::CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE,
   /** 2: Prioritizes the local preview quality. The SDK chooses higher camera output parameters to improve the local video preview quality. This option requires extra CPU and RAM usage for video pre-processing.
   */
   CAPTURER_OUTPUT_PREFERENCE_PREVIEW = agora::rtc::CAPTURER_OUTPUT_PREFERENCE_PREVIEW,
};

/** Audio profiles.

Sets the sample rate, bitrate, encoding mode, and the number of channels:*/
UENUM( BlueprintType )
enum EAUDIO_PROFILE_TYPE
{
   /**
    0: Default audio profile.

    - In the Communication profile, the default value is #AUDIO_PROFILE_SPEECH_STANDARD;
    - In the Live-broadcast profile, the default value is #AUDIO_PROFILE_MUSIC_STANDARD.
    */
   AUDIO_PROFILE_DEFAULT = agora::rtc::AUDIO_PROFILE_DEFAULT, // use default settings
   /**
    1: A sample rate of 32 kHz, audio encoding, mono, and a bitrate of up to 18 Kbps.
    */
   AUDIO_PROFILE_SPEECH_STANDARD = agora::rtc::AUDIO_PROFILE_SPEECH_STANDARD, // 32Khz, 18Kbps, mono, speech
   /**
    2: A sample rate of 48 kHz, music encoding, mono, and a bitrate of up to 48 Kbps.
    */
   AUDIO_PROFILE_MUSIC_STANDARD = agora::rtc::AUDIO_PROFILE_MUSIC_STANDARD, // 48Khz, 48Kbps, mono, music
   /**
    3: A sample rate of 48 kHz, music encoding, stereo, and a bitrate of up to 56 Kbps.
    */
   AUDIO_PROFILE_MUSIC_STANDARD_STEREO = agora::rtc::AUDIO_PROFILE_MUSIC_STANDARD_STEREO, // 48Khz, 56Kbps, stereo, music
   /**
    4: A sample rate of 48 kHz, music encoding, mono, and a bitrate of up to 128 Kbps.
    */
   AUDIO_PROFILE_MUSIC_HIGH_QUALITY = agora::rtc::AUDIO_PROFILE_MUSIC_HIGH_QUALITY, // 48Khz, 128Kbps, mono, music
   /**
    5: A sample rate of 48 kHz, music encoding, stereo, and a bitrate of up to 192 Kbps.
    */
   AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = agora::rtc::AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO, // 48Khz, 192Kbps, stereo, music
   /**
    6: A sample rate of 16 kHz, audio encoding, mono, and Acoustic Echo Cancellation (AES) enabled.
    */
   AUDIO_PROFILE_IOT = agora::rtc::AUDIO_PROFILE_IOT,
   AUDIO_PROFILE_NUM = agora::rtc::AUDIO_PROFILE_NUM,
};

/** Audio application scenarios.*/
UENUM( BlueprintType )
enum EAUDIO_SCENARIO_TYPE// set a suitable scenario for your app type
{
   /** 0: Default. */
   AUDIO_SCENARIO_DEFAULT = agora::rtc::AUDIO_SCENARIO_DEFAULT,
   /** 1: Entertainment scenario, supporting voice during gameplay. */
   AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT = agora::rtc::AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT,
   /** 2: Education scenario, prioritizing smoothness and stability. */
   AUDIO_SCENARIO_EDUCATION = agora::rtc::AUDIO_SCENARIO_EDUCATION,
   /** 3: Live gaming scenario, enabling the gaming audio effects in the speaker mode in a live broadcast scenario. Choose this scenario for high-fidelity music playback. */
   AUDIO_SCENARIO_GAME_STREAMING = agora::rtc::AUDIO_SCENARIO_GAME_STREAMING,
   /** 4: Showroom scenario, optimizing the audio quality with external professional equipment. */
   AUDIO_SCENARIO_SHOWROOM = agora::rtc::AUDIO_SCENARIO_SHOWROOM,
   /** 5: Gaming scenario. */
   AUDIO_SCENARIO_CHATROOM_GAMING = agora::rtc::AUDIO_SCENARIO_CHATROOM_GAMING,
   /** 6: Applicable to the IoT scenario. */
   AUDIO_SCENARIO_IOT = agora::rtc::AUDIO_SCENARIO_IOT,
   AUDIO_SCENARIO_NUM = agora::rtc::AUDIO_SCENARIO_NUM,
};

/** Audio equalization band frequencies. */
UENUM( BlueprintType )
enum EAUDIO_EQUALIZATION_BAND_FREQUENCY
{
   /** 0: 31 Hz */
   AUDIO_EQUALIZATION_BAND_31 = agora::rtc::AUDIO_EQUALIZATION_BAND_31,
   /** 1: 62 Hz */
   AUDIO_EQUALIZATION_BAND_62 = agora::rtc::AUDIO_EQUALIZATION_BAND_62,
   /** 2: 125 Hz */
   AUDIO_EQUALIZATION_BAND_125 = agora::rtc::AUDIO_EQUALIZATION_BAND_125,
   /** 3: 250 Hz */
   AUDIO_EQUALIZATION_BAND_250 = agora::rtc::AUDIO_EQUALIZATION_BAND_250,
   /** 4: 500 Hz */
   AUDIO_EQUALIZATION_BAND_500 = agora::rtc::AUDIO_EQUALIZATION_BAND_500,
   /** 5: 1 kHz */
   AUDIO_EQUALIZATION_BAND_1K = agora::rtc::AUDIO_EQUALIZATION_BAND_1K,
   /** 6: 2 kHz */
   AUDIO_EQUALIZATION_BAND_2K = agora::rtc::AUDIO_EQUALIZATION_BAND_2K,
   /** 7: 4 kHz */
   AUDIO_EQUALIZATION_BAND_4K = agora::rtc::AUDIO_EQUALIZATION_BAND_4K,
   /** 8: 8 kHz */
   AUDIO_EQUALIZATION_BAND_8K = agora::rtc::AUDIO_EQUALIZATION_BAND_8K,
   /** 9: 16 kHz */
   AUDIO_EQUALIZATION_BAND_16K = agora::rtc::AUDIO_EQUALIZATION_BAND_16K,
};

/** Audio reverberation types. */
UENUM( BlueprintType )
enum EAUDIO_REVERB_TYPE
{
   /** 0: The level of the dry signal (db). The value is between -20 and 10. */
   AUDIO_REVERB_DRY_LEVEL = agora::rtc::AUDIO_REVERB_DRY_LEVEL, // (dB, [-20,10]), the level of the dry signal
   /** 1: The level of the early reflection signal (wet signal) (dB). The value is between -20 and 10. */
   AUDIO_REVERB_WET_LEVEL = agora::rtc::AUDIO_REVERB_WET_LEVEL, // (dB, [-20,10]), the level of the early reflection signal (wet signal)
   /** 2: The room size of the reflection. The value is between 0 and 100. */
   AUDIO_REVERB_ROOM_SIZE = agora::rtc::AUDIO_REVERB_ROOM_SIZE, // ([0,100]), the room size of the reflection
   /** 3: The length of the initial delay of the wet signal (ms). The value is between 0 and 200. */
   AUDIO_REVERB_WET_DELAY = agora::rtc::AUDIO_REVERB_WET_DELAY, // (ms, [0,200]), the length of the initial delay of the wet signal in ms
   /** 4: The reverberation strength. The value is between 0 and 100. */
   AUDIO_REVERB_STRENGTH = agora::rtc::AUDIO_REVERB_STRENGTH, // ([0,100]), the strength of the reverberation
};

/** Local voice reverberation presets. */
UENUM( BlueprintType )
enum EAUDIO_REVERB_PRESET
{
   /** 0: The original voice (no local voice reverberation).
    */
   AUDIO_REVERB_OFF = agora::rtc::AUDIO_REVERB_OFF, // Turn off audio reverb
   /** 1: Pop music.
   */
   AUDIO_REVERB_POPULAR = agora::rtc::AUDIO_REVERB_POPULAR,
   /** 2: R&B.
   */
   AUDIO_REVERB_RNB = agora::rtc::AUDIO_REVERB_RNB,
   /** 3: Rock music.
   */
   AUDIO_REVERB_ROCK = agora::rtc::AUDIO_REVERB_ROCK,
   /** 4: Hip-hop.
   */
   AUDIO_REVERB_HIPHOP = agora::rtc::AUDIO_REVERB_HIPHOP,
   /** 5: Pop concert.
   */
   AUDIO_REVERB_VOCAL_CONCERT = agora::rtc::AUDIO_REVERB_VOCAL_CONCERT,
   /** 6: Karaoke.
   */
   AUDIO_REVERB_KTV = agora::rtc::AUDIO_REVERB_KTV,
   /** 7: Recording studio.
   */
   AUDIO_REVERB_STUDIO = agora::rtc::AUDIO_REVERB_STUDIO
};

/** Client roles in a live broadcast. */
UENUM( BlueprintType )
enum ECLIENT_ROLE_TYPE
{
   /** 1: Host */
   CLIENT_ROLE_BROADCASTER = agora::rtc::CLIENT_ROLE_BROADCASTER,
   /** 2: Audience */
   CLIENT_ROLE_AUDIENCE = agora::rtc::CLIENT_ROLE_AUDIENCE,
};

/** The priority of the remote user.*/
UENUM( BlueprintType )
enum EPRIORITY_TYPE
{
   /** 50: The user's priority is high.
   */
   PRIORITY_HIGH = agora::rtc::PRIORITY_HIGH,
   /** 100: (Default) The user's priority is normal.
   */
   PRIORITY_NORMAL = agora::rtc::PRIORITY_NORMAL,
};

/** Video display modes. */
UENUM( BlueprintType )
enum ERENDER_MODE_TYPE
{
   /**
   1: Uniformly scale the video until it fills the visible boundaries (cropped). One dimension of the video may have clipped contents.
   */
   RENDER_MODE_HIDDEN = agora::rtc::RENDER_MODE_HIDDEN,
   /**
   2: Uniformly scale the video until one of its dimension fits the boundary (zoomed to fit). Areas that are not filled due to disparity in the aspect ratio are filled with black.
   */
   RENDER_MODE_FIT = agora::rtc::RENDER_MODE_FIT,
   /** **DEPRECATED** 
   3: This mode is deprecated.
   */
   RENDER_MODE_ADAPTIVE = agora::rtc::RENDER_MODE_ADAPTIVE,
};

/** Audio codec profile types. The default value is LC_ACC. */
UENUM( BlueprintType )
enum EAUDIO_CODEC_PROFILE_TYPE
{
   /** 0: LC-AAC, which is the low-complexity audio codec type. */
   AUDIO_CODEC_PROFILE_LC_AAC = agora::rtc::AUDIO_CODEC_PROFILE_LC_AAC,
   /** 1: HE-AAC, which is the high-efficiency audio codec type. */
   AUDIO_CODEC_PROFILE_HE_AAC = agora::rtc::AUDIO_CODEC_PROFILE_HE_AAC,
};

/** Camera capturer configuration.*/
USTRUCT( BlueprintType )
struct FCameraCapturerConfiguration
{
   GENERATED_BODY()
public:
   /** Camera capturer preference settings.See: #ECAPTURER_OUTPUT_PREFERENCE. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|CameraCapturerConfiguration" )
      TEnumAsByte<ECAPTURER_OUTPUT_PREFERENCE> Preference;
};

/** Use modes of the \ref UIAgora::OnRecordAudioFrameDelegate "OnRecordAudioFrame" callback. */
UENUM( BlueprintType )
enum ERAW_AUDIO_FRAME_OP_MODE_TYPE
{
   //todo:: replace agora::media::IAudioFrameObserver::AudioFrame
   /** 0: Read-only mode: Users only read the \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame" data without modifying anything. For example, when users acquire the data with the Agora SDK, then push the RTMP streams. */
   RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = agora::rtc::RAW_AUDIO_FRAME_OP_MODE_READ_ONLY,
   /** 1: Write-only mode: Users replace the \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame" data with their own data and pass the data to the SDK for encoding. For example, when users acquire the data. */
   RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = agora::rtc::RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY,
   /** 2: Read and write mode: Users read the data from \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame", modify it, and then play it. For example, when users have their own sound-effect processing module and perform some voice pre-processing, such as a voice change. */
   RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = agora::rtc::RAW_AUDIO_FRAME_OP_MODE_READ_WRITE,
};

/** Stream fallback options. */
UENUM( BlueprintType )
enum ESTREAM_FALLBACK_OPTIONS
{
   /** 0: No fallback behavior for the local/remote video stream when the uplink/downlink network conditions are poor. The quality of the stream is not guaranteed. */
   STREAM_FALLBACK_OPTION_DISABLED = agora::rtc::STREAM_FALLBACK_OPTION_DISABLED,
   /** 1: Under poor downlink network conditions, the remote video stream, to which you subscribe, falls back to the low-stream (low resolution and low bitrate) video. You can set this option only in the \ref UIAgora::SetRemoteSubscribeFallbackOption "setRemoteSubscribeFallbackOption" method. Nothing happens when you set this in the \ref UIAgora::SetLocalPublishFallbackOption "setLocalPublishFallbackOption" method. */
   STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = agora::rtc::STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW,
   /** 2: Under poor uplink network conditions, the locally published video stream falls back to audio only.

   Under poor downlink network conditions, the remote video stream, to which you subscribe, first falls back to the low-stream (low resolution and low bitrate) video; and then to an audio-only stream if the network conditions worsen.*/
   STREAM_FALLBACK_OPTION_AUDIO_ONLY = agora::rtc::STREAM_FALLBACK_OPTION_AUDIO_ONLY,
};

/** Local voice changer options. */
UENUM( BlueprintType )
enum EVOICE_CHANGER_PRESET
{
   /** 0: The original voice (no local voice change).*/
   VOICE_CHANGER_OFF = agora::rtc::VOICE_CHANGER_OFF, //Turn off the voice changer
   /** 1: An old man's voice.*/
   VOICE_CHANGER_OLDMAN = agora::rtc::VOICE_CHANGER_OLDMAN,
   /** 2: A little boy's voice.*/
   VOICE_CHANGER_BABYBOY = agora::rtc::VOICE_CHANGER_BABYBOY,
   /** 3: A little girl's voice.*/
   VOICE_CHANGER_BABYGIRL = agora::rtc::VOICE_CHANGER_BABYGIRL,
   /** 4: The voice of a growling bear.*/
   VOICE_CHANGER_ZHUBAJIE = agora::rtc::VOICE_CHANGER_ZHUBAJIE,
   /** 5: Ethereal vocal effects.*/
   VOICE_CHANGER_ETHEREAL = agora::rtc::VOICE_CHANGER_ETHEREAL,
   /** 6: Hulk's voice.*/
   VOICE_CHANGER_HULK = agora::rtc::VOICE_CHANGER_HULK
};

/** Video mirror modes. */
UENUM( BlueprintType )
enum EVIDEO_MIRROR_MODE_TYPE
{
   /** 0: The default mirror mode is determined by the SDK. */
   VIDEO_MIRROR_MODE_AUTO = agora::rtc::VIDEO_MIRROR_MODE_AUTO,//determined by SDK
   /** 1: Enable mirror mode. */
   VIDEO_MIRROR_MODE_ENABLED = agora::rtc::VIDEO_MIRROR_MODE_ENABLED,//enabled mirror
   /** 2: Disable mirror mode. */
   VIDEO_MIRROR_MODE_DISABLED = agora::rtc::VIDEO_MIRROR_MODE_DISABLED,//disable mirror
};

/** Audio recording qualities.*/
UENUM( BlueprintType )
enum EAUDIO_RECORDING_QUALITY_TYPE
{
   /** 0: Low quality. The sample rate is 32 kHz, and the file size is around
    * 1.2 MB after 10 minutes of recording.
   */
   AUDIO_RECORDING_QUALITY_LOW = agora::rtc::AUDIO_RECORDING_QUALITY_LOW,
   /** 1: Medium quality. The sample rate is 32 kHz, and the file size is
    * around 2 MB after 10 minutes of recording.
   */
   AUDIO_RECORDING_QUALITY_MEDIUM = agora::rtc::AUDIO_RECORDING_QUALITY_MEDIUM,
   /** 2: High quality. The sample rate is 32 kHz, and the file size is
    * around 3.75 MB after 10 minutes of recording.
   */
   AUDIO_RECORDING_QUALITY_HIGH = agora::rtc::AUDIO_RECORDING_QUALITY_HIGH,
};

/** The contrast level, used with the @p lightening parameter.*/
UENUM( BlueprintType )
enum ELIGHTENING_CONTRAST_LEVEL
{
   /** Low contrast level. */
   LIGHTENING_CONTRAST_LOW = agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LOW,
   /** (Default) Normal contrast level. */
   LIGHTENING_CONTRAST_NORMAL = agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_NORMAL,
   /** High contrast level. */
   LIGHTENING_CONTRAST_HIGH = agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_HIGH
};

/** Audio-sample rates. */
UENUM( BlueprintType )
enum EAUDIO_SAMPLE_RATE_TYPE
{
   /** 32000: 32 kHz */
   AUDIO_SAMPLE_RATE_32000 = agora::rtc::AUDIO_SAMPLE_RATE_32000,
   /** 44100: 44.1 kHz */
   AUDIO_SAMPLE_RATE_44100 = agora::rtc::AUDIO_SAMPLE_RATE_44100,
   /** 48000: 48 kHz */
   AUDIO_SAMPLE_RATE_48000 = agora::rtc::AUDIO_SAMPLE_RATE_48000,
};

/** Video codec profile types. */
UENUM( BlueprintType )
enum EVIDEO_CODEC_PROFILE_TYPE
{  /** 66: Baseline video codec profile. Generally used in video calls on mobile phones. */
   VIDEO_CODEC_PROFILE_BASELINE = agora::rtc::VIDEO_CODEC_PROFILE_BASELINE,
   /** 77: Main video codec profile. Generally used in mainstream electronics such as MP4 players, portable video players, PSP, and iPads. */
   VIDEO_CODEC_PROFILE_MAIN = agora::rtc::VIDEO_CODEC_PROFILE_MAIN,
   /** 100: (Default) High video codec profile. Generally used in high-resolution broadcasts or television. */
   VIDEO_CODEC_PROFILE_HIGH = agora::rtc::VIDEO_CODEC_PROFILE_HIGH,
};

/** Image enhancement options.*/
USTRUCT( BlueprintType )
struct FBeautyOptions
{
   GENERATED_BODY();

   /** The contrast level, used with the @p lightening parameter.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions" )
      TEnumAsByte <ELIGHTENING_CONTRAST_LEVEL> LighteningContrastLevel;

   /** The brightness level. The value ranges from 0.0 (original) to 1.0. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions" )
      float LighteningLevel;

   /** The sharpness level. The value ranges between 0 (original) and 1. This parameter is usually used to remove blemishes.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions" )
      float SmoothnessLevel;

   /** The redness level. The value ranges between 0 (original) and 1. This parameter adjusts the red saturation level.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|BeautyOptions" )
      float RednessLevel;

   FBeautyOptions( ELIGHTENING_CONTRAST_LEVEL contrastLevel, float lightening, float smoothness, float redness )
      : LighteningContrastLevel( contrastLevel ),
      LighteningLevel( lightening ),
      SmoothnessLevel( smoothness ),
      RednessLevel( redness )
   {}

   FBeautyOptions()
      : LighteningContrastLevel( LIGHTENING_CONTRAST_NORMAL ),
      LighteningLevel( 0 ),
      SmoothnessLevel( 0 ),
      RednessLevel( 0 )
   {}
};

/** The definition of ChannelMediaInfo. */
USTRUCT( BlueprintType )
struct FChannelMediaInfo
{
   GENERATED_BODY()
public:

   /** The channel name. The default value is NULL, which means that the SDK
   * applies the current channel name.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaInfo" )
      FString ChannelName;

   /** The token that enables the user to join the channel. The default value
    * is NULL, which means that the SDK applies the current token.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaInfo" )
      FString Token;

   /** The user ID.
    *
    * @note
    * String user accounts are not supported in media stream relay.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaInfo" )
      int Uid;
};

/** The definition of ChannelMediaRelayConfiguration.*/
USTRUCT( BlueprintType )
struct FChannelMediaRelayConfiguration
{
   GENERATED_BODY()
public:

   /** Source channel: FChannelMediaInfo.
   *
   * @note
   * - `Uid`: ID of the user whose media stream you want to relay. We
   * recommend setting it as 0, which means that the SDK relays the media
   * stream of the current broadcaster.
   * - If you do not use a token, we recommend using the default values of
   * the parameters in FChannelMediaInfo.
   * - If you use a token, set uid as 0, and ensure that the token is
   * generated with the uid set as 0.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration" )
      FChannelMediaInfo SrcInfo;

   /** Destination channel: FChannelMediaInfo. If you want to
    * relay the media stream to multiple channels, define as many
    * FChannelMediaInfo structs (at most four).
    *
    * @note `Uid`: ID of the user who is in the source channel.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|ChannelMediaRelayConfiguration" )
      TArray<FChannelMediaInfo> DestInfos;

   agora::rtc::ChannelMediaRelayConfiguration convert( std::unique_ptr< agora::rtc::ChannelMediaInfo >& SrcInfo,
                                                       std::unique_ptr< agora::rtc::ChannelMediaInfo[] >& DestInfos ) const;
};

/** Configuration of the imported live broadcast voice or video stream.*/
USTRUCT( BlueprintType )
struct FInjectStreamConfig
{
   GENERATED_BODY()
public:

   /** Width of the added stream in the live broadcast. The default value is 0 (same width as the original stream).
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig" )
      int width;

   /** Height of the added stream in the live broadcast. The default value is 0 (same height as the original stream).
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig" )
      int Height;

   /** Video GOP of the added stream in the live broadcast in frames. The default value is 30 fps.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig" )
      int VideoGop;

   /** Video frame rate of the added stream in the live broadcast. The default value is 15 fps.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig" )
      int VideoFramerate;

   /** Video bitrate of the added stream in the live broadcast. The default value is 400 Kbps.

    @note The setting of the video bitrate is closely linked to the resolution. If the video bitrate you set is beyond a reasonable range, the SDK sets it within a reasonable range.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig" )
      int VideoBitrate;

   /** Audio-sample rate of the added stream in the live broadcast: #EAUDIO_SAMPLE_RATE_TYPE. The default value is 48000 Hz.

    @note We recommend setting the default value.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig" )
      TEnumAsByte< EAUDIO_SAMPLE_RATE_TYPE > AudioSampleRate;

   /** Audio bitrate of the added stream in the live broadcast. The default value is 48.

    @note We recommend setting the default value.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig" )
      int AudioBitrate;

   /** Audio channels in the live broadcast.

    - 1: (Default) Mono
    - 2: Two-channel stereo

    @note We recommend setting the default value.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|InjectStreamConfig" )
      int AudioChannels;

   // width / height default set to 0 means pull the stream with its original resolution
   FInjectStreamConfig()
      : width( 0 )
      , Height( 0 )
      , VideoGop( 30 )
      , VideoFramerate( 15 )
      , VideoBitrate( 400 )
      , AudioSampleRate( AUDIO_SAMPLE_RATE_48000 )
      , AudioBitrate( 48 )
      , AudioChannels( 1 )
   {}
};

/** Configurations of the last-mile network probe test. */
USTRUCT( BlueprintType )
struct FLastmileProbeConfig
{
   GENERATED_BODY()
public:

   /** Sets whether or not to test the uplink network. Some users, for example, the audience in a Live-broadcast channel, do not need such a test:
   - true: test.
   - false: do not test. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig" )
      bool ProbeUplink;

   /** Sets whether or not to test the downlink network:
   - true: test.
   - false: do not test. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig" )
      bool ProbeDownlink;

   /** The expected maximum sending bitrate (Kbps) of the local user. The value ranges between 100 and 5000. We recommend setting this parameter according to the bitrate value set by \ref UIAgora::SetVideoEncoderConfiguration "SetVideoEncoderConfiguration". */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig" )
      int64 ExpectedUplinkBitrate;

   /** The expected maximum receiving bitrate (Kbps) of the local user. The value ranges between 100 and 5000. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeConfig" )
      int64 ExpectedDownlinkBitrate;
};

/** Image properties.

 The properties of the watermark and background images.
 */
USTRUCT( BlueprintType )
struct FRtcImage
{
   GENERATED_BODY()
public:

   /** HTTP/HTTPS URL address of the image on the broadcasting video. The maximum length of this parameter is 1024 bytes. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage" )
      FString Url;

   /** Horizontal position of the image from the upper left of the broadcasting video. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage" )
      int X;

   /** Vertical position of the image from the upper left of the broadcasting video. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage" )
      int Y;

   /** Width of the image on the broadcasting video. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage" )
      int Width;

   /** Height of the image on the broadcasting video. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcImage" )
      int Height;

   FRtcImage() :
      Url( "" ),
      X( 0 ),
      Y( 0 ),
      Width( 0 ),
      Height( 0 )
   {}
};

/** The video properties of the user displaying the video in the CDN live. Agora supports a maximum of 17 transcoding users in a CDN streaming channel.
*/
USTRUCT( BlueprintType )
struct FAgoraTranscodingUser
{
   GENERATED_BODY()
public:
   /** User ID of the user displaying the video in the CDN live.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser" )
      int Uid;

   /** Horizontal position (pixel) of the video frame relative to the top left corner.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser" )
      int X;
   /** Vertical position (pixel) of the video frame relative to the top left corner.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser" )
      int Y;
   /** Width (pixel) of the video frame. The default value is 360.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser" )
      int Width;
   /** Height (pixel) of the video frame. The default value is 640.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser" )
      int Height;

   /** Layer position of the video frame. The value ranges between 0 and 100.

    - 0: (Default) Lowest
    - 100: Highest

    @note
    - If zOrder is beyond this range, the SDK reports #ERR_INVALID_ARGUMENT.
    - As of v2.3, the SDK supports zOrder = 0.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser" )
      int ZOrder;

   /**  Transparency of the video frame in CDN live. The value ranges between 0 and 1.0:

    - 0: Completely transparent
    - 1.0: (Default) Opaque
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser" )
      float Alpha;

   /** The audio channel of the sound. The default value is 0:

    - 0: (Default) Supports dual channels at most, depending on the upstream of the broadcaster.
    - 1: The audio stream of the broadcaster uses the FL audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
    - 2: The audio stream of the broadcaster uses the FC audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
    - 3: The audio stream of the broadcaster uses the FR audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
    - 4: The audio stream of the broadcaster uses the BL audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
    - 5: The audio stream of the broadcaster uses the BR audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.

    @note If your setting is not 0, you may need a specialized player.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|TranscodingUser" )
      int AudioChannel;

   FAgoraTranscodingUser()
      : Uid( 0 )
      , X( 0 )
      , Y( 0 )
      , Width( 0 )
      , Height( 0 )
      , ZOrder( 0 )
      , Alpha( 1.0 )
      , AudioChannel( 0 )
   {}

};

/** A struct for managing CDN live audio/video transcoding settings.
*/
USTRUCT( BlueprintType )
struct FLiveTranscoding
{
   GENERATED_BODY()
public:

   /** Width of the video. The default value is 360. The minimum value of width &times; height is 16 &times; 16.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      int Width;

   /** Height of the video. The default value is 640. The minimum value of width &times; height is 16 &times; 16.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      int Height;

   /** Bitrate of the CDN live output video stream. The default value is 400 Kbps.

   Set this parameter according to the Video Bitrate Table. If you set a bitrate beyond the proper range, the SDK automatically adapts it to a value within the range.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      int VideoBitrate;

   /** Frame rate of the output video stream set for the CDN live broadcast. The default value is 15 fps, and the value range is (0,30].

   @note Agora adjusts all values over 30 to 30.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      int VideoFramerate;

   /** **DEPRECATED** Latency mode:

    - true: Low latency with unassured quality.
    - false: (Default) High latency with assured quality.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      bool LowLatency;

   /** Video GOP in frames. The default value is 30 fps.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      int VideoGop;

   /** Self-defined video codec profile: #EVIDEO_CODEC_PROFILE_TYPE.

  @note If you set this parameter to other values, Agora adjusts it to the default value of 100.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      TEnumAsByte < EVIDEO_CODEC_PROFILE_TYPE > VideoCodecProfile;

   /** The background color in RGB hex value. Value only, do not include a #. For example, 0xFFB6C1 (light pink). The default value is 0x000000 (black).
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      int64 BackgroundColor;

   /** TranscodingUser */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      TArray<FAgoraTranscodingUser> TranscodingUsers;

   /** Reserved property. Extra user-defined information to send SEI for the H.264/H.265 video stream to the CDN live client. Maximum length: 4096 Bytes.

    For more information on SEI frame, see [SEI-related questions](https://docs.agora.io/cn/Agora%20Platform/live_related_faq?platform=%E7%9B%B4%E6%92%AD%E7%9B%B8%E5%85%B3#sei).
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      FString TranscodingExtraInfo;

   /** **DEPRECATED** The metadata sent to the CDN live client defined by the RTMP or FLV metadata.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      FString Metadata;

   /** Self-defined audio-sample rate: #EAUDIO_SAMPLE_RATE_TYPE.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      TEnumAsByte < EAUDIO_SAMPLE_RATE_TYPE > AudioSampleRate;

   /** Bitrate of the CDN live audio output stream. The default value is 48 Kbps, and the highest value is 128.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      int AudioBitrate;

   /** Agora's self-defined audio-channel types. We recommend choosing option 1 or 2. A special player is required if you choose option 3, 4, or 5:

    - 1: (Default) Mono
    - 2: Two-channel stereo
    - 3: Three-channel stereo
    - 4: Four-channel stereo
    - 5: Five-channel stereo
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      int AudioChannels;

   /** Self-defined audio codec profile: #EAUDIO_CODEC_PROFILE_TYPE.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      TEnumAsByte < EAUDIO_CODEC_PROFILE_TYPE > AudioCodecProfile;

   /** The watermark image added to the CDN live publishing stream.

   Ensure that the format of the image is PNG. Once a watermark image is added, the audience of the CDN live publishing stream can see the watermark image. See FRtcImage.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      FRtcImage Watermark;

   /** The background image added to the CDN live publishing stream.

    Once a background image is added, the audience of the CDN live publishing stream can see the background image. See FRtcImage.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LiveTranscoding" )
      FRtcImage BackgroundImage;

   agora::rtc::LiveTranscoding convert( std::unique_ptr< agora::rtc::TranscodingUser[] >& users,
                                        std::unique_ptr< agora::rtc::RtcImage >& Watermark,
                                        std::unique_ptr< agora::rtc::RtcImage >& BackgroundImage ) const;

   FLiveTranscoding()
      : Width( 360 )
      , Height( 640 )
      , VideoBitrate( 400 )
      , VideoFramerate( 15 )
      , LowLatency( false )
      , VideoGop( 30 )
      , VideoCodecProfile( VIDEO_CODEC_PROFILE_HIGH )
      , BackgroundColor( 0 )
      , TranscodingExtraInfo( "" )
      , Metadata( "" )
      , AudioSampleRate( AUDIO_SAMPLE_RATE_48000 )
      , AudioBitrate( 48 )
      , AudioChannels( 1 )
      , AudioCodecProfile( AUDIO_CODEC_PROFILE_LC_AAC )
   {}
};

USTRUCT(BlueprintType)
struct FAgoraUserInfo
{
   GENERATED_BODY()
public:
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo" )
      int64 Uid;
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|UserInfo" )
      FString UserAccount;

   FAgoraUserInfo()
      : Uid( 0 )
      , UserAccount(TEXT(""))
   {}
};

/** Video display settings of the VideoCanvas class.*/
USTRUCT( BlueprintType )
struct FVideoCanvas
{
   GENERATED_BODY()
public:
   /** Video display window (view).*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas" )
      UPlainData* View;

   /** Video display mode: #ERENDER_MODE_TYPE.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas" )
      int RenderMode;

   /**  User Id*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas" )
      int64 Uid;

   /** Private data (underlying video engine denotes it) */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|VideoCanvas" )
      UPlainData* Priv;

   FVideoCanvas()
      : RenderMode( RENDER_MODE_HIDDEN )
      , Uid( 0 )
   {}
   FVideoCanvas( void* v, int m, int u )
      : RenderMode( m )
      , Uid( u )
   {
      if( View )
         View->SetPlainData( v );
   }
};

/** The relative location of the region to the screen or window.*/
USTRUCT( BlueprintType )
struct FRectangle
{
   GENERATED_BODY()
public:

   /** The horizontal offset from the top-left corner.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle" )
      int X;

   /** The vertical offset from the top-left corner.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle" )
      int Y;

   /** The width of the region.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle" )
      int Width;

   /** The height of the region.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|Rectangle" )
      int Height;

   FRectangle() : X( 0 ), Y( 0 ), Width( 0 ), Height( 0 ) {}
   FRectangle( int xx, int yy, int ww, int hh ) : X( xx ), Y( yy ), Width( ww ), Height( hh ) {}
};

/** The options of the watermark image to be added. */
USTRUCT( BlueprintType )
struct FWatermarkOptions
{
   GENERATED_BODY()
public:
   /** Sets whether or not the watermark image is visible in the local video preview:
    * - true: The watermark image is visible in preview.
    * - false: The watermark image is not visible in preview.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions" )
      bool VisibleInPreview;

   /**
    * The watermark position in the landscape mode. See Rectangle.
    * For detailed information on the landscape mode, see [Rotate the video](https://docs.agora.io/en/Interactive%20Broadcast/rotation_guide_windows?platform=Windows).
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions" )
      FRectangle PositionInLandscapeMode;
   /**
    * The watermark position in the portrait mode. See Rectangle.
    * For detailed information on the portrait mode, see [Rotate the video](https://docs.agora.io/en/Interactive%20Broadcast/rotation_guide_windows?platform=Windows).
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|WatermarkOptions" )
      FRectangle PositionInPortraitMode;

   FWatermarkOptions()
      : VisibleInPreview( false )
      , PositionInLandscapeMode( 0, 0, 0, 0 )
      , PositionInPortraitMode( 0, 0, 0, 0 )
   {}
};

/** Statistics of the channel.*/
USTRUCT( BlueprintType )
struct FRtcStats
{
   GENERATED_BODY()
public:

   /** Call duration (s), represented by an aggregate value. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int64 duration;

   /** Total number of bytes transmitted, represented by an aggregate value.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int64 TxBytes;

   /** Total number of bytes received, represented by an aggregate value. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int64 RxBytes;

   /** Total number of audio bytes sent (bytes), represented
   * by an aggregate value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int64 TxAudioBytes;

   /** Total number of video bytes sent (bytes), represented
   * by an aggregate value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int64 TxVideoBytes;

   /** Total number of audio bytes received (bytes) before
   * network countermeasures, represented by an aggregate value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int64 RxAudioBytes;

   /** Total number of video bytes received (bytes),
   * represented by an aggregate value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int64 RxVideoBytes;

   /**
   Transmission bitrate (Kbps), represented by an instantaneous value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 TxKBitRate;

   /**
   Receive bitrate (Kbps), represented by an instantaneous value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 RxKBitRate;

   /**
   Audio receive bitrate (Kbps), represented by an instantaneous value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 RxAudioKBitRate;

   /**
   Audio transmission bitrate (Kbps), represented by an instantaneous value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 TxAudioKBitRate;

   /**
   Video receive bitrate (Kbps), represented by an instantaneous value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 RxVideoKBitRate;

   /**
   Video transmission bitrate (Kbps), represented by an instantaneous value.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 TxVideoKBitRate;

   /** Client-server latency (ms) */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 LastmileDelay;

   /** The packet loss rate (%) from the local client to Agora's edge server,
   * before using the anti-packet-loss method.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 TxPacketLossRate;

   /** The packet loss rate (%) from Agora's edge server to the local client,
    * before using the anti-packet-loss method.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int32 RxPacketLossRate;

   /** Number of users in the channel.

   - Communication profile: The number of users in the channel.
   - Live broadcast profile:

      -  If the local user is an audience: The number of users in the channel = The number of hosts in the channel + 1.
      -  If the user is a host: The number of users in the channel = The number of hosts in the channel.
   */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      int64 UserCount;

   /** Application CPU usage (%).*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      float cpuAppUsage;

   /** System CPU usage (%). */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RtcStats" )
      float cpuTotalUsage;

   FRtcStats();
   FRtcStats( const agora::rtc::RtcStats& stats );

   FRtcStats& operator=( const agora::rtc::RtcStats& stats );

   operator agora::rtc::RtcStats();
};

/** Reasons for a user being offline. */
UENUM( BlueprintType )
enum EUSER_OFFLINE_REASON_TYPE
{
   /** -1: None*/
   USER_OFFLINE_NONE = -1,
   /** 0: The user quits the call. */
   USER_OFFLINE_QUIT = agora::rtc::USER_OFFLINE_QUIT,
   /** 1: The SDK times out and the user drops offline because no data packet is received within a certain period of time. If the user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user dropped offline. */
   USER_OFFLINE_DROPPED = agora::rtc::USER_OFFLINE_DROPPED,
   /** 2: (Live broadcast only.) The client role switched from the host to the audience. */
   USER_OFFLINE_BECOME_AUDIENCE = agora::rtc::USER_OFFLINE_BECOME_AUDIENCE,
};

UENUM( BlueprintType )
enum EENCRYPTION_MODE
{
   /** 0: aes-128-xts.
   (Default) 128-bit AES encryption, XTS mode.
   */
   ENCRYPTION_MODE_AES_128_XTC = 0,

   /** 1: aes-128-ecb.
   128-bit AES encryption, ECB mode.
   */
   ENCRYPTION_MODE_AES_128_ECB = 1,

   /** 2: aes-256-xts.
   256-bit AES encryption, XTS mode.
   */
   ENCRYPTION_MODE_AES_256_XTS = 2,
};

/** Channel profiles.*/
UENUM( BlueprintType )
enum ECHANNEL_PROFILE_TYPE
{
   /** 0: Communication.

    This is used in one-on-one calls or group calls, where all users in the channel can talk freely.
    */
   CHANNEL_PROFILE_COMMUNICATION = agora::rtc::CHANNEL_PROFILE_COMMUNICATION,
   /** 1: Live Broadcast.

    Host and audience roles that can be set by calling the \ref UIAgora::SetClientRole "setClientRole" method. The host sends and receives voice, while the audience receives voice only with the sending function disabled.
    */
   CHANNEL_PROFILE_LIVE_BROADCASTING = agora::rtc::CHANNEL_PROFILE_LIVE_BROADCASTING,
   /** 2: Gaming.

    @note This profile applies to the Agora Gaming SDK only.

    Any user in the channel can talk freely. This mode uses the codec with low-power consumption and low bitrate by default.
    */
   CHANNEL_PROFILE_GAME = agora::rtc::CHANNEL_PROFILE_GAME,
};

/** The IVideoFrameObserver class.*/
UENUM( BlueprintType )
enum EVIDEO_FRAME_TYPE
{
   /**
    * -1: NONE
    */
   FRAME_TYPE_NONE = -1,
   /**
    * 0: YUV420
    */
   FRAME_TYPE_YUV420 = agora::media::IVideoFrameObserver::FRAME_TYPE_YUV420,  // YUV 420 format
   /**
    * 1: YUV422
    */
   FRAME_TYPE_YUV422 = agora::media::IVideoFrameObserver::FRAME_TYPE_YUV422,  // YUV 422 format
   /**
    * 2: RGBA
    */
   FRAME_TYPE_RGBA = agora::media::IVideoFrameObserver::FRAME_TYPE_RGBA,    // RGBA format
};

UENUM( BlueprintType )
enum ECAMERA_DIRECTION
{
   /** The rear camera. */
   CAMERA_REAR = 0,
   /** The front camera. */
   CAMERA_FRONT = 1,
};

/** Audio session restriction. */
UENUM( BlueprintType )
enum EAUDIO_SESSION_OPERATION_RESTRICTION
{
   /** No restriction, the SDK has full control of the audio session operations. */
   AUDIO_SESSION_OPERATION_RESTRICTION_NONE = 0,
   /** The SDK does not change the audio session category. */
   AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY = 1,
   /** The SDK does not change any setting of the audio session (category, mode, categoryOptions). */
   AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION = 1 << 1,
   /** The SDK keeps the audio session active when leaving a channel. */
   AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION = 1 << 2,
   /** The SDK does not configure the audio session anymore. */
   AUDIO_SESSION_OPERATION_RESTRICTION_ALL = 1 << 7,
};

/** Content hints for screen sharing.*/
UENUM( BlueprintType )
enum EVIDEO_CONTENT_HINT
{
   /** (Default) No content hint.*/
   CONTENT_HINT_NONE = agora::rtc::CONTENT_HINT_NONE,
   /** Motion-intensive content. Choose this option if you prefer smoothness or when you are sharing a video clip, movie, or video game.
    */
   CONTENT_HINT_MOTION = agora::rtc::CONTENT_HINT_MOTION,
   /** Motionless content. Choose this option if you prefer sharpness or when you are sharing a picture, PowerPoint slide, or text.
    */
   CONTENT_HINT_DETAILS = agora::rtc::CONTENT_HINT_DETAILS
};

/** States of the last-mile network probe test. */
UENUM( BlueprintType )
enum ELASTMILE_PROBE_RESULT_STATE
{
   /** 1: The last-mile network probe test is complete. */
   LASTMILE_PROBE_RESULT_COMPLETE = agora::rtc::LASTMILE_PROBE_RESULT_COMPLETE,
   /** 2: The last-mile network probe test is incomplete and the bandwidth estimation is not available, probably due to limited test resources. */
   LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE = agora::rtc::LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE,
   /** 3: The last-mile network probe test is not carried out, probably due to poor network conditions. */
   LASTMILE_PROBE_RESULT_UNAVAILABLE = agora::rtc::LASTMILE_PROBE_RESULT_UNAVAILABLE
};

/** The uplink or downlink last-mile network probe test result. */
USTRUCT( BlueprintType )
struct FLastmileProbeOneWayResult
{
   GENERATED_BODY()
public:
   /** The packet loss rate (%). */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult" )
      int64 PacketLossRate;

   /** The network jitter (ms). */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult" )
      int64 Jitter;

   /* The estimated available bandwidth (Kbps). */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeOneWayResult" )
      int64 AvailableBandwidth;
};

/** The uplink and downlink last-mile network probe test result. */
USTRUCT( BlueprintType )
struct FLastmileProbeResult
{
   GENERATED_BODY()
public:

   /** The state of the probe test. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult" )
      TEnumAsByte < ELASTMILE_PROBE_RESULT_STATE > State;

   /** The uplink last-mile network probe test result. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult" )
      FLastmileProbeOneWayResult UplinkReport;

   /** The downlink last-mile network probe test result. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult" )
      FLastmileProbeOneWayResult DownlinkReport;

   /** The round-trip delay time (ms). */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LastmileProbeResult" )
      int64 Rtt;
};

/** Quality change of the local video in terms of target frame rate and target bit rate since last count.
  */
UENUM( BlueprintType )
enum EQUALITY_ADAPT_INDICATION
{
   /** The quality of the local video stays the same. */
   ADAPT_NONE = agora::rtc::ADAPT_NONE,
   /** The quality improves because the network bandwidth increases. */
   ADAPT_UP_BANDWIDTH = agora::rtc::ADAPT_UP_BANDWIDTH,
   /** The quality worsens because the network bandwidth decreases. */
   ADAPT_DOWN_BANDWIDTH = agora::rtc::ADAPT_DOWN_BANDWIDTH,
};

/** Video codec types */
UENUM( BlueprintType )
enum EVIDEO_CODEC_TYPE
{
   /** Standard VP8 */
   VIDEO_CODEC_VP8 = agora::rtc::VIDEO_CODEC_VP8,
   /** Standard H264 */
   VIDEO_CODEC_H264 = agora::rtc::VIDEO_CODEC_H264,
   /** Enhanced VP8 */
   VIDEO_CODEC_EVP = agora::rtc::VIDEO_CODEC_EVP,
   /** Enhanced H264 */
   VIDEO_CODEC_E264 = agora::rtc::VIDEO_CODEC_E264,
};

/** Statistics of the local video stream.*/
USTRUCT( BlueprintType )
struct FLocalVideoStats
{
   GENERATED_BODY()
public:

   /** Bitrate (Kbps) sent in the reported interval, which does not include
    * the bitrate of the retransmission video after packet loss.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int SentBitrate;

   /** Frame rate (fps) sent in the reported interval, which does not include
    * the frame rate of the retransmission video after packet loss.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int SentFrameRate;

   /** The encoder output frame rate (fps) of the local video.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int EncoderOutputFrameRate;

   /** The render output frame rate (fps) of the local video.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int RendererOutputFrameRate;

   /** The target bitrate (Kbps) of the current encoder. This value is estimated by the SDK based on the current network conditions.
     */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int TargetBitrate;

   /** The target frame rate (fps) of the current encoder.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int TargetFrameRate;

   /** Quality change of the local video in terms of target frame rate and
    * target bit rate in this reported interval. See #EQUALITY_ADAPT_INDICATION.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      TEnumAsByte< EQUALITY_ADAPT_INDICATION > QualityAdaptIndication;

   /** The encoding bitrate (Kbps), which does not include the bitrate of the
    * re-transmission video after packet loss.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int EncodedBitrate;

   /** The width of the encoding frame (px).*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int EncodedFrameWidth;

   /** The height of the encoding frame (px).*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int EncodedFrameHeight;

   /** The value of the sent frames, represented by an aggregate value.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      int EncodedFrameCount;

   /** The codec type of the local video:
    * - VIDEO_CODEC_VP8 = 1: VP8.
    * - VIDEO_CODEC_H264 = 2: (Default) H.264.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalVideoStats" )
      TEnumAsByte < EVIDEO_CODEC_TYPE > CodecType;
};

/** Remote video stream types. */
UENUM( BlueprintType )
enum EREMOTE_VIDEO_STREAM_TYPE
{
   /** 0: High-stream video. */
   REMOTE_VIDEO_STREAM_HIGH = agora::rtc::REMOTE_VIDEO_STREAM_HIGH,
   /** 1: Low-stream video. */
   REMOTE_VIDEO_STREAM_LOW = agora::rtc::REMOTE_VIDEO_STREAM_LOW,
};

USTRUCT( BlueprintType )
struct FRemoteVideoStats
{
   GENERATED_BODY()
public:
   /** User ID of the remote user sending the video streams.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int64 Uid;

   /** **DEPRECATED** Time delay (ms).*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int Delay;

   /** Width (pixels) of the video stream.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int Width;

   /** Height (pixels) of the video stream.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int Height;

   /** Bitrate (Kbps) received since the last count.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int ReceivedBitrate;

   /** The decoder output frame rate (fps) of the remote video.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int DecoderOutputFrameRate;

   /** The render output frame rate (fps) of the remote video.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int RendererOutputFrameRate;

   /** Packet loss rate (%) of the remote video stream after using the anti-packet-loss method.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int PacketLossRate;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      TEnumAsByte < EREMOTE_VIDEO_STREAM_TYPE> RxStreamType;

   /**
    The total freeze time (ms) of the remote video stream after the remote user joins the channel.
    In a video session where the frame rate is set to no less than 5 fps, video freeze occurs when
    the time interval between two adjacent renderable video frames is more than 500 ms.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int TotalFrozenTime;

   /**
    The total video freeze time as a percentage (%) of the total time when the video is available.
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteVideoStats" )
      int FrozenRate;
};

/** Audio statistics of the local user */
USTRUCT( BlueprintType )
struct FLocalAudioStats
{
   GENERATED_BODY()
public:

   /** The number of channels. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats" )
      int NumChannels;

   /** The sample rate (Hz). */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats" )
      int SentSampleRate;

   /** The average sending bitrate (Kbps).*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|LocalAudioStats" )
      int SentBitrate;
};

/** Audio statistics of a remote user */
USTRUCT( BlueprintType )
struct FRemoteAudioStats
{
   GENERATED_BODY()
public:

   /** User ID of the remote user sending the audio streams.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int64 Uid;

   /** Audio quality received by the user: #QUALITY_TYPE.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int Quality;

   /** Network delay (ms) from the sender to the receiver.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int NetworkTransportDelay;

   /** Network delay (ms) from the receiver to the jitter buffer.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int JitterBufferDelay;

   /** The audio frame loss rate in the reported interval.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int AudioLossRate;

   /** The number of channels.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int NumChannels;

   /** The sample rate (Hz) of the received audio stream in the reported interval.*/
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int ReceivedSampleRate;

   /** The average bitrate (Kbps) of the received audio stream in the
    * reported interval. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int ReceivedBitrate;

   /** The total freeze time (ms) of the remote audio stream after the remote user joins the channel. In a session, audio freeze occurs when the audio frame loss rate reaches 4%.
    * Agora uses 2 seconds as an audio piece unit to calculate the audio freeze time. The total audio freeze time = The audio freeze number &times; 2 seconds
    */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int TotalFrozenTime;

   /** The total audio freeze time as a percentage (%) of the total time when the audio is available. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Agora|RemoteAudioStats" )
      int FrozenRate;
};

/** Local audio state error codes.
 */
UENUM( BlueprintType )
enum ELOCAL_AUDIO_STREAM_ERROR
{
   /** 0: The local audio is normal.*/
   LOCAL_AUDIO_STREAM_ERROR_OK = agora::rtc::LOCAL_AUDIO_STREAM_ERROR_OK,

   /** 1: No specified reason for the local audio failure.*/
   LOCAL_AUDIO_STREAM_ERROR_FAILURE = agora::rtc::LOCAL_AUDIO_STREAM_ERROR_FAILURE,

   /** 2: No permission to use the local audio device.*/
   LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION = agora::rtc::LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION,
   
   /** 3: The microphone is in use.*/
   LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY = agora::rtc::LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY,
   
   /** 4: The local audio recording fails. Check whether the recording device
    * is working properly.
    */
   LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE = agora::rtc::LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE,
   
   /** 5: The local audio encoding fails.*/
   LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = agora::rtc::LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE
};

/** Local audio state types.*/
UENUM( BlueprintType )
enum ELOCAL_AUDIO_STREAM_STATE
{
   /** 0: The local audio is in the initial state.*/
   LOCAL_AUDIO_STREAM_STATE_STOPPED = agora::rtc::LOCAL_AUDIO_STREAM_STATE_STOPPED,

   /** 1: The recording device starts successfully.*/
   LOCAL_AUDIO_STREAM_STATE_RECORDING = agora::rtc::LOCAL_AUDIO_STREAM_STATE_RECORDING,

   /** 2: The first audio frame encodes successfully.*/
   LOCAL_AUDIO_STREAM_STATE_ENCODING = agora::rtc::LOCAL_AUDIO_STREAM_STATE_ENCODING,

   /** 3: The local audio fails to start.*/
   LOCAL_AUDIO_STREAM_STATE_FAILED = agora::rtc::LOCAL_AUDIO_STREAM_STATE_FAILED
};

/** Remote audio states.*/
UENUM( BlueprintType )
enum EREMOTE_AUDIO_STATE
{
   /** 0: The remote audio is in the default state, probably due to
    * #REMOTE_AUDIO_REASON_LOCAL_MUTED (3),
    * #REMOTE_AUDIO_REASON_REMOTE_MUTED (5), or
    * #REMOTE_AUDIO_REASON_REMOTE_OFFLINE (7).
    */
   REMOTE_AUDIO_STATE_STOPPED = agora::rtc::REMOTE_AUDIO_STATE_STOPPED,  // Default state, audio is started or remote user disabled/muted audio stream
   /** 1: The first remote audio packet is received.
    */
   REMOTE_AUDIO_STATE_STARTING = agora::rtc::REMOTE_AUDIO_STATE_STARTING,  // The first audio frame packet has been received
   /** 2: The remote audio stream is decoded and plays normally, probably
    * due to #REMOTE_AUDIO_REASON_NETWORK_RECOVERY (2),
    * #REMOTE_AUDIO_REASON_LOCAL_UNMUTED (4), or
    * #REMOTE_AUDIO_REASON_REMOTE_UNMUTED (6).
    */
   REMOTE_AUDIO_STATE_DECODING = agora::rtc::REMOTE_AUDIO_STATE_DECODING,  // The first remote audio frame has been decoded or fronzen state ends
   /** 3: The remote audio is frozen, probably due to
    * #REMOTE_AUDIO_REASON_NETWORK_CONGESTION (1).
    */
   REMOTE_AUDIO_STATE_FROZEN = agora::rtc::REMOTE_AUDIO_STATE_FROZEN,    // Remote audio is frozen, probably due to network issue
   /** 4: The remote audio fails to start, probably due to
    * #REMOTE_AUDIO_REASON_INTERNAL (0).
    */
   REMOTE_AUDIO_STATE_FAILED = agora::rtc::REMOTE_AUDIO_STATE_FAILED,    // Remote audio play failed
};

/** Remote audio state reasons.*/
UENUM( BlueprintType )
enum EREMOTE_AUDIO_STATE_REASON
{
   /** 0: Internal reasons.*/
   REMOTE_AUDIO_REASON_INTERNAL = agora::rtc::REMOTE_AUDIO_REASON_INTERNAL,

   /** 1: Network congestion.*/
   REMOTE_AUDIO_REASON_NETWORK_CONGESTION = agora::rtc::REMOTE_AUDIO_REASON_NETWORK_CONGESTION,

   /** 2: Network recovery.*/
   REMOTE_AUDIO_REASON_NETWORK_RECOVERY = agora::rtc::REMOTE_AUDIO_REASON_NETWORK_RECOVERY,

   /** 3: The local user stops receiving the remote audio stream or
    * disables the audio module.
    */
   REMOTE_AUDIO_REASON_LOCAL_MUTED = agora::rtc::REMOTE_AUDIO_REASON_LOCAL_MUTED,

   /** 4: The local user resumes receiving the remote audio stream or
    * enables the audio module.
    */
   REMOTE_AUDIO_REASON_LOCAL_UNMUTED = agora::rtc::REMOTE_AUDIO_REASON_LOCAL_UNMUTED,

   /** 5: The remote user stops sending the audio stream or disables the
    * audio module.
    */
   REMOTE_AUDIO_REASON_REMOTE_MUTED = agora::rtc::REMOTE_AUDIO_REASON_REMOTE_MUTED,

   /** 6: The remote user resumes sending the audio stream or enables the
    * audio module.
    */
   REMOTE_AUDIO_REASON_REMOTE_UNMUTED = agora::rtc::REMOTE_AUDIO_REASON_REMOTE_UNMUTED,

   /** 7: The remote user leaves the channel.*/
   REMOTE_AUDIO_REASON_REMOTE_OFFLINE = agora::rtc::REMOTE_AUDIO_REASON_REMOTE_OFFLINE,
};

/** Media device types.*/
UENUM( BlueprintType )
enum EMEDIA_DEVICE_TYPE
{
   /** -1: Unknown device type.*/
   UNKNOWN_AUDIO_DEVICE = agora::rtc::UNKNOWN_AUDIO_DEVICE,

   /** 0: Audio playback device.*/
   AUDIO_PLAYOUT_DEVICE = agora::rtc::AUDIO_PLAYOUT_DEVICE,

   /** 1: Audio recording device.*/
   AUDIO_RECORDING_DEVICE = agora::rtc::AUDIO_RECORDING_DEVICE,

   /** 2: Video renderer.*/
   VIDEO_RENDER_DEVICE = agora::rtc::VIDEO_RENDER_DEVICE,

   /** 3: Video capturer.*/
   VIDEO_CAPTURE_DEVICE = agora::rtc::VIDEO_CAPTURE_DEVICE,

   /** 4: Application audio playback device.*/
   AUDIO_APPLICATION_PLAYOUT_DEVICE = agora::rtc::AUDIO_APPLICATION_PLAYOUT_DEVICE,
};

/** The states of the local user's audio mixing file.*/
UENUM( BlueprintType )
enum EAUDIO_MIXING_STATE_TYPE
{
   /** 710: The audio mixing file is playing.*/
   AUDIO_MIXING_STATE_PLAYING = agora::rtc::AUDIO_MIXING_STATE_PLAYING,

   /** 711: The audio mixing file pauses playing.*/
   AUDIO_MIXING_STATE_PAUSED = agora::rtc::AUDIO_MIXING_STATE_PAUSED,

   /** 713: The audio mixing file stops playing.*/
   AUDIO_MIXING_STATE_STOPPED = agora::rtc::AUDIO_MIXING_STATE_STOPPED,

   /** 714: An exception occurs when playing the audio mixing file. See #EAUDIO_MIXING_ERROR_TYPE.*/
   AUDIO_MIXING_STATE_FAILED = agora::rtc::AUDIO_MIXING_STATE_FAILED,
};

/** The error codes of the local user's audio mixing file.*/
UENUM( BlueprintType )
enum EAUDIO_MIXING_ERROR_TYPE
{
   /** 701: The SDK cannot open the audio mixing file.*/
   AUDIO_MIXING_ERROR_CAN_NOT_OPEN = agora::rtc::AUDIO_MIXING_ERROR_CAN_NOT_OPEN,

   /** 702: The SDK opens the audio mixing file too frequently.*/
   AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL = agora::rtc::AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL,

   /** 703: The audio mixing file playback is interrupted.*/
   AUDIO_MIXING_ERROR_INTERRUPTED_EOF = agora::rtc::AUDIO_MIXING_ERROR_INTERRUPTED_EOF,

   /** 0: The SDK can open the audio mixing file.*/
   AUDIO_MIXING_ERROR_OK = agora::rtc::AUDIO_MIXING_ERROR_OK,
};

/** Local video state types.*/
UENUM( BlueprintType )
enum ELOCAL_VIDEO_STREAM_STATE
{
   /** Initial state */
   LOCAL_VIDEO_STREAM_STATE_STOPPED = agora::rtc::LOCAL_VIDEO_STREAM_STATE_STOPPED,

   /** The capturer starts successfully. */
   LOCAL_VIDEO_STREAM_STATE_CAPTURING = agora::rtc::LOCAL_VIDEO_STREAM_STATE_CAPTURING,

   /** The first video frame is successfully encoded. */
   LOCAL_VIDEO_STREAM_STATE_ENCODING = agora::rtc::LOCAL_VIDEO_STREAM_STATE_ENCODING,

   /** The local video fails to start. */
   LOCAL_VIDEO_STREAM_STATE_FAILED = agora::rtc::LOCAL_VIDEO_STREAM_STATE_FAILED
};

/** Local video state error codes.*/
UENUM( BlueprintType )
enum ELOCAL_VIDEO_STREAM_ERROR
{
   /** The local video is normal. */
   LOCAL_VIDEO_STREAM_ERROR_OK = agora::rtc::LOCAL_VIDEO_STREAM_ERROR_OK,

   /** No specified reason for the local video failure. */
   LOCAL_VIDEO_STREAM_ERROR_FAILURE = agora::rtc::LOCAL_VIDEO_STREAM_ERROR_FAILURE,

   /** No permission to use the local video device. */
   LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION = agora::rtc::LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION,

   /** The local video capturer is in use. */
   LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY = agora::rtc::LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY,

   /** The local video capture fails. Check whether the capturer is working properly. */
   LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = agora::rtc::LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE,

   /** The local video encoding fails. */
   LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = agora::rtc::LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE
};

/** The state of the remote video. */
UENUM( BlueprintType )
enum EREMOTE_VIDEO_STATE
{
   /** 0: The remote video is in the default state, probably due to #REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED (3), #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5), or #REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE (7).
    */
   REMOTE_VIDEO_STATE_STOPPED = agora::rtc::REMOTE_VIDEO_STATE_STOPPED,

   /** 1: The first remote video packet is received.
    */
   REMOTE_VIDEO_STATE_STARTING = agora::rtc::REMOTE_VIDEO_STATE_STARTING,

   /** 2: The remote video stream is decoded and plays normally, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY (2), #REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED (4), #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6), or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY (9).
    */
   REMOTE_VIDEO_STATE_DECODING = agora::rtc::REMOTE_VIDEO_STATE_DECODING,

   /** 3: The remote video is frozen, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION (1) or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK (8).
    */
   REMOTE_VIDEO_STATE_FROZEN = agora::rtc::REMOTE_VIDEO_STATE_FROZEN,

   /** 4: The remote video fails to start, probably due to #EREMOTE_VIDEO_STATE_REASON_INTERNAL (0).
    */
   REMOTE_VIDEO_STATE_FAILED = agora::rtc::REMOTE_VIDEO_STATE_FAILED
};

/** The reason of the remote video state change. */
UENUM( BlueprintType )
enum EREMOTE_VIDEO_STATE_REASON
{
   /** 0: Internal reasons.*/
   REMOTE_VIDEO_STATE_REASON_INTERNAL = agora::rtc::REMOTE_VIDEO_STATE_REASON_INTERNAL,

   /** 1: Network congestion.*/
   REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = agora::rtc::REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION,

   /** 2: Network recovery.*/
   REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = agora::rtc::REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY,

   /** 3: The local user stops receiving the remote video stream or disables the video module.*/
   REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = agora::rtc::REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED,

   /** 4: The local user resumes receiving the remote video stream or enables the video module.*/
   REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = agora::rtc::REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED,

   /** 5: The remote user stops sending the video stream or disables the video module.*/
   REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = agora::rtc::REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED,

   /** 6: The remote user resumes sending the video stream or enables the video module.*/
   REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = agora::rtc::REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED,

   /** 7: The remote user leaves the channel.*/
   REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = agora::rtc::REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE,

   /** 8: The remote media stream falls back to the audio-only stream due to poor network conditions.*/
   REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = agora::rtc::REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK,

   /** 9: The remote media stream switches back to the video stream after the network conditions improve.*/
   REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = agora::rtc::REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY
};

/** The state code in ECHANNEL_MEDIA_RELAY_STATE. */
UENUM( BlueprintType )
enum ECHANNEL_MEDIA_RELAY_STATE
{
   /** 0: The SDK is initializing.*/
   RELAY_STATE_IDLE = agora::rtc::RELAY_STATE_IDLE,

   /** 1: The SDK tries to relay the media stream to the destination channel.*/
   RELAY_STATE_CONNECTING = agora::rtc::RELAY_STATE_CONNECTING,

   /** 2: The SDK successfully relays the media stream to the destination channel.*/
   RELAY_STATE_RUNNING = agora::rtc::RELAY_STATE_RUNNING,

   /** 3: A failure occurs. See the details in code.*/
   RELAY_STATE_FAILURE = agora::rtc::RELAY_STATE_FAILURE,
};

/** The error code in CHANNEL_MEDIA_RELAY_ERROR. */
UENUM( BlueprintType )
enum ECHANNEL_MEDIA_RELAY_ERROR
{
   /** 0: The state is normal.*/
   RELAY_OK = agora::rtc::RELAY_OK,

   /** 1: An error occurs in the server response.*/
   RELAY_ERROR_SERVER_ERROR_RESPONSE = agora::rtc::RELAY_ERROR_SERVER_ERROR_RESPONSE,

   /** 2: No server response. You can call the
    * \ref UIAgora::LeaveChannel "LeaveChannel" method to
    * leave the channel.
    */
   RELAY_ERROR_SERVER_NO_RESPONSE = agora::rtc::RELAY_ERROR_SERVER_NO_RESPONSE,

   /** 3: The SDK fails to access the service, probably due to limited resources of the server.*/
   RELAY_ERROR_NO_RESOURCE_AVAILABLE = agora::rtc::RELAY_ERROR_NO_RESOURCE_AVAILABLE,

   /** 4: The server fails to join the source channel.*/
   RELAY_ERROR_FAILED_JOIN_SRC = agora::rtc::RELAY_ERROR_FAILED_JOIN_SRC,

   /** 5: The server fails to join the destination channel.*/
   RELAY_ERROR_FAILED_JOIN_DEST = agora::rtc::RELAY_ERROR_FAILED_JOIN_DEST,

   /** 6: The server fails to receive the data from the source channel.*/
   RELAY_ERROR_FAILED_PACKET_RECEIVED_FROM_SRC = agora::rtc::RELAY_ERROR_FAILED_PACKET_RECEIVED_FROM_SRC,

   /** 7: The source channel fails to transmit data.*/
   RELAY_ERROR_FAILED_PACKET_SENT_TO_DEST = agora::rtc::RELAY_ERROR_FAILED_PACKET_SENT_TO_DEST,

   /** 8: The SDK disconnects from the server due to poor network
    * connections. You can call the \ref UIAgora::LeaveChannel
    * "LeaveChannel" method to leave the channel.
    */
   RELAY_ERROR_SERVER_CONNECTION_LOST = agora::rtc::RELAY_ERROR_SERVER_CONNECTION_LOST,

   /** 9: An internal error occurs in the server.*/
   RELAY_ERROR_INTERNAL_ERROR = agora::rtc::RELAY_ERROR_INTERNAL_ERROR,

   /** 10: The token of the source channel has expired.*/
   RELAY_ERROR_SRC_TOKEN_EXPIRED = agora::rtc::RELAY_ERROR_SRC_TOKEN_EXPIRED,

   /** 11: The token of the destination channel has expired.*/
   RELAY_ERROR_DEST_TOKEN_EXPIRED = agora::rtc::RELAY_ERROR_DEST_TOKEN_EXPIRED,
};

/** The event code in CHANNEL_MEDIA_RELAY_EVENT. */
UENUM( BlueprintType )
enum ECHANNEL_MEDIA_RELAY_EVENT
{
   /** 0: The user disconnects from the server due to poor network connections.*/
   RELAY_EVENT_NETWORK_DISCONNECTED = agora::rtc::RELAY_EVENT_NETWORK_DISCONNECTED,

   /** 1: The network reconnects. */
   RELAY_EVENT_NETWORK_CONNECTED = agora::rtc::RELAY_EVENT_NETWORK_CONNECTED,

   /** 2: The user joins the source channel.*/
   RELAY_EVENT_PACKET_JOINED_SRC_CHANNEL = agora::rtc::RELAY_EVENT_PACKET_JOINED_SRC_CHANNEL,

   /** 3: The user joins the destination channel.*/
   RELAY_EVENT_PACKET_JOINED_DEST_CHANNEL = agora::rtc::RELAY_EVENT_PACKET_JOINED_DEST_CHANNEL,

   /** 4: The SDK starts relaying the media stream to the destination channel.*/
   RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL = agora::rtc::RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL,

   /** 5: The server receives the video stream from the source channel.*/
   RELAY_EVENT_PACKET_RECEIVED_VIDEO_FROM_SRC = agora::rtc::RELAY_EVENT_PACKET_RECEIVED_VIDEO_FROM_SRC,

   /** 6: The server receives the audio stream from the source channel.*/
   RELAY_EVENT_PACKET_RECEIVED_AUDIO_FROM_SRC = agora::rtc::RELAY_EVENT_PACKET_RECEIVED_AUDIO_FROM_SRC,

   /** 7: The destination channel is updated.*/
   RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL = agora::rtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL,
   /** 8: The destination channel update fails due to internal reasons.*/

   RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_REFUSED = agora::rtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_REFUSED,
   
   /** 9: The destination channel does not change, which means that the
    * destination channel fails to be updated.
    */
   RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_NOT_CHANGE = agora::rtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_NOT_CHANGE,
   
   /** 10: The destination channel name is NULL.*/
   RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL = agora::rtc::RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL,
   
   /** 11: The video profile is sent to the server.*/
   RELAY_EVENT_VIDEO_PROFILE_UPDATE = agora::rtc::RELAY_EVENT_VIDEO_PROFILE_UPDATE,
};

/** States of the RTMP streaming.*/
UENUM( BlueprintType )
enum ERTMP_STREAM_PUBLISH_STATE
{
   /** The RTMP streaming has not started or has ended. This state is also triggered after you remove an RTMP address from the CDN by calling removePublishStreamUrl.
    */
   RTMP_STREAM_PUBLISH_STATE_IDLE = agora::rtc::RTMP_STREAM_PUBLISH_STATE_IDLE,
   
   /** The SDK is connecting to Agora's streaming server and the RTMP server. This state is triggered after you call the \ref UIAgora::AddPublishStreamUrl "AddPublishStreamUrl" method.
    */
   RTMP_STREAM_PUBLISH_STATE_CONNECTING = agora::rtc::RTMP_STREAM_PUBLISH_STATE_CONNECTING,
   
   /** The RTMP streaming publishes. The SDK successfully publishes the RTMP streaming and returns this state.
    */
   RTMP_STREAM_PUBLISH_STATE_RUNNING = agora::rtc::RTMP_STREAM_PUBLISH_STATE_RUNNING,
   
   /** The RTMP streaming is recovering. When exceptions occur to the CDN, or the streaming is interrupted, the SDK tries to resume RTMP streaming and returns this state.

    - If the SDK successfully resumes the streaming, #RTMP_STREAM_PUBLISH_STATE_RUNNING (2) returns.
    - If the streaming does not resume within 60 seconds or server errors occur, #RTMP_STREAM_PUBLISH_STATE_FAILURE (4) returns. You can also reconnect to the server by calling the \ref UIAgora::RemovePublishStreamUrl "RemovePublishStreamUrl" and \ref UIAgora::AddPublishStreamUrl "AddPublishStreamUrl" methods.
    */
   RTMP_STREAM_PUBLISH_STATE_RECOVERING = agora::rtc::RTMP_STREAM_PUBLISH_STATE_RECOVERING,
   
   /** The RTMP streaming fails. See the errCode parameter for the detailed error information. You can also call the \ref UIAgora::AddPublishStreamUrl "AddPublishStreamUrl" method to publish the RTMP streaming again.
    */
   RTMP_STREAM_PUBLISH_STATE_FAILURE = agora::rtc::RTMP_STREAM_PUBLISH_STATE_FAILURE,
};

/** Error codes of the RTMP streaming.*/
UENUM( BlueprintType )
enum ERTMP_STREAM_PUBLISH_ERROR
{
   /** The RTMP streaming publishes successfully. */
   RTMP_STREAM_PUBLISH_ERROR_OK = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_OK,
   
   /** Invalid argument used. If, for example, you do not call the \ref UIAgora::SetLiveTranscoding "SetLiveTranscoding" method to configure the LiveTranscoding parameters before calling the addPublishStreamUrl method, the SDK returns this error. Check whether you set the parameters in the *SetLiveTranscoding* method properly. */
   RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT,
   
   /** The RTMP streaming is encrypted and cannot be published. */
   RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED,
   
   /** Timeout for the RTMP streaming. Call the \ref UIAgora::AddPublishStreamUrl "AddPublishStreamUrl" method to publish the streaming again. */
   RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT,
   
   /** An error occurs in Agora's streaming server. Call the AddPublishStreamUrl method to publish the streaming again. */
   RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR,
   
   /** An error occurs in the RTMP server. */
   RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR,
   
   /** The RTMP streaming publishes too frequently. */
   RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN,
   
   /** The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
   RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT,
   
   /** The host manipulates other hosts' URLs. Check your app logic. */
   RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED,
   
   /** Agora's server fails to find the RTMP streaming. */
   RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND,
   
   /** The format of the RTMP streaming URL is not supported. Check whether the URL format is correct. */
   RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED = agora::rtc::RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED,
};

/** Audio output routing. */
UENUM( BlueprintType )
enum EAUDIO_ROUTE_TYPE
{
   /** Default.*/
   AUDIO_ROUTE_DEFAULT = agora::rtc::AUDIO_ROUTE_DEFAULT,
   
   /** Headset.*/
   AUDIO_ROUTE_HEADSET = agora::rtc::AUDIO_ROUTE_HEADSET,
   
   /** Earpiece.*/
   AUDIO_ROUTE_EARPIECE = agora::rtc::AUDIO_ROUTE_EARPIECE,
   
   /** Headset with no microphone.*/
   AUDIO_ROUTE_HEADSET_NO_MIC = agora::rtc::AUDIO_ROUTE_HEADSET_NO_MIC,
   
   /** Speakerphone.*/
   AUDIO_ROUTE_SPEAKERPHONE = agora::rtc::AUDIO_ROUTE_SPEAKERPHONE,
   
   /** Loudspeaker.*/
   AUDIO_ROUTE_LOUDSPEAKER = agora::rtc::AUDIO_ROUTE_LOUDSPEAKER,
   
   /** Bluetooth headset.*/
   AUDIO_ROUTE_BLUETOOTH = agora::rtc::AUDIO_ROUTE_BLUETOOTH
};

/** Connection states.*/
UENUM( BlueprintType )
enum ECONNECTION_STATE_TYPE
{
   /** 1: The SDK is disconnected from Agora's edge server.

    - This is the initial state before calling the \ref UIAgora::JoinChannel "JoinChannel" method.
    - The SDK also enters this state when the application calls the \ref UIAgora::LeaveChannel "LeaveChannel" method.
    */
   CONNECTION_STATE_DISCONNECTED = agora::rtc::CONNECTION_STATE_DISCONNECTED,
   
   /** 2: The SDK is connecting to Agora's edge server.

    - When the application calls the \ref UIAgora::JoinChannel "JoinChannel" method, the SDK starts to establish a connection to the specified channel, triggers the \ref UIAgora::OnConnectionStateChangedDelegate "OnConnectionStateChanged" callback, and switches to the #CONNECTION_STATE_CONNECTING state.
    - When the SDK successfully joins the channel, it triggers the \ref UIAgora::OnConnectionStateChangedDelegate "OnConnectionStateChanged" callback and switches to the #CONNECTION_STATE_CONNECTED state.
    - After the SDK joins the channel and when it finishes initializing the media engine, the SDK triggers the \ref UIAgora::OnJoinChannelSuccessDelegate "OnJoinChannelSuccess" callback.
    */
   CONNECTION_STATE_CONNECTING = agora::rtc::CONNECTION_STATE_CONNECTING,

   /** 3: The SDK is connected to Agora's edge server and has joined a channel. You can now publish or subscribe to a media stream in the channel.

    If the connection to the channel is lost because, for example, if the network is down or switched, the SDK automatically tries to reconnect and triggers:
    - The \ref UIAgora::OnConnectionInterruptedDelegate "OnConnectionInterrupted" callback (deprecated).
    - The \ref UIAgora::OnConnectionStateChangedDelegate "OnConnectionStateChanged" callback and switches to the #CONNECTION_STATE_RECONNECTING state.
    */
   CONNECTION_STATE_CONNECTED = agora::rtc::CONNECTION_STATE_CONNECTED,

   /** 4: The SDK keeps rejoining the channel after being disconnected from a joined channel because of network issues.

    - If the SDK cannot rejoin the channel within 10 seconds after being disconnected from Agora's edge server, the SDK triggers the \ref UIAgora::OnConnectionLostDelegate "OnConnectionLost" callback, stays in the #CONNECTION_STATE_RECONNECTING state, and keeps rejoining the channel.
    - If the SDK fails to rejoin the channel 20 minutes after being disconnected from Agora's edge server, the SDK triggers the \ref UIAgora::OnConnectionStateChangedDelegate "OnConnectionStateChanged" callback, switches to the #CONNECTION_STATE_FAILED state, and stops rejoining the channel.
    */
   CONNECTION_STATE_RECONNECTING = agora::rtc::CONNECTION_STATE_RECONNECTING,

   /** 5: The SDK fails to connect to Agora's edge server or join the channel.

    You must call the \ref UIAgora::LeaveChannel "LeaveChannel" method to leave this state, and call the \ref UIAgora::JoinChannel "JoinChannel" method again to rejoin the channel.

    If the SDK is banned from joining the channel by Agora's edge server (through the RESTful API), the SDK triggers the \ref UIAgora::OnConnectionBannedDelegate "OnConnectionBanned" (deprecated) and \ref UIAgora::OnConnectionStateChangedDelegate "OnConnectionStateChanged" callbacks.
    */
   CONNECTION_STATE_FAILED = agora::rtc::CONNECTION_STATE_FAILED,
};

/** Reasons for a connection state change. */
UENUM( BlueprintType )
enum ECONNECTION_CHANGED_REASON_TYPE
{
   /** 0: The SDK is connecting to Agora's edge server. */
   CONNECTION_CHANGED_CONNECTING = agora::rtc::CONNECTION_CHANGED_CONNECTING,

   /** 1: The SDK has joined the channel successfully. */
   CONNECTION_CHANGED_JOIN_SUCCESS = agora::rtc::CONNECTION_CHANGED_JOIN_SUCCESS,

   /** 2: The connection between the SDK and Agora's edge server is interrupted. */
   CONNECTION_CHANGED_INTERRUPTED = agora::rtc::CONNECTION_CHANGED_INTERRUPTED,

   /** 3: The connection between the SDK and Agora's edge server is banned by Agora's edge server. */
   CONNECTION_CHANGED_BANNED_BY_SERVER = agora::rtc::CONNECTION_CHANGED_BANNED_BY_SERVER,

   /** 4: The SDK fails to join the channel for more than 20 minutes and stops reconnecting to the channel. */
   CONNECTION_CHANGED_JOIN_FAILED = agora::rtc::CONNECTION_CHANGED_JOIN_FAILED,

   /** 5: The SDK has left the channel. */
   CONNECTION_CHANGED_LEAVE_CHANNEL = agora::rtc::CONNECTION_CHANGED_LEAVE_CHANNEL,

   /** 6: The connection failed since Appid is not valid. */
   CONNECTION_CHANGED_INVALID_APP_ID = agora::rtc::CONNECTION_CHANGED_INVALID_APP_ID,

   /** 7: The connection failed since channel name is not valid. */
   CONNECTION_CHANGED_INVALID_CHANNEL_NAME = agora::rtc::CONNECTION_CHANGED_INVALID_CHANNEL_NAME,

   /** 8: The connection failed since token is not valid, possibly because:

    - The App Certificate for the project is enabled in Dashboard, but you do not use Token when joining the channel. If you enable the App Certificate, you must use a token to join the channel.
    - The uid that you specify in the \ref UIAgora::JoinChannel "JoinChannel" method is different from the uid that you pass for generating the token.
    */
   CONNECTION_CHANGED_INVALID_TOKEN = agora::rtc::CONNECTION_CHANGED_INVALID_TOKEN,

   /** 9: The connection failed since token is expired. */
   CONNECTION_CHANGED_TOKEN_EXPIRED = agora::rtc::CONNECTION_CHANGED_TOKEN_EXPIRED,

   /** 10: The connection is rejected by server. */
   CONNECTION_CHANGED_REJECTED_BY_SERVER = agora::rtc::CONNECTION_CHANGED_REJECTED_BY_SERVER,

   /** 11: The connection changed to reconnecting since SDK has set a proxy server. */
   CONNECTION_CHANGED_SETTING_PROXY_SERVER = agora::rtc::CONNECTION_CHANGED_SETTING_PROXY_SERVER,

   /** 12: When SDK is in connection failed, the renew token operation will make it connecting. */
   CONNECTION_CHANGED_RENEW_TOKEN = agora::rtc::CONNECTION_CHANGED_RENEW_TOKEN,

   /** 13: The IP Address of SDK client has changed. i.e., Network type or IP/Port changed by network operator might change client IP address. */
   CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED = agora::rtc::CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED,
   
   /** 14: Timeout for the keep-alive of the connection between the SDK and Agora's edge server. The connection state changes to CONNECTION_STATE_RECONNECTING(4). */
   CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT = agora::rtc::CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT,
};

/** Network type. */
UENUM( BlueprintType )
enum ENETWORK_TYPE
{
   /** -1: The network type is unknown. */
   NETWORK_TYPE_UNKNOWN = agora::rtc::NETWORK_TYPE_UNKNOWN,

   /** 0: The SDK disconnects from the network. */
   NETWORK_TYPE_DISCONNECTED = agora::rtc::NETWORK_TYPE_DISCONNECTED,

   /** 1: The network type is LAN. */
   NETWORK_TYPE_LAN = agora::rtc::NETWORK_TYPE_LAN,

   /** 2: The network type is Wi-Fi(including hotspots). */
   NETWORK_TYPE_WIFI = agora::rtc::NETWORK_TYPE_WIFI,

   /** 3: The network type is mobile 2G. */
   NETWORK_TYPE_MOBILE_2G = agora::rtc::NETWORK_TYPE_MOBILE_2G,

   /** 4: The network type is mobile 3G. */
   NETWORK_TYPE_MOBILE_3G = agora::rtc::NETWORK_TYPE_MOBILE_3G,

   /** 5: The network type is mobile 4G. */
   NETWORK_TYPE_MOBILE_4G = agora::rtc::NETWORK_TYPE_MOBILE_4G,
};

EVIDEO_FRAME_TYPE convert( agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE frameType );
agora::rtc::CHANNEL_PROFILE_TYPE convert( ECHANNEL_PROFILE_TYPE profileType );
const char* convert( EENCRYPTION_MODE encryptionMode );
EUSER_OFFLINE_REASON_TYPE convert( agora::rtc::USER_OFFLINE_REASON_TYPE reasonType );
agora::rtc::VideoEncoderConfiguration convert( const FVideoEncoderConfiguration& configuration );
agora::rtc::FRAME_RATE convert( EFRAME_RATE frameRate );
agora::rtc::ORIENTATION_MODE convert( EORIENTATION_MODE orientationMode );
agora::rtc::DEGRADATION_PREFERENCE convert( EDEGRADATION_PREFERENCE degradationPreference );
agora::rtc::CAPTURER_OUTPUT_PREFERENCE convert( ECAPTURER_OUTPUT_PREFERENCE capturerOutputPreference );
agora::rtc::CameraCapturerConfiguration convert( const FCameraCapturerConfiguration& configuration );
agora::rtc::AUDIO_PROFILE_TYPE convert( EAUDIO_PROFILE_TYPE audioProfileType );
agora::rtc::AUDIO_SCENARIO_TYPE convert( EAUDIO_SCENARIO_TYPE audioScenarioType );
agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY convert( EAUDIO_EQUALIZATION_BAND_FREQUENCY audioEqualizationBandFrequency );
agora::rtc::AUDIO_REVERB_TYPE convert( EAUDIO_REVERB_TYPE audioReverbType );
agora::rtc::AUDIO_REVERB_PRESET convert( EAUDIO_REVERB_PRESET audioReverbPreset );
ECLIENT_ROLE_TYPE convert( agora::rtc::CLIENT_ROLE_TYPE clientRoleType );
agora::rtc::CLIENT_ROLE_TYPE convert( ECLIENT_ROLE_TYPE clientRoleType );
agora::rtc::PRIORITY_TYPE convert( EPRIORITY_TYPE priorityType );
agora::rtc::RENDER_MODE_TYPE convert( ERENDER_MODE_TYPE renderModeType );
agora::rtc::REMOTE_VIDEO_STREAM_TYPE convert( EREMOTE_VIDEO_STREAM_TYPE  remoteVideoStreamType );
agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE convert( ERAW_AUDIO_FRAME_OP_MODE_TYPE rawAudioFrameOpModeType );
agora::rtc::STREAM_FALLBACK_OPTIONS convert( ESTREAM_FALLBACK_OPTIONS streamFallbackOptions );
agora::rtc::VOICE_CHANGER_PRESET convert( EVOICE_CHANGER_PRESET voiceChangerPreset );
agora::rtc::VIDEO_MIRROR_MODE_TYPE convert( EVIDEO_MIRROR_MODE_TYPE videoMirrorModeType );
agora::rtc::AUDIO_RECORDING_QUALITY_TYPE convert( EAUDIO_RECORDING_QUALITY_TYPE audioRecordingQualityType );
ECONNECTION_STATE_TYPE convert( agora::rtc::CONNECTION_STATE_TYPE connectionStateType );
agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LEVEL convert( ELIGHTENING_CONTRAST_LEVEL lighteningContrastLevel );
agora::rtc::BeautyOptions convert( const FBeautyOptions& beautyOptions );
agora::rtc::ChannelMediaInfo convert( const FChannelMediaInfo& channelMediaInfo );
agora::rtc::AUDIO_SAMPLE_RATE_TYPE convert( EAUDIO_SAMPLE_RATE_TYPE audioSampleRateType );
agora::rtc::InjectStreamConfig convert( const FInjectStreamConfig& injectStreamConfig );
agora::rtc::LastmileProbeConfig convert( const FLastmileProbeConfig& lastmileProbeConfig );
agora::rtc::VIDEO_CODEC_PROFILE_TYPE convert( EVIDEO_CODEC_PROFILE_TYPE videoCodecProfileType );
agora::rtc::AUDIO_CODEC_PROFILE_TYPE convert( EAUDIO_CODEC_PROFILE_TYPE audioCodecProfileType );
agora::rtc::RtcImage convert( const FRtcImage& rtcImage );
agora::rtc::TranscodingUser convert( const FAgoraTranscodingUser& transcodingUser );
FAgoraUserInfo convert( const agora::rtc::UserInfo& userInfo );
agora::rtc::VideoCanvas convert( const FVideoCanvas& videoCanvas );
agora::rtc::WatermarkOptions convert( const FWatermarkOptions& watermarkOptions );
agora::rtc::VideoDimensions convert( const FVideoDimensions& dimensions );
agora::rtc::ScreenCaptureParameters convert( const FScreenCaptureParameters& parameters );
agora::rtc::Rectangle convert( const FRectangle& rectangle );
agora::rtc::VideoContentHint convert( EVIDEO_CONTENT_HINT contentHint );
FAudioVolumeInfo convert( const agora::rtc::AudioVolumeInfo& volumeInfo );
ELASTMILE_PROBE_RESULT_STATE convert( agora::rtc::LASTMILE_PROBE_RESULT_STATE  lastmileProbeResultState );
FLastmileProbeOneWayResult convert( const agora::rtc::LastmileProbeOneWayResult& lastmileProbeOneWayResult );
FLastmileProbeResult convert( const agora::rtc::LastmileProbeResult&  lastmileProbeResultStruct );
EQUALITY_ADAPT_INDICATION convert( agora::rtc::QUALITY_ADAPT_INDICATION qualityAdaptIndication );
EVIDEO_CODEC_TYPE convert( agora::rtc::VIDEO_CODEC_TYPE videoCodecType );
FLocalVideoStats convert( const agora::rtc::LocalVideoStats& localVideoStats );
EREMOTE_VIDEO_STREAM_TYPE convert( agora::rtc::REMOTE_VIDEO_STREAM_TYPE remoteVideoStreamType );
FRemoteVideoStats convert( const agora::rtc::RemoteVideoStats& remoteVideoStats );
FLocalAudioStats convert( const agora::rtc::LocalAudioStats& localAudioStats );
FRemoteAudioStats convert( const agora::rtc::RemoteAudioStats& localAudioStats );
ELOCAL_AUDIO_STREAM_ERROR convert( agora::rtc::LOCAL_AUDIO_STREAM_ERROR localAudioStreamError );
ELOCAL_AUDIO_STREAM_STATE convert( agora::rtc::LOCAL_AUDIO_STREAM_STATE localAudioStreamState );
EREMOTE_AUDIO_STATE convert( agora::rtc::REMOTE_AUDIO_STATE remoteAudioState );
EREMOTE_AUDIO_STATE_REASON convert( agora::rtc::REMOTE_AUDIO_STATE_REASON remoteAudioStateReason );
EMEDIA_DEVICE_TYPE convert( agora::rtc::MEDIA_DEVICE_TYPE mediaDeviceType );
EAUDIO_MIXING_STATE_TYPE convert( agora::rtc::AUDIO_MIXING_STATE_TYPE audioMixingStateType );
EAUDIO_MIXING_ERROR_TYPE convert( agora::rtc::AUDIO_MIXING_ERROR_TYPE audioMixingErrorType );
ELOCAL_VIDEO_STREAM_STATE convert( agora::rtc::LOCAL_VIDEO_STREAM_STATE localVideoStreamState );
ELOCAL_VIDEO_STREAM_ERROR convert( agora::rtc::LOCAL_VIDEO_STREAM_ERROR localVideoStreamError );
EREMOTE_VIDEO_STATE convert( agora::rtc::REMOTE_VIDEO_STATE remoteVideoState );
EREMOTE_VIDEO_STATE_REASON convert( agora::rtc::REMOTE_VIDEO_STATE_REASON remoteVideoStateReason );
ECHANNEL_MEDIA_RELAY_STATE convert( agora::rtc::CHANNEL_MEDIA_RELAY_STATE channelMediaRelayState );
ECHANNEL_MEDIA_RELAY_ERROR convert( agora::rtc::CHANNEL_MEDIA_RELAY_ERROR channelMediaRelayError );
ECHANNEL_MEDIA_RELAY_EVENT convert( agora::rtc::CHANNEL_MEDIA_RELAY_EVENT channelMediaRelayEvent );
ERTMP_STREAM_PUBLISH_STATE convert( agora::rtc::RTMP_STREAM_PUBLISH_STATE rtmpStreamPublishState );
ERTMP_STREAM_PUBLISH_ERROR convert( agora::rtc::RTMP_STREAM_PUBLISH_ERROR rtmpStreamPublishError );
EAUDIO_ROUTE_TYPE convert( agora::rtc::AUDIO_ROUTE_TYPE audioRouteType );
ECONNECTION_CHANGED_REASON_TYPE convert( agora::rtc::CONNECTION_CHANGED_REASON_TYPE connectionChangedReasonType );
ENETWORK_TYPE convert( agora::rtc::NETWORK_TYPE networkType );

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
agora::rtc::CAMERA_DIRECTION convert( ECAMERA_DIRECTION cameraDirection );
#endif

#if (defined(__APPLE__) && TARGET_OS_IOS)
agora::rtc::AUDIO_SESSION_OPERATION_RESTRICTION convert( EAUDIO_SESSION_OPERATION_RESTRICTION operationRestriction );
#endif

