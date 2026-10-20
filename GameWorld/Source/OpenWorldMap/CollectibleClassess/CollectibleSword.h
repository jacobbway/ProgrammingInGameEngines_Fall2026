// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwordModel.h"
#include "GameFramework/Actor.h"
#include "CollectibleSword.generated.h"

class UCapsuleComponent;
class USceneComponent;
class ABootCharacter;
class ABootManInventory;

UCLASS()
class OPENWORLDMAP_API ACollectibleSword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleSword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SwordRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword Properties")
	FSwordModel SwordStats;

	UFUNCTION()
	void OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep,
		const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
