// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CollectionGameInstance.generated.h"

class ABootCharacter;
class AStalkingMonster;
class AInteractiveLight;
class ACollectibleSword;
class UCollectionGameInstance;

/**
 * 
 */
UCLASS()
class OPENWORLDMAP_API UCollectionGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	ABootCharacter* Player;
	TArray<AStalkingMonster*> Snails;
	TArray<AInteractiveLight*> Lights;

public:
	void OnStart();
	
	ABootCharacter* GetPlayer();
	AStalkingMonster* GetSnail(int32 Position);
	AInteractiveLight* GetLight(int32 Position);
	int32 GetNumSnails() { return Snails.Num(); }
	int32 GetNumLights() { return Lights.Num(); }
	void AddSnail(AStalkingMonster* Snail);
	void AddLight(AInteractiveLight* Light);
	void SetAllLightState(bool IsOn);
	bool AreAllLightsOn();
	void DestroyAllSnails();

	UFUNCTION()
	void HandleLightStateChanged(bool IsOn);
};
