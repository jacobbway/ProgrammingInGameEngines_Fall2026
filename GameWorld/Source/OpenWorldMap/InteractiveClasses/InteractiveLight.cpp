// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveLight.h"
#include "Components/SceneComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameModeClasses/CollectionGameInstance.h"
#include "GameFramework/Character.h"
#include "CharacterClasses/BootManPlayerState.h"
#include "LightState.h"

// Sets default values
AInteractiveLight::AInteractiveLight()
{
	PrimaryActorTick.bCanEverTick = true;

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

	// player isnt near at start
	IsPlayerNear = false; // begin play
}

void AInteractiveLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeInState += DeltaTime;
	
	bool AllLightsOn = GameInstance ? GameInstance->AreAllLightsOn() : false;

	CurrentState->InState(this, DeltaTime, TimeInState, AllLightsOn, IsPlayerNear);

	LightState* NextState = CurrentState->NextState(this, DeltaTime, TimeInState, AllLightsOn, IsPlayerNear);

	if (NextState && NextState != CurrentState)
	{
		CurrentState = NextState;
		TimeInState = 0.0f;
	}
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
		TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AInteractiveLight::OnOverlapEnd);

	}

	GameInstance = GetWorld()->GetGameInstanceChecked<UCollectionGameInstance>();
	if (GameInstance)
	{
		GameInstance->AddLight(this);
	}

	CurrentState = OffLightState::GetInstance();
	TimeInState = 0.0f;

	CurrentState->InState(this, 0.0f, TimeInState, false, IsPlayerNear);
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
				IsPlayerNear = true;
			}
		}
	}
}

void AInteractiveLight::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("In End Over Lap"));
	if (OtherActor && OtherActor != this)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("in other actor"));
		if (APawn* PlayerPawn = Cast<APawn>(OtherActor))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("In Pawn"));
			if (ABootManPlayerState* BootState = PlayerPawn->GetPlayerState<ABootManPlayerState>())
			{
				IsPlayerNear = false;
			}
		}
	}
}

void AInteractiveLight::SetIsLightOn(bool NewOn)
{
	IsLightOn = NewOn;
	SpotLight->SetVisibility(IsLightOn);
	OnLightStateChange.Broadcast(IsLightOn);
}

void AInteractiveLight::FadeLight(float CurrentTimeInState)
{
	if (FadeDuration > 0.0f)
	{
		float RemainingTime = FadeDuration - CurrentTimeInState;

		if (RemainingTime < 0.0f)
		{
			RemainingTime = 0.0f;
		}

		float Alpha = RemainingTime / FadeDuration;
		float TargetIntensity = Alpha * LightMaxIntensity;

		SetSpotLightIntensity(TargetIntensity);
	}
}

void AInteractiveLight::SetSpotLightIntensity(float Intensity)
{
	SpotLight->SetIntensity(Intensity);
	if(Intensity < 3.0f)
		SetIsLightOn(false);
}

