// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobaGameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class MOBADEMO_API UGA_Combo : public UMobaGameplayAbility
{
	GENERATED_BODY()

public:

	UGA_Combo();


	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	static FGameplayTag GetComboChangeEventTag();
	static FGameplayTag GetComboChangeEventEndTag();

private:
	UFUNCTION()
	void HandleInputPress(float TimeWaited);
	void TryCommitCombo();

	
	void SetupWaitComboInputPress();
		
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	TObjectPtr<UAnimMontage> ComboMontage;

	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Data);

	
	FName NextComboName;
};
 