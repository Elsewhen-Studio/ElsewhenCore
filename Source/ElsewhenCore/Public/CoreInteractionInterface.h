// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoreInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCoreInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ELSEWHENCORE_API ICoreInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) FText LookAt();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void Use();
};
