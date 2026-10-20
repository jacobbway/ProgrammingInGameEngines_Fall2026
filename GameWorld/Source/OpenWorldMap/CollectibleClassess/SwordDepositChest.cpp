// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordDepositChest.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterClasses/BootCharacter.h"
#include "Components/BoxComponent.h"
#include "CollectibleClassess/CollectibleSword.h"
#include "CharacterClasses/BootManInventory.h"

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

	DepositArea->OnComponentBeginOverlap.AddDynamic(this, &ASwordDepositChest::OnChestOverlap);

    TArray<AActor*> FoundSwords;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectibleSword::StaticClass(), FoundSwords);

	NumSwordsInLevel = FoundSwords.Num();
	SetBeaconActive(false);

	UE_LOG(LogTemp, Warning, TEXT("Number of swords in level: %d"), NumSwordsInLevel)

    if (ABootCharacter* Player = Cast<ABootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
    {
        if (UBootManInventory* CharInventory = Player->GetInventory())
        {
            CharInventory->OnSwordNumberChanged.AddDynamic(this, &ASwordDepositChest::CheckIfAllSwordsCollected);
        }
    }
}

void ASwordDepositChest::OnChestOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        if (APawn* PlayerPawn = Cast<APawn>(OtherActor))
        {
            if (ABootCharacter* BootCharacter = Cast<ABootCharacter>(PlayerPawn))
            {
                if (BootCharacter->GetInventory()->GetNumberOfSwords() == NumSwordsInLevel)
                {
					UE_LOG(LogTemp, Warning, TEXT("All swords deposited: %d"), BootCharacter->GetInventory()->GetNumberOfSwords());
                    SetBeaconActive(false);
					BootCharacter->GetInventory()->RemoveAllSwords();
                }
            }
        }
    }
}

void ASwordDepositChest::CheckIfAllSwordsCollected(int32 NumberOfSwords)
{
    if (NumberOfSwords == NumSwordsInLevel)
    {
        SetBeaconActive(true);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("All swords collected!"));
    }
}

// Called every frame
void ASwordDepositChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

