// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Misc/MessageDialog.h"

#if PLATFORM_WINDOWS
	#include "Windows/WindowsHWrapper.h"
	#include "wininet.h"
#endif

#include "CoreInstance.generated.h"

/**
 * 
 */
UCLASS()
class ELSEWHENCORE_API UCoreInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void StartGameInstance() override;
	virtual void Shutdown() override;
	
	UFUNCTION(BlueprintPure) static FString GetGameVersion() {
		FString GameVersion;
		GConfig->GetString(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("ProjectVersion"),
			GameVersion,
			GGameIni
		);
		return GameVersion;
	};
	
	UFUNCTION(BlueprintPure) static bool CheckInternetConnection() {
		#if PLATFORM_WINDOWS
				DWORD flags;
				return InternetGetConnectedState(&flags, 0);
		#else
				return false;
		#endif
	};
};
