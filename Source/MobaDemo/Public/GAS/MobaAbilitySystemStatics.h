// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MobaAbilitySystemStatics.generated.h"

/**
 * 
 */
UCLASS()
class MOBADEMO_API UMobaAbilitySystemStatics:public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FGameplayTag GetBasicAttackAbilityTag();
};
