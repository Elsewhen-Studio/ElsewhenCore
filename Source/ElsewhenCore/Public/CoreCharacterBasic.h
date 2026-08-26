// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreCharacterBase.h"
#include "CoreCharacterBasic.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;
class USceneComponent;

class UPhysicsHandleComponent;

/**
 * 
 */
UCLASS()
class ELSEWHENCORE_API ACoreCharacterBasic : public ACoreCharacterBase
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flashlight", meta = (AllowPrivateAccess = "true")) USpringArmComponent* WeaponSpring;
	
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh) USkeletalMeshComponent* Mesh1P;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)	USkeletalMeshComponent* FP_Gun;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)	USceneComponent* FP_MuzzleLocation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) UPhysicsHandleComponent* PhysicsHandle;
	
public:
	ACoreCharacterBasic();
	virtual void Tick(float DeltaTime) override;
	
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	
protected:
	virtual void BeginPlay();
	
	void MoveFront(float Axis);
	void MoveSide(float Axis);
	void Turn(float Rate);
	void LookUp(float Rate);
	
	UFUNCTION(BlueprintCallable) void OnFire();
	
	void UpdateParallaxData();
	
	UFUNCTION(BlueprintCallable) void BeginInteraction(bool& bIsGrabSuccessful);
	void GrabLocation();
	bool TraceLineFromCamera(FName TraceTag, float Distance, ECollisionChannel Channel, FHitResult& OutResult);
	
	UFUNCTION(BlueprintCallable) void StopGrab();
	UFUNCTION(BlueprintCallable) void ToggleGrab(bool& bIsGrabSuccessful);
	UFUNCTION(BlueprintCallable) void ShootGrab();
	
	UPROPERTY(EditAnywhere) UMaterialParameterCollection* ParallaxCollection;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Movement|Speed") float WalkSpeed = 620.0f; // 350.0f
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Movement|Speed") float RunSpeed = 1240.0f; // 620.0f
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Movement|Speed") float CrouchSpeed = 285.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction") float GrabDistance = 512.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Interaction") FHitResult HitResult;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frequencies") float WalkFrequency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Frequencies") float SprintFrequency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float InterpSpeed = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timers") float IdleTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timers") float BobTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float IdlePitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BobHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BobRoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SprintBobHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SprintBobRoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float WalkBobHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float WalkBobRoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector BaseCamLoc;
	
	UPROPERTY(BlueprintReadWrite, Category = "Interaction") bool bIsGrabbing;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) FVector GunOffset;
	UPROPERTY(EditDefaultsOnly, Category=Projectile) TSubclassOf<class ACoreCannonProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) 	USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage* FireAnimation;
	
private:
	UPROPERTY() UPrimitiveComponent* HitComponent;
	
	UPROPERTY() float YawRate;
	UPROPERTY() float PitchRate;
	UPROPERTY() float YawParallaxOffset;
	UPROPERTY() float PitchParallaxOffset;
	UPROPERTY() float ParallaxSpeed = 12.0f;
	UPROPERTY() FRotator CameraRot;
	UPROPERTY() float MinMaxYawRate = 2.0f;
	UPROPERTY() float MinMaxPitchRate = 12.0f;
};
