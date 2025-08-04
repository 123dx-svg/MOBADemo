// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/OverHeadStatsGauge.h"

#include "GAS/MobaAttributeSet.h"
#include "Widgets/ValueGauge.h"

void UOverHeadStatsGauge::ConfigureWithASC(class UAbilitySystemComponent* AbilitySystemComponent)
{
	if (AbilitySystemComponent)
	{
		HealthBar->SetAndBindToGameplayAttribute(AbilitySystemComponent, UMobaAttributeSet::GetHealthAttribute(),UMobaAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBindToGameplayAttribute(AbilitySystemComponent, UMobaAttributeSet::GetManaAttribute(),UMobaAttributeSet::GetMaxManaAttribute());	
	}
}
