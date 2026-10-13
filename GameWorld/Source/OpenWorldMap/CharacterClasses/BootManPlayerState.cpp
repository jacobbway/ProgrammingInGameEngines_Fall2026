// Fill out your copyright notice in the Description page of Project Settings.


#include "BootManPlayerState.h"

ABootManPlayerState::ABootManPlayerState()
{
	CollectedSwords = 0;
	OnCollected.Broadcast(this, 0, CollectedSwords);
}

void ABootManPlayerState::AddToNumSwords(int32 Swords)
{
	int32 OldSwords = CollectedSwords;
	CollectedSwords += Swords;
	UE_LOG(LogTemp, Warning, TEXT("SWORDS UPDATED %d"), CollectedSwords)
	OnCollected.Broadcast(this, OldSwords, CollectedSwords);
}