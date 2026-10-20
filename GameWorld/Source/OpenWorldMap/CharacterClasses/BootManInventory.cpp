// Fill out your copyright notice in the Description page of Project Settings.


#include "BootManInventory.h"
#include "CollectibleClassess/SwordModel.h"

UBootManInventory::UBootManInventory()
{
}

void UBootManInventory::AddSword(const FSwordModel& Sword)
{
	Swords.Add(Sword);
	OnSwordNumberChanged.Broadcast(Swords.Num());
}


int32 UBootManInventory::GetNumberOfSwords()
{
	if(!Swords.IsEmpty())
		return Swords.Num();
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No swords in inventory"));
		return 0;
	}
}

FSwordModel UBootManInventory::GetSwordByID(int32 SwordID) const
{	
	for (const FSwordModel& Sword : Swords)
	{
		if(Sword.SwordID == SwordID)
			return Sword;
	}

	return FSwordModel();
}

void UBootManInventory::RemoveAllSwords()
{
	Swords.Empty();
	UE_LOG(LogTemp, Warning, TEXT("All swords removed from inventory"))
		OnSwordNumberChanged.Broadcast(Swords.Num());
}
