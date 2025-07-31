// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MobaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOBADEMO_API AMobaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//服务端
	virtual void OnPossess(APawn* InPawn) override;

	//客户端 这种也会在LS服务端调用
	virtual void AcknowledgePossession(class APawn* P) override;
private:
	UPROPERTY()
	class AMobaPlayerCharacter* MobaPlayerCharacter;
};
