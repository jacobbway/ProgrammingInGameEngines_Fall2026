// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeClasses/CollectionGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CharacterClasses/BootCharacter.h"
#include "MonsterClasses/StalkingMonster.h"

void UCollectionGameInstance::OnStart()
{

}

ABootCharacter* UCollectionGameInstance::GetPlayer()
{
	if (Player == nullptr)
	{
		Player = Cast<ABootCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	return Player;
}

AStalkingMonster* UCollectionGameInstance::GetSnail(int32 Position)
{
	if(Snails.IsValidIndex(Position))
		return Snails[Position];
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Snail Not Found %d doesnt exist"), Position)
		return nullptr;
	}
}

AInteractiveLight* UCollectionGameInstance::GetLight(int32 Position)
{
	if (Lights.IsValidIndex(Position))
		return Lights[Position];
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Light Not Found %d doesnt exist"), Position)
		return nullptr;
	}
}

void UCollectionGameInstance::AddSnail(AStalkingMonster* Snail)
{
	if (Snail)
	{
		Snails.Add(Snail);
	}
}

void UCollectionGameInstance::AddLight(AInteractiveLight* Light)
{
	if (Light)
	{
		Lights.Add(Light);
	}
}

void UCollectionGameInstance::SetAllLightState(bool IsOn)
{
}

bool UCollectionGameInstance::AreAllLightsInState(bool IsOn)
{
	return false;
}

void UCollectionGameInstance::DestroyAllSnails()
{
}

void UCollectionGameInstance::HandleLightStateChanged(bool IsOn)
{
}
