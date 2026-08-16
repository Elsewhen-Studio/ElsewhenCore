// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ELSEWHENCORE_API UBasicAttributes : public UAttributeSet
{
	GENERATED_BODY()
	
	public:
	UBasicAttributes();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Health) FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBasicAttributes, Health)
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxHealth) FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBasicAttributes, MaxHealth)
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_Energy) FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS(UBasicAttributes, Energy)
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing=OnRep_MaxEnergy) FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS(UBasicAttributes, MaxEnergy)
	
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldValue) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributes, Health, OldValue);
	}
	
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributes, MaxHealth, OldValue);
	}
	
	UFUNCTION() void OnRep_Energy(const FGameplayAttributeData& OldValue) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributes, Energy, OldValue);
	}
	
	UFUNCTION() void OnRep_MaxEnergy(const FGameplayAttributeData& OldValue) const {
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBasicAttributes, MaxEnergy, OldValue);
	}
};
