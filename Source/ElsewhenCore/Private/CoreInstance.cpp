// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreInstance.h"
#include "GeneralProjectSettings.h"

void UCoreInstance::Init() {
	Super::Init();
	
	/*
	 * Thanks to Andrew Bindraw (mrbindraw) for the plugin "CheckAppInstance". This code is from that, so cheers!
	 */

	#if PLATFORM_WINDOWS
		#if !UE_EDITOR
			const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
			const FString LockFilePath = FPlatformProcess::UserTempDir() + ProjectSettings.ProjectID.ToString();
			if (!IFileManager::Get().CreateFileWriter(*LockFilePath, 0) && true)
			{
				FPlatformApplicationMisc::RequestMinimize();
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Only one instance of the game can be running at one time.")));
				FPlatformMisc::RequestExit(0);
			}
		#endif
	#endif
}

void UCoreInstance::StartGameInstance() {
	Super::StartGameInstance();
	
}

void UCoreInstance::Shutdown() {
	Super::Shutdown();
	
}
