// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AgoraBlueprintable.h"

#define LOCTEXT_NAMESPACE "FAgoraBlueprintableModule"

DEFINE_LOG_CATEGORY( AgoraEngineLog );

void FAgoraBlueprintableModule::StartupModule()
{
}

void FAgoraBlueprintableModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAgoraBlueprintableModule, AgoraBlueprintable)
