// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
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

};
