// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AgoraPlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#include <string>

#include <Agora/IAgoraRtcEngine.h>

#define LOCTEXT_NAMESPACE "FAgoraPluginModule"

void FAgoraPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("AgoraPlugin")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/Agora/x64/Release/agora_rtc_sdk.dll"));
    
    AgoraLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
    
    if (AgoraLibraryHandle)
    {
        // Call the test function in the third party library
        int build = 0;
        getAgoraRtcEngineVersion(&build);
        
        std::string buildVersion = std::to_string(build);
        buildVersion = "Hello from Agora! buildVersion: " + buildVersion;
        
        UE_LOG(LogTemp, Warning, TEXT("FAgoraPluginModule: %s"), ANSI_TO_TCHAR(buildVersion.c_str()) );
    }
    else
    {
        FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load Agora third party library"));
    }
    
#elif PLATFORM_MAC

#endif // PLATFORM_WINDOWS

}

void FAgoraPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
    if(AgoraLibraryHandle)
    {
        FPlatformProcess::FreeDllHandle(AgoraLibraryHandle);
        AgoraLibraryHandle = nullptr;
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAgoraPluginModule, AgoraPlugin)
