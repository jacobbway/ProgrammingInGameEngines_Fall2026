// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BootManPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FSwordCollectedEvent,
	ABootManPlayerState*, PlayerInfo,
	int32, OrigSwords,
	int32, CurSwords
);

/**
 * 
 */
UCLASS()
class OPENWORLDMAP_API ABootManPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory",
		meta = (AllowPrivateAccess = "true"))
	int32 CollectedSwords;

public:
	ABootManPlayerState();

	int32 GetNumSwords() { return CollectedSwords; }
	void AddToNumSwords(int32 Swords);
	void ResetSwords() { CollectedSwords = 0; }

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FSwordCollectedEvent OnCollected;
};
