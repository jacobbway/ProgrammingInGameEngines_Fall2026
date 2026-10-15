// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveLight.h"
#include "Components/SceneComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "CharacterClasses/BootManPlayerState.h"

// Sets default values
AInteractiveLight::AInteractiveLight()
{
	PrimaryActorTick.bCanEverTick = false;

	// did this in sword
	LightRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LightRoot"));
	RootComponent = LightRoot;

	// attach the light to the scene root
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);

	// attach capsule to light
	TriggerZone = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerZone"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));
	TriggerZone->InitCapsuleSize(30.0f, 120.0f);

	// set light to off
	IsLightOn = false;
}

// Called when the game starts or when spawned
void AInteractiveLight::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("Light begin play"));

	if (SpotLight)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, TEXT("SpotLight is real"));
		SpotLight->SetVisibility(IsLightOn);
	}
	if (TriggerZone)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, TEXT("Trigger is real"));
		TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveLight::OnOverlapBegin);
	}
}

void AInteractiveLight::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("In Overlap"));
	// Ensure the other actor is valid, is not this actor
	if (OtherActor && OtherActor != this)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("in other actor"));
		if (APawn* PlayerPawn = Cast<APawn>(OtherActor))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("In Pawn"));
			if (ABootManPlayerState* BootState = PlayerPawn->GetPlayerState<ABootManPlayerState>())
			{
				IsLightOn = !IsLightOn;

				//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("Set Light On"));
				SpotLight->SetVisibility(IsLightOn);
				// Broadcast the new state via our delegate
				OnLightStateChange.Broadcast(IsLightOn);
			}
		}
	}
}

