// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MobaGameplayAbility.h"
#include "Components/SkeletalMeshComponent.h"

UAnimInstance* UMobaGameplayAbility::GetOwnerAnimInstance() const
{
	USkeletalMeshComponent* OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo();
	if (OwnerSkeletalMeshComponent)
	{
		return OwnerSkeletalMeshComponent->GetAnimInstance();
	}
	return nullptr;
}
