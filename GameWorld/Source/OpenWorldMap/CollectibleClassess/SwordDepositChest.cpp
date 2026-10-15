// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordDepositChest.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterClasses/BootManPlayerState.h"
#include "Components/BoxComponent.h"

// Sets default values
ASwordDepositChest::ASwordDepositChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ChestRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ChestRoot"));
	RootComponent = ChestRoot;

	DepositArea = CreateDefaultSubobject<UBoxComponent>(TEXT("DepositArea"));
	DepositArea->SetupAttachment(RootComponent);

    GoldBeacon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoldBeacon"));
    GoldBeacon->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASwordDepositChest::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("CHEST begin play"));

	DepositArea->OnComponentBeginOverlap.AddDynamic(this, &ASwordDepositChest::OnChestOverlap);

	SetBeaconActive(false);
}

void ASwordDepositChest::OnChestOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        if (APawn* PlayerPawn = Cast<APawn>(OtherActor))
        {
            if (ABootManPlayerState* BootState = PlayerPawn->GetPlayerState<ABootManPlayerState>())
            {
                UE_LOG(LogTemp, Warning, TEXT("Player successfully touched the chest!"));
                BootState->ResetSwords();
                SetBeaconActive(false);
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("All Swords Deposited!"));
            }
        }
    }
}

// Called every frame
void ASwordDepositChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

