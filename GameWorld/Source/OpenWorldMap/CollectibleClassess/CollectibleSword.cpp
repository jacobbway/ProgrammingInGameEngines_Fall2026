// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleSword.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterClasses/BootCharacter.h"
#include "CharacterClasses/BootManInventory.h"

static int32 GlobalSwordId = 1;

// Sets default values
ACollectibleSword::ACollectibleSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    SwordRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SwordRoot"));
    RootComponent = SwordRoot;

    CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
    CapsuleCollider->SetupAttachment(RootComponent);

    CapsuleCollider->InitCapsuleSize(20.f, 60.f);
}

// Called when the game starts or when spawned
void ACollectibleSword::BeginPlay()
{
	Super::BeginPlay();
    //GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("Sword begin play"));

    CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleSword::OnSwordOverlap);

    if (SwordStats.SwordID == 0)
    {
        SwordStats.SwordID = GlobalSwordId;
        GlobalSwordId++;
    }
}

void ACollectibleSword::OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        if (ABootCharacter* PlayerCharacter = Cast<ABootCharacter>(OtherActor))
        {
            if (UBootManInventory* CharInventory = PlayerCharacter->GetInventory())
            {
				UE_LOG(LogTemp, Log, TEXT("Player Collected Sword: %d"), SwordStats.SwordID);
                CharInventory->AddSword(SwordStats);
				Destroy();
            }
        }
    }
}

// Called every frame
void ACollectibleSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

