// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

#include "CoreCharacterBase.generated.h"

UCLASS()
class ELSEWHENCORE_API ACoreCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACoreCharacterBase();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities") UAbilitySystemComponent* ASC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities") class UBasicAttributes* BasicAttributes;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities") EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;
};
