// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BootManPlayerState.generated.h"

class UBootManInventory;

/**
 * 
 */
UCLASS()
class OPENWORLDMAP_API ABootManPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	UBootManInventory* PlayerInventory;
	

public:
	ABootManPlayerState();
};
