// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleGameBase.h"
#include "CollectibleClassess/CollectibleSword.h"
#include "CharacterClasses/BootManPlayerState.h"
#include "CharacterClasses/BootCharacter.h"
#include "CollectibleClassess/SwordDepositChest.h"
#include "Kismet/GameplayStatics.h"

ACollectibleGameBase::ACollectibleGameBase()
{
	PlayerStateClass = ABootManPlayerState::StaticClass();
}

void ACollectibleGameBase::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, TEXT("Game Base Called Begin Play"));

	TArray<AActor*> NumberOfSwords;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectibleSword::StaticClass(), NumberOfSwords);

	TotalSwordsInLevel = NumberOfSwords.Num();
}

void ACollectibleGameBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		if (ABootManPlayerState* BootState = NewPlayer->GetPlayerState<ABootManPlayerState>())
		{
			BootState->OnCollected.AddDynamic(this, &ACollectibleGameBase::HandleSwordCollected);
		}
	}
}

void ACollectibleGameBase::HandleSwordCollected(ABootManPlayerState* PlayerInfo, int32 OrigSwords, int32 CurSwords)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("Sword Collected Handler"));
	if (CurSwords >= TotalSwordsInLevel)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("All Swords Collected"));
		AActor* ChestActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASwordDepositChest::StaticClass());

		if (ASwordDepositChest* Chest = Cast<ASwordDepositChest>(ChestActor))
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("INSIDE CHEST SWORD"));
			Chest->SetBeaconActive(true);
		}
	}
}