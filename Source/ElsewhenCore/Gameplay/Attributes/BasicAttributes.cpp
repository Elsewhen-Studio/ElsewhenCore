// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttributes.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UBasicAttributes::UBasicAttributes()
{
	MaxHealth = 100.0f;
	Health = MaxHealth;

	MaxEnergy = 100.0f;
	Energy = MaxEnergy;
}

void UBasicAttributes::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributes, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributes, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributes, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributes, MaxEnergy, COND_None, REPNOTIFY_Always);
}

void UBasicAttributes::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	} else if (Attribute == GetEnergyAttribute()){
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxEnergy());
	}
}

void UBasicAttributes::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute ==  GetHealthAttribute()) {
		SetHealth(GetHealth());
	} else if (Data.EvaluatedData.Attribute == GetEnergyAttribute())  {
		SetEnergy(GetEnergy());
	}
}
