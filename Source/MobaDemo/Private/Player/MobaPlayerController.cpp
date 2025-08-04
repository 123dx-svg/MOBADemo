// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MobaPlayerController.h"
#include "Widgets/GameplayWidget.h"
#include "Blueprint/UserWidget.h"
#include "Player/MobaPlayerCharacter.h"

void AMobaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	MobaPlayerCharacter = Cast<AMobaPlayerCharacter>(InPawn);
	if (MobaPlayerCharacter)
	{
		MobaPlayerCharacter->ServerSideInitialize();
	}
}

void AMobaPlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);
	MobaPlayerCharacter = Cast<AMobaPlayerCharacter>(P);
	if (MobaPlayerCharacter)
	{
		MobaPlayerCharacter->ClientSideInitialize();
		SpawnGameplayWidget();
	}
}

void AMobaPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController())
		return;
	GameplayWidget = CreateWidget<UGameplayWidget>(this,GameplayWidgetClass);
	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}
