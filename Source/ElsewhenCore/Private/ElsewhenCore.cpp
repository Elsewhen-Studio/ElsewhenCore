// Copyright Epic Games, Inc. All Rights Reserved.

#include "ElsewhenCore.h"

#include "GameplayTagsManager.h"

#define LOCTEXT_NAMESPACE "FElsewhenCoreModule"

void FElsewhenCoreModule::StartupModule() {
	UGameplayTagsManager::Get().AddTagIniSearchPath(FPaths::ProjectPluginsDir() / TEXT("ElsewhenCore/Config/Tags"));
}

void FElsewhenCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FElsewhenCoreModule, ElsewhenCore)