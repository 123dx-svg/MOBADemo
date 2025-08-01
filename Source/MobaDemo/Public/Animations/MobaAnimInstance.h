// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MobaAnimInstance.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class MOBADEMO_API UMobaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() const {return Speed;}

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const {return Speed != 0;}

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE bool IsNotMoving() const {return Speed == 0;}

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE float GetYawSpeed() const {return YawSpeed;}

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE float GetSmoothedYawSpeed() const {return SmoothedYawSpeed;}

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE bool IsJumping() const {return bIsJumping;}

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE bool IsOnGround() const {return !bIsJumping;}

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE float GetLookYawOffset() const {return LookRotOffset.Yaw;}

	UFUNCTION(BlueprintCallable,meta=(BlueprintThreadSafe))
	FORCEINLINE float GetLookPitchOffset() const {return LookRotOffset.Pitch;}

private:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwnerMovementComponent;

	float Speed;
	float YawSpeed;
	float SmoothedYawSpeed;
	bool bIsJumping;

	UPROPERTY(EditAnywhere,Category="Animation")
	float YawSpeedSmoothLerpSpeed = 1.f;
	
	FRotator BodyPrevRot;
	FRotator LookRotOffset;
	
};
