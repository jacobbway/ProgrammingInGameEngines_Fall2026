// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StalkingMonster.generated.h"

class UArrowComponent;
class USphereComponent;

UCLASS()
class OPENWORLDMAP_API AStalkingMonster : public APawn
{
	GENERATED_BODY()

private:
	float PlayerFOV = 0.8f;

public:
	// Sets default values for this pawn's properties
	AStalkingMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDistance = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnSpeed = 200.0f; // degrees/sec

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ViewDistance = 1000.0f; // want to be far so they are always moving in

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldOfView = 360.0f; // might not need. Going for can always see player	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Snail Component")
	USceneComponent* SnailRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Snail Component")
	USphereComponent* SnailZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Snail Component")
	UArrowComponent* SnailForward;

	UFUNCTION()
	bool IsPlayerLooking();

	UFUNCTION()
	void RotateToPlayer(float DeltaTime);

	UFUNCTION()
	void MoveToPlayer(float DeltaTime);

	UFUNCTION()
	void MoveTo(float DeltaTime, FVector Location);
};
