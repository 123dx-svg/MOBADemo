// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MobaCharacter.h"

#include "GAS/MobaAbilitySystemComponent.h"
#include "GAS/MobaAttributeSet.h"

// Sets default values
AMobaCharacter::AMobaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MobaAbilitySystemComponent = CreateDefaultSubobject<UMobaAbilitySystemComponent>(TEXT("MobaAbilitySystemComponent"));
	MobaAttributeSet = CreateDefaultSubobject<UMobaAttributeSet>(TEXT("MobaAttributeSet"));
}

// Called when the game starts or when spawned
void AMobaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMobaCharacter::ServerSideInitialize()
{
	MobaAbilitySystemComponent->InitAbilityActorInfo(this, this);
	MobaAbilitySystemComponent->ApplyInitialEffects();
}

void AMobaCharacter::ClientSideInitialize()
{
	MobaAbilitySystemComponent->InitAbilityActorInfo(this, this);
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

UAbilitySystemComponent* AMobaCharacter::GetAbilitySystemComponent() const
{
	return MobaAbilitySystemComponent;
}

