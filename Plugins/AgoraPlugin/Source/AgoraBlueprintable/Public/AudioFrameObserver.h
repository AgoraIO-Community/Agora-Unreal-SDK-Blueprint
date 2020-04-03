#pragma once
#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
//#include <Agora/AgoraBase.h>
//#include <Agora/IAgoraRtcEngine.h>
#include <Agora/IAgoraMediaEngine.h>
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

class UAgora;
namespace agora
{
namespace blueprints
{
/** Audio Frame Observer Interface.

Inherit this class to implement custom audio frames handling
*/
class AGORABLUEPRINTABLE_API IAudioFrameObserver : public agora::media::IAudioFrameObserver
{
public:
   virtual ~IAudioFrameObserver() = default;

   /** This function is called in \ref UIAgora::Tick.

   Agora callbacks must be synchronized with Unreal Engine thread.

   Use this function to synchronize agora callbacks and UE main thread.
   @param DeltaTime The amount of time between frames (seconds).
   */
   virtual void OnTick( float DeltaTime ) = 0;
};
//todo: implement
/*
class AGORAVIDEOCALL_API AudioFrameObserver : public IAudioFrameObserver
{
public:
   AudioFrameObserver( UAgora* agora );
   virtual bool onRecordAudioFrame( AudioFrame& audioFrame ) override;
   virtual bool onPlaybackAudioFrame( AudioFrame& audioFrame ) override;
   virtual bool onMixedAudioFrame( AudioFrame& audioFrame ) override;
   virtual bool onPlaybackAudioFrameBeforeMixing( unsigned int uid, AudioFrame& audioFrame ) override;

   virtual void OnTick( float DeltaTime ) override;

public:
   UAgora* m_agora = nullptr;
};*/
}
}