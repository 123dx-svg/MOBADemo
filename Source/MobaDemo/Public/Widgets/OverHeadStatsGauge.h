// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverHeadStatsGauge.generated.h"

class UValueGauge;
/**
 * 
 */
UCLASS()
class MOBADEMO_API UOverHeadStatsGauge : public UUserWidget
{
	GENERATED_BODY()

public:
	void ConfigureWithASC(class UAbilitySystemComponent* AbilitySystemComponent);

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UValueGauge> HealthBar;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UValueGauge> ManaBar;
	
};
