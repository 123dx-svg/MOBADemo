// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/MobaAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMobaAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
	
}

void UMobaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (OwnerCharacter)
	{
		Speed = OwnerCharacter->GetVelocity().Length();

		//用户混合空间计算Lean
		FRotator BodyRot = OwnerCharacter->GetActorRotation();
		FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot,BodyPrevRot);
		BodyPrevRot = BodyRot;
		YawSpeed =BodyRotDelta.Yaw/DeltaSeconds;
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed,YawSpeed,DeltaSeconds,YawSpeedSmoothLerpSpeed);
		//计算瞄准偏移 网络同步时不一定会同步Yaw值 因为客户端只有自己的Controller
		FRotator ControlRot = OwnerCharacter->GetBaseAimRotation();
		LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot,BodyRot);
	}

	if (OwnerMovementComponent)
	{
		bIsJumping =  OwnerMovementComponent->IsFalling();
	}
}

void UMobaAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
