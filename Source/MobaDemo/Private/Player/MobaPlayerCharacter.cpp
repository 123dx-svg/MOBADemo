// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MobaPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

AMobaPlayerCharacter::AMobaPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate = FRotator(0,720,0);
}

void AMobaPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (OwningPlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GameplayInputContext);
			InputSubsystem->AddMappingContext(GameplayInputContext,0);
		}
	}
}

void AMobaPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComp)
	{
		EnhancedInputComp->BindAction(JumpAction,ETriggerEvent::Triggered,this,&AMobaPlayerCharacter::Jump);
		EnhancedInputComp->BindAction(LookAction,ETriggerEvent::Triggered,this,&AMobaPlayerCharacter::HandleLookInput);
		EnhancedInputComp->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AMobaPlayerCharacter::HandleMoveInput);

		for (const auto& InputActions:AbilityInputActions)
		{
			//新增参数
			EnhancedInputComp->BindAction(InputActions.Value,ETriggerEvent::Triggered,this,&AMobaPlayerCharacter::HandleAbilityInput,InputActions.Key);
		}
	}
}

void AMobaPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();

	AddControllerPitchInput(-InputVal.Y);
	AddControllerYawInput(InputVal.X);
	
}

void AMobaPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputVal = InputActionValue.Get<FVector2D>();
	InputVal.Normalize();

	AddMovementInput(GetMoveFwdDir()*InputVal.Y+GetLookRightDir()*InputVal.X);
}

void AMobaPlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue,EMobaAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();
	if (bPressed)
	{
		//根据ID判断按下
		GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(InputID));
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<int32>(InputID));
	}
}

FVector AMobaPlayerCharacter::GetLookRightDir() const
{
	return CameraComponent->GetRightVector();
}

FVector AMobaPlayerCharacter::GetLookFwdDir() const
{
	return CameraComponent->GetForwardVector();
}

FVector AMobaPlayerCharacter::GetMoveFwdDir() const
{
	return FVector::CrossProduct(GetLookRightDir(),FVector::UpVector);
}
