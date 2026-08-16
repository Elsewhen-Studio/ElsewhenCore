// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreCharacterBase.h"
#include "../Gameplay/Attributes/BasicAttributes.h"

// Sets default values
ACoreCharacterBase::ACoreCharacterBase() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(ASCReplicationMode);
	
	BasicAttributes = CreateDefaultSubobject<UBasicAttributes>(TEXT("BasicAttributes"));
}

// Called when the game starts or when spawned
void ACoreCharacterBase::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ACoreCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACoreCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACoreCharacterBase::GetAbilitySystemComponent() const {
	return ASC;
}

void ACoreCharacterBase::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	
	if (ASC) {
		ASC->InitAbilityActorInfo(this, this);
	} else {
		UE_LOG(LogTemp, Error, TEXT("'%s' failed to find an Ability System Component! This project is built to use the Gameplay Ability System."), *GetNameSafe(this));
	}
}

void ACoreCharacterBase::OnRep_PlayerState() {
	Super::OnRep_PlayerState();
	
	if (ASC) {
		ASC->InitAbilityActorInfo(this, this);
	} else {
		UE_LOG(LogTemp, Error, TEXT("'%s' failed to find an Ability System Component! This project is built to use the Gameplay Ability System."), *GetNameSafe(this));
	}
}

