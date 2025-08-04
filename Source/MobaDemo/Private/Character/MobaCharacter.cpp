// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MobaCharacter.h"

#include "GAS/MobaAbilitySystemComponent.h"
#include "GAS/MobaAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/OverHeadStatsGauge.h"

// Sets default values
AMobaCharacter::AMobaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MobaAbilitySystemComponent = CreateDefaultSubobject<UMobaAbilitySystemComponent>(TEXT("MobaAbilitySystemComponent"));
	MobaAttributeSet = CreateDefaultSubobject<UMobaAttributeSet>(TEXT("MobaAttributeSet"));

	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidget"));
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMobaCharacter::BeginPlay()
{
	Super::BeginPlay();

	ConfigureOverHeadStatusWidget();
	
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

bool AMobaCharacter::IsLocallyControlledByPlayer() const
{
	return GetController()  && GetController()->IsLocalPlayerController();
}

void AMobaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//让AI也有血条
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInitialize();
	}
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

void AMobaCharacter::ConfigureOverHeadStatusWidget()
{
	if (!OverHeadWidgetComponent) return;
	if (IsLocallyControlledByPlayer())
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}
	UOverHeadStatsGauge* OverHeadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverHeadStatsGauge)
	{
		OverHeadStatsGauge->ConfigureWithASC(MobaAbilitySystemComponent);
		OverHeadWidgetComponent->SetHiddenInGame(false);

		GetWorldTimerManager().ClearTimer(HeadStatGaugeVisibilityHandle);
		GetWorldTimerManager().SetTimer(HeadStatGaugeVisibilityHandle,this,&AMobaCharacter::UpdateHeadGaugeVisibility,HeadStatGaugeVisibilityDelayGap,true);
	}
}

void AMobaCharacter::UpdateHeadGaugeVisibility()
{
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this,0);
	if (LocalPlayerPawn)
	{
		float DisSquared = FVector::DistSquared(GetActorLocation(),LocalPlayerPawn->GetActorLocation());
		OverHeadWidgetComponent->SetHiddenInGame(DisSquared > HeadStatGaugeVisibilityRangeSquared);
	}
}

