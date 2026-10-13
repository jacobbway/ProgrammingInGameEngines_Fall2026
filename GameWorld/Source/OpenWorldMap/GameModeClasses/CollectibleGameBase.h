// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CollectibleGameBase.generated.h"

class ACollectibleSword;
class ABootManPlayerState;
class ASwordDepositChest;
/**
 * 
 */
UCLASS()
class OPENWORLDMAP_API ACollectibleGameBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 TotalSwordsInLevel;

	UFUNCTION()
	void HandleSwordCollected(class ABootManPlayerState* PlayerInfo, int32 OrigSwords, int32 CurSwords);

public:
	ACollectibleGameBase();
};
