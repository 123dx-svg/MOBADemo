// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MobaAbilitySystemStatics.h"

FGameplayTag UMobaAbilitySystemStatics::GetBasicAttackAbilityTag()
{
	return FGameplayTag::RequestGameplayTag(FName("Ability.BasicAttack"));
}
