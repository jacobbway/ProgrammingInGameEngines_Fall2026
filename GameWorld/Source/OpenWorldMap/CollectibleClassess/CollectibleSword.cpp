// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleSword.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"

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
    GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("Sword begin play"));

    CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleSword::OnSwordOverlap);
}

void ACollectibleSword::OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("ON SWORD OVERLAP"))

}

// Called every frame
void ACollectibleSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

