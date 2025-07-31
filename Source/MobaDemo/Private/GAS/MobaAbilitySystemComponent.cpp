// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MobaAbilitySystemComponent.h"

void UMobaAbilitySystemComponent::ApplyInitialEffects()
{
	//像初始生命属性这么重要的值当然要在服务器端初始化
	if (!GetOwner() || !GetOwner()->HasAuthority())
		return;
	for (const auto &EffectClass : InitialEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(EffectClass,1,MakeEffectContext());
		//这种获取不需要实例化对象
		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
