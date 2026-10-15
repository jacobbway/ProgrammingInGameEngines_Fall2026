// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveLight.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLightStateChange, bool, IsLightOn);

class USceneComponent;
class USpotLightComponent;
class UCapsuleComponent;

UCLASS()
class OPENWORLDMAP_API AInteractiveLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep,
		const FHitResult& SweepResult);

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Component")
	USceneComponent* LightRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Component")
	USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Component")
	UCapsuleComponent* TriggerZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light State")
	bool IsLightOn;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLightStateChange OnLightStateChange;

};
