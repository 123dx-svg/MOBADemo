// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "MobaCharacter.generated.h"

class UMobaAbilitySystemComponent;
class UMobaAttributeSet;

UCLASS()
class MOBADEMO_API AMobaCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMobaCharacter();

	
	void ServerSideInitialize();
	void ClientSideInitialize();
	bool IsLocallyControlledByPlayer() const;
	//只在服务端调用
	virtual void PossessedBy(AController* NewController) override;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//************************************GameAbilityBegin********************************************//
	/**
	 * @brief 获取AbilitySystemComponent
	 * @return 
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(VisibleDefaultsOnly,Category="Gameplay Effects")
	TObjectPtr<UMobaAbilitySystemComponent> MobaAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UMobaAttributeSet> MobaAttributeSet;

	
	//************************************GameAbilityEnd**********************************************//


	//UI组件
	UPROPERTY(VisibleDefaultsOnly,Category="Gameplay UI")
	TObjectPtr<UWidgetComponent> OverHeadWidgetComponent;
	void ConfigureOverHeadStatusWidget();

	//头显组件
	UPROPERTY(VisibleDefaultsOnly,Category="Gameplay UI")
	TObjectPtr<UWidgetComponent> HeadStatGaugeWidgetComponent;
	void ConfigureHeadStatGaugeWidget();

	//不可见范围
	UPROPERTY(EditDefaultsOnly,Category="Gameplay UI")
	float HeadStatGaugeVisibilityDelayGap =1.f;

	UPROPERTY(EditDefaultsOnly,Category="Gameplay UI")
	float HeadStatGaugeVisibilityRangeSquared = 10000000.f;
	
	FTimerHandle HeadStatGaugeVisibilityHandle;

	void UpdateHeadGaugeVisibility();
};
