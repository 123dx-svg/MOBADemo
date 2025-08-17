// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS/MobaGameAbilityTypes.h"
#include "MobaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MOBADEMO_API UMobaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void ApplyInitialEffects();

	void GiveInitialAbilities();

	
private:
    UPROPERTY(EditDefaultsOnly,Category="Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly,Category="Gameplay Effects")
	TMap<EMobaAbilityInputID,TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly,Category="Gameplay Effects")
	TMap<EMobaAbilityInputID,TSubclassOf<UGameplayAbility>> BasicAbilities;
};
