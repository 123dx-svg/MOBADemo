// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameplayWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/MobaAttributeSet.h"
#include "Widgets/ValueGauge.h"

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (OwnerAbilitySystemComponent)
	{
		HealthBar->SetAndBindToGameplayAttribute(OwnerAbilitySystemComponent, UMobaAttributeSet::GetHealthAttribute(),UMobaAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBindToGameplayAttribute(OwnerAbilitySystemComponent, UMobaAttributeSet::GetManaAttribute(),UMobaAttributeSet::GetMaxManaAttribute());
	}	
}
