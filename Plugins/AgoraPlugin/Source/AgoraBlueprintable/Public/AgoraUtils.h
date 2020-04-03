// Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/UObjectGlobals.h"
#include "UECompatibility.h"
#include "AgoraUtils.generated.h"

/**
 * Auxiliary functions that can help when working with Agora in blueprints.
 */
UCLASS()
class AGORABLUEPRINTABLE_API UAgoraUtils : public UBlueprintFunctionLibrary
{
   GENERATED_BODY()

   /** Converts string number to int64.
   May be convenient when working with *Uid*.
   @param String Number as a string.
   @return
    - int64 number : Success.
    - 0 : Failure. Error message will be written to the log, search "UAgoraUtils::StringToInt64 - exception:".
   */
   UFUNCTION( BlueprintCallable, meta = ( DisplayName = "String To Int64"), Category = "Agora|Utils" )
   static int64 StringToInt64( const FString& String );

   /** Creates audio file for speakers test called \"ID_TEST_AUDIO.wav\"
   
   For Windows in *Content/Audio* directory.
   
   For Mac in *Library/Caches* directory.

   May be used for \ref UIAgora::StartAudioPlaybackDeviceTest "StartAudioPlaybackDeviceTest" function.
   @return
   - Path to the file : Success.
   - Empty string : Failure.
   */
   UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Agora|Utils" )
   static FString CreateAudioFileForSpeakersTest();
};
