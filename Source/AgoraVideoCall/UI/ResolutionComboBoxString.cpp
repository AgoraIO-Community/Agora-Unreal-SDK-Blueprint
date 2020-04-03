// Copyright (c) 2019 Agora.io. All rights reserved.


#include "ResolutionComboBoxString.h"

void UResolutionComboBoxString::addResolution( int Width, int Height, EFRAME_RATE FrameRate )
{
   int pos = Options.size();
   Entry entry( Width, Height, FrameRate );
   Options.emplace( pos, entry );
   AddOption( entry.TextOption );
}

EFRAME_RATE UResolutionComboBoxString::getSelectedResolution( int& Width, int& Height )
{
   auto Index = GetSelectedIndex();
   auto Found = Options.find( Index );
   if( Found == Options.end() )
   {
      return FRAME_RATE_FPS_15;
   }
   Width = Found->second.Width;
   Height = Found->second.Height;
   EFRAME_RATE FrameRate = Found->second.FrameRate;
   return FrameRate;
}
void UResolutionComboBoxString::AddOption( const FString& Option )
{
   UComboBoxString::AddOption( Option );
}