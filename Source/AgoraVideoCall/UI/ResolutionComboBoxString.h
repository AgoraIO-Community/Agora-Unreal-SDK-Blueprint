// Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxString.h"
#include <Containers/EnumAsByte.h>
#include <map>
#include "UECompatibility.h"
#include "ResolutionComboBoxString.generated.h"

struct Entry
{
   Entry(
      int PassedWidth,
      int PassedHeight,
      EFRAME_RATE PassedFrameRate )
      : Width( PassedWidth )
      , Height( PassedHeight )
      , FrameRate( PassedFrameRate )
   {
      TextOption = FString::FromInt( Width ) + "x"
         + FString::FromInt( Height ) + " " + FString::FromInt( FrameRate ) + "fps";
   }
   int Width;
   int Height;
   EFRAME_RATE FrameRate;

   FString TextOption;
};

/**
 * 
 */
UCLASS()
//todo: add this combo box to c++ implementation?
class AGORAVIDEOCALL_API UResolutionComboBoxString : public UComboBoxString
{
   GENERATED_BODY()

public:
   UFUNCTION( BlueprintCallable )
      void addResolution( int Width, int Height, EFRAME_RATE FrameRate );
   
   UFUNCTION( BlueprintCallable )
      EFRAME_RATE getSelectedResolution( int& Width, int& Height );

   private:
      
   std::map<int, Entry> Options;
   
   void AddOption( const FString& Option );
};
