// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwordDepositChest.generated.h"

class StaticMeshComponent;
class UBoxComponent;
class UStaticMeshComponent;
class UCollectibleSword;
class UBootManInventory;
class ABootCharacter;

UCLASS()
class OPENWORLDMAP_API ASwordDepositChest : public AActor
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ASwordDepositChest();
	
	UFUNCTION(BlueprintCallable, Category = "Beacon")
	void SetBeaconActive(bool Active) { GoldBeacon->SetVisibility(Active); }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Collision")
	UBoxComponent* DepositArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ChestRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* GoldBeacon;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnChestOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

private:
		int32 NumSwordsInLevel;
		UFUNCTION()
		void CheckIfAllSwordsCollected(int32 NumberOfSwords);
};
