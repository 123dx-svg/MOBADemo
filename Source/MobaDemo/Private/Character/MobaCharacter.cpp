// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MobaCharacter.h"

// Sets default values
AMobaCharacter::AMobaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AMobaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMobaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMobaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

