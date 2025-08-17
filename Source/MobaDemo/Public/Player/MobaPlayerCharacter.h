// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MobaCharacter.h"
#include  "GAS/MobaGameAbilityTypes.h"
#include "MobaPlayerCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class MOBADEMO_API AMobaPlayerCharacter : public AMobaCharacter
{
	GENERATED_BODY()

public:
	AMobaPlayerCharacter();

	virtual void PawnClientRestart() override;

	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:

	UPROPERTY(VisibleDefaultsOnly,Category="View")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleDefaultsOnly,Category="View")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	FVector GetLookRightDir() const;
	FVector GetLookFwdDir() const;
	FVector GetMoveFwdDir() const;

	//************************************Input  Begin********************************************//	
private:
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TMap<EMobaAbilityInputID,TObjectPtr<UInputAction>> AbilityInputActions;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputMappingContext> GameplayInputContext;

	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	void HandleAbilityInput(const FInputActionValue& InputActionValue,EMobaAbilityInputID InputID);

	//************************************Input End********************************************//
	
};
