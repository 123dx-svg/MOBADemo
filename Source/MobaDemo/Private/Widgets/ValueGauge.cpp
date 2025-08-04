// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ValueGauge.h"

#include "FrameNumberDisplayFormat.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GAS/MobaAbilitySystemComponent.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::SetAndBindToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (AbilitySystemComponent)
	{
		bool bFound;
		float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute,bFound);
		float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute,bFound);
		if (bFound)
			SetValue(Value,MaxValue);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this,&UValueGauge::ValueChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this,&UValueGauge::MaxValueChanged);
	}
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	CachedValue = NewValue;
	CachedMaxValue = NewMaxValue;
	
	if (NewMaxValue ==0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ValueGauge::%s, NewMaxValue is 0"),*GetName());
		return;
	}

	float NewPercentage = NewValue / NewMaxValue;
	ProgressBar->SetPercent(NewPercentage);

	// 整数显示
	FNumberFormattingOptions FormatOpt = FNumberFormattingOptions().SetMaximumFractionalDigits(0);

	ValueText->SetText(
		FText::Format(
			FTextFormat::FromString("{0}/{1}"),
			FText::AsNumber(NewValue,&FormatOpt),
			FText::AsNumber(NewMaxValue,&FormatOpt)
			)
		);
}

void UValueGauge::ValueChanged(const FOnAttributeChangeData& ChangedData)
{
	SetValue(ChangedData.NewValue,CachedMaxValue);
}

void UValueGauge::MaxValueChanged(const FOnAttributeChangeData& ChangedMaxData)
{
	SetValue(CachedValue,ChangedMaxData.NewValue);
}
