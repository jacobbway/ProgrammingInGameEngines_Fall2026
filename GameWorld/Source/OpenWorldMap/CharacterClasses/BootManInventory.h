// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BootManInventory.generated.h"

struct FSwordModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FSwordInventoryChanged, 
	int32, NumberOfSwords
);

/**
 * 
 */
UCLASS()
class OPENWORLDMAP_API UBootManInventory : public UObject
{
	GENERATED_BODY()

public:
	UBootManInventory();

	FSwordInventoryChanged OnSwordNumberChanged;

	UFUNCTION()
	void AddSword(const FSwordModel& Sword);
	
	UFUNCTION()
	int32 GetNumberOfSwords();

	UFUNCTION()
	FSwordModel GetSwordByID(int32 SwordID) const;

	UFUNCTION()
	void RemoveAllSwords();

private:
	TArray<FSwordModel> Swords;
};
