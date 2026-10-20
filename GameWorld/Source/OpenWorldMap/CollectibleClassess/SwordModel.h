// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "SwordModel.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSwordModel
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	FName SwordName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	int32 SwordID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")	
	int32 SwordValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword")
	bool IsCollected;

	FSwordModel()
	{
		SwordName = FName(TEXT("CollectibleSword"));
		SwordID = 0;	
		SwordValue = 100;
		IsCollected = false;
	}
};
