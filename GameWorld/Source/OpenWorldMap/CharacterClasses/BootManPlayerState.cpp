// Fill out your copyright notice in the Description page of Project Settings.


#include "BootManPlayerState.h"
#include "BootManInventory.h"

ABootManPlayerState::ABootManPlayerState()
{
	PlayerInventory = CreateDefaultSubobject<UBootManInventory>(TEXT("BootManInventory"));
}

