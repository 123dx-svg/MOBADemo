// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA_Combo.h"

#include "GameplayTagsManager.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "GAS/MobaAbilitySystemStatics.h"

UGA_Combo::UGA_Combo()
{
	AbilityTags.AddTag(UMobaAbilitySystemStatics::GetBasicAttackAbilityTag());
	BlockAbilitiesWithTag.AddTag(UMobaAbilitySystemStatics::GetBasicAttackAbilityTag());
}

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	if (HasAuthorityOrPredictionKey(ActorInfo,&ActivationInfo))
	{
	    UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,NAME_None,ComboMontage);
		PlayComboMontageTask->OnBlendOut.AddDynamic(this,&UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this,&UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this,&UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this,&UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();

		//不用开启精确匹配
		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,GetComboChangeEventTag(),
			nullptr,false,false);

		WaitComboChangeEventTask->EventReceived.AddDynamic(this,&UGA_Combo::ComboChangedEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();
	}

	SetupWaitComboInputPress();

}

FGameplayTag UGA_Combo::GetComboChangeEventTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Combo.Change");
}

FGameplayTag UGA_Combo::GetComboChangeEventEndTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Combo.Change.End");
}

void UGA_Combo::HandleInputPress(float TimeWaited)
{
	SetupWaitComboInputPress();
	TryCommitCombo();
}

void UGA_Combo::TryCommitCombo()
{
	if (NextComboName ==  NAME_None)
	{
		return;
	}
	UAnimInstance* OwnerAnimInstance = GetOwnerAnimInstance();
	if (OwnerAnimInstance == nullptr)
		return;
	OwnerAnimInstance->Montage_SetNextSection(OwnerAnimInstance->Montage_GetCurrentSection(ComboMontage),NextComboName,ComboMontage);
}

void UGA_Combo::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPressTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPressTask->OnPress.AddDynamic(this,&UGA_Combo::HandleInputPress);
	WaitInputPressTask->ReadyForActivation();
}

void UGA_Combo::ComboChangedEventReceived(FGameplayEventData Data)
{
	FGameplayTag EventTag = Data.EventTag;
	if (EventTag ==  GetComboChangeEventEndTag())
	{
		NextComboName == NAME_None;
		UE_LOG(LogTemp, Log, TEXT("DX>>> next Combo is cleared"));
		return;
	}
	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag,TagNames);
	NextComboName = TagNames.Last();
	UE_LOG(LogTemp, Log, TEXT("DX>>> next Combo is now: %s"),*NextComboName.ToString());

	
}
