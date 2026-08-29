// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreCharacterBasic.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameUserSettings.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "CoreInteractionInterface.h"

ACoreCharacterBasic::ACoreCharacterBasic() {
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->FallingLateralFriction = 5.0f;
	
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->MaxAcceleration = 857.25f;
	
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;
	
	WeaponSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("WeaponSpring"));
	WeaponSpring->SetupAttachment(CameraComponent);
	WeaponSpring->TargetArmLength = 0.0f;
	WeaponSpring->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	WeaponSpring->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(WeaponSpring);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);
	
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
	
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

void ACoreCharacterBasic::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	UpdateParallaxData();
	
	bIsGrabbing = IsValid(PhysicsHandle->GetGrabbedComponent());
	
	TraceLineFromCamera(FName("BaseTrace"), GrabDistance, ECC_Camera, HitResult);
	GrabLocation();
}

void ACoreCharacterBasic::BeginPlay() {
	Super::BeginPlay();
	
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void ACoreCharacterBasic::MoveFront(float Axis) {
	if (Axis != 0.0f) {
		AddMovementInput(GetActorForwardVector(), Axis);
	}
}

void ACoreCharacterBasic::MoveSide(float Axis) {
	if (Axis != 0.0f) {
		AddMovementInput(GetActorRightVector(), Axis);
	}
}

void ACoreCharacterBasic::Turn(float Rate) {
	if (Rate != 0.0f) {
		AddControllerYawInput(Rate * 120.0f * GetWorld()->GetDeltaSeconds());
	}
}

void ACoreCharacterBasic::LookUp(float Rate) {
	if (Rate != 0.0f) {
		AddControllerPitchInput(Rate * 120.0f * GetWorld()->GetDeltaSeconds());
	}
}

void ACoreCharacterBasic::OnFire() {
	
}

void ACoreCharacterBasic::UpdateParallaxData() {
	PitchRate = UKismetMathLibrary::FClamp((CameraComponent->GetComponentRotation().Pitch - CameraRot.Pitch) + PitchRate, MinMaxPitchRate * -1.0f, MinMaxPitchRate);
	YawRate = UKismetMathLibrary::FClamp((CameraComponent->GetComponentRotation().Yaw - CameraRot.Yaw) + YawRate, MinMaxYawRate * -1.0f, MinMaxYawRate);
	CameraRot = CameraComponent->GetComponentRotation();
	PitchParallaxOffset = UKismetMathLibrary::FInterpTo(PitchParallaxOffset, PitchRate, GetWorld()->GetDeltaSeconds(), ParallaxSpeed);
	YawParallaxOffset = UKismetMathLibrary::FInterpTo(YawParallaxOffset, YawRate, GetWorld()->GetDeltaSeconds(), ParallaxSpeed);

	if (ParallaxCollection != nullptr) {
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), ParallaxCollection, "Offset", FLinearColor(YawParallaxOffset, PitchParallaxOffset, 0.0f));
	}

	PitchRate = UKismetMathLibrary::FInterpTo(PitchRate, 0.0f, GetWorld()->GetDeltaSeconds(), ParallaxSpeed);
	YawRate = UKismetMathLibrary::FInterpTo(YawRate, 0.0f, GetWorld()->GetDeltaSeconds(), ParallaxSpeed);
}

void ACoreCharacterBasic::BeginInteraction(bool& bIsGrabSuccessful) {
	if (!bIsGrabbing) {
		if (IsValid(HitResult.GetActor()) && HitResult.GetActor()->GetClass()->ImplementsInterface(UCoreInteractionInterface::StaticClass())) {
			ICoreInteractionInterface::Execute_Use(HitResult.GetActor());
		} else if (IsValid(HitResult.GetComponent())) {
			if (HitResult.GetComponent()->IsSimulatingPhysics()) {
				HitComponent = HitResult.GetComponent();
				PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitComponent->GetComponentLocation(), HitComponent->GetRelativeRotation());
				if (UGameUserSettings::GetGameUserSettings()->GetShadowQuality() < 2) {
					PhysicsHandle->GetGrabbedComponent()->SetCastShadow(false);
				}
				bIsGrabSuccessful = IsValid(PhysicsHandle->GetGrabbedComponent());
			}
		}
	}
}

void ACoreCharacterBasic::GrabLocation() {
	if (bIsGrabbing) {
		PhysicsHandle->SetTargetLocationAndRotation(CameraComponent->GetComponentLocation() + (CameraComponent->GetForwardVector() * GrabDistance), GetActorRotation());
		if (IsValid(HitComponent)) {
			HitComponent->SetRelativeRotation(FRotator(0, HitComponent->GetRelativeRotation().Yaw, 0), false, nullptr);
		}
	}
}

bool ACoreCharacterBasic::TraceLineFromCamera(FName TraceTag, float Distance, ECollisionChannel Channel, FHitResult& OutResult) {
	UWorld* World = GetWorld();
	if (!bIsGrabbing && IsValid(World)) {
		FVector Start = CameraComponent->GetComponentLocation();
		FVector End = (CameraComponent->GetForwardVector() * GrabDistance) + Start;

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.TraceTag = TraceTag;
		TraceParams.bTraceComplex = true;
		TraceParams.MobilityType = EQueryMobilityType::Dynamic;
        
		return World->LineTraceSingleByChannel(OutResult, Start, End, Channel, TraceParams);
	}

	return false;
}

void ACoreCharacterBasic::StopGrab() {
	if (bIsGrabbing) {
		PhysicsHandle->GetGrabbedComponent()->SetCastShadow(true);
		PhysicsHandle->ReleaseComponent();
		bIsGrabbing = IsValid(PhysicsHandle->GetGrabbedComponent());
	}
}

void ACoreCharacterBasic::ToggleGrab(bool& bIsGrabSuccessful) {
	if (bIsGrabbing) {
		StopGrab();
	} else {
		BeginInteraction(bIsGrabSuccessful);
	}
}

void ACoreCharacterBasic::ShootGrab() {
	if (bIsGrabbing) {
		const float Strength = 5000.0f;
		const FVector Velocity = CameraComponent->GetForwardVector() * Strength;

		PhysicsHandle->GetGrabbedComponent()->SetCastShadow(true);
		PhysicsHandle->GetGrabbedComponent()->AddImpulse(Velocity, NAME_None, true);
		PhysicsHandle->ReleaseComponent();
	}
}
