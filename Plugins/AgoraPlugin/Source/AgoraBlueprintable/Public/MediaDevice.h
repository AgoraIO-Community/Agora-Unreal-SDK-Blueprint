#pragma once

#include "CoreMinimal.h"
#include "MediaDevice.generated.h"

/** Describes audio and video devices available in the system. */
USTRUCT( Blueprintable )
struct FMediaDevice
{
   GENERATED_USTRUCT_BODY()

   /** Specified index of the device. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "MediaDevice" )
   int Index;

   /** Device Id. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "MediaDevice" )
   FString DeviceID;
   
   /** Device name. */
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "MediaDevice" )
   FString DeviceName;

   FMediaDevice() = default;
   FMediaDevice( int index, const FString& deviceId, const FString& deviceName )
      : Index( index )
      , DeviceID( deviceId )
      , DeviceName( deviceName )
   {}
};