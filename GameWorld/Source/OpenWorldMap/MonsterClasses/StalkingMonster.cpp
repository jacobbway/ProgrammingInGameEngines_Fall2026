// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkingMonster.h"
#include "GameModeClasses/CollectionGameInstance.h"
#include "CharacterClasses/BootCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AStalkingMonster::AStalkingMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Stalker Created"))

	SnailRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SnailRoot"));
	RootComponent = SnailRoot;

	SnailZone = CreateDefaultSubobject<USphereComponent>(TEXT("SnailZone"));
	SnailZone->SetupAttachment(RootComponent);
	SnailZone->SetCollisionProfileName(TEXT("Snailed"));
	SnailZone->InitSphereRadius(10.0f);

	SnailForward = CreateDefaultSubobject<UArrowComponent>(TEXT("SnailForward"));
	SnailForward->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStalkingMonster::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, TEXT("Snail Begin Play"));

	UCollectionGameInstance* GameInstance = GetWorld()->GetGameInstance<UCollectionGameInstance>();
	if (GameInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, TEXT("Snail Added to Game Instance"));
		GameInstance->AddSnail(this);
	}
}

// Called every frame
void AStalkingMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsPlayerLooking())
	{
		RotateToPlayer(DeltaTime);
		MoveToPlayer(DeltaTime);
	}
}

bool AStalkingMonster::IsPlayerLooking()
{
	//UE_LOG(LogTemp, Warning, TEXT("ENTERED IS PLAYER LOOKING"))
	APlayerController* BootController = GetWorld()->GetFirstPlayerController();
	
	if (BootController && BootController->PlayerCameraManager)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ENTERED IS PLAYER LOOKING BOOT CONTROLLER"))
		FVector BootCamera = BootController->PlayerCameraManager->GetCameraLocation();
		FVector BootForward = BootController->PlayerCameraManager->GetCameraRotation().Vector();

		FVector DirectionToBoot = (GetActorLocation() - BootCamera).GetSafeNormal();

		float DotResult = FVector::DotProduct(BootForward, DirectionToBoot); // should convert to degrees
		
		if (DotResult >= PlayerFOV)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ENTERED IS PLAYER LOOKING YES LOOKING"))
			return true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Bad Return False in IsPlayerLooking"))
	}
	return false;
}

void AStalkingMonster::RotateToPlayer(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("ROTATING TO PLAYER"))

	FVector StartPos = this->GetActorLocation();

	// vector to player
	UCollectionGameInstance* Game =
		GetWorld()->GetGameInstanceChecked<UCollectionGameInstance>();
	FVector ToPlayer;
	ToPlayer = Game->GetPlayer()->GetActorLocation() - StartPos;
	ToPlayer.Z = 0.0f;

	if (ToPlayer.Length() <= MinDistance)
		return;

	ToPlayer.Normalize();

	if (!SnailForward)
		return;

	// Forward Vector
	FVector Forward = SnailForward->GetForwardVector();
	Forward.Z = 0.0f;
	Forward.Normalize();

	float Dot = Forward.Dot(ToPlayer);
	float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));
	float AngleToTurn = FMath::ClampAngle(TurnSpeed * DeltaTime, 0.0f, Angle);

	//UE_LOG(LogTemp, Warning, TEXT("Turn Angle: %3.2f Angle: %3.2f"), TurnSpeed * DeltaTime, Angle)

	FVector Cross = Forward.Cross(ToPlayer);
	if (Cross.Z < 0)
		AngleToTurn *= -1;

	FQuat Turn(GetActorRotation().Add(0.0f, AngleToTurn, 0.0f));
	SetActorRotation(Turn);
}

void AStalkingMonster::MoveToPlayer(float DeltaTime)
{
	UCollectionGameInstance* Game =
		GetWorld()->GetGameInstanceChecked<UCollectionGameInstance>();
	MoveTo(DeltaTime, Game->GetPlayer()->GetActorLocation());
}

void AStalkingMonster::MoveTo(float DeltaTime, FVector Location)
{
	FVector StartPos = GetActorLocation();
	FVector ToLocation = Location - StartPos;

	float TotalDistance = ToLocation.Size2D(); 

	if (TotalDistance <= MinDistance || TotalDistance == 0.0f)
		return;

	float Distance = FMath::Clamp(MoveSpeed * DeltaTime, 0.0f, TotalDistance);

	ToLocation.Z = 0.0f;
	ToLocation.Normalize();
	FVector FlatDelta = ToLocation * Distance;

	FHitResult GroundHit;
	FVector TraceStart = StartPos + FlatDelta + FVector(0.f, 0.f, 50.f); 
	FVector TraceEnd = TraceStart - FVector(0.f, 0.f, 200.f);            

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(GroundHit, TraceStart, TraceEnd, ECC_Visibility, Params))
	{
		FlatDelta = FVector::VectorPlaneProject(FlatDelta, GroundHit.Normal);
	}

	FHitResult MoveHit;
	AddActorWorldOffset(FlatDelta, true, &MoveHit);
}
