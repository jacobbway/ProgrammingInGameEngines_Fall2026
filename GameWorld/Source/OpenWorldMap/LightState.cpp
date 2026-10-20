// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveLight.h"
#include "LightState.h"

LightState::LightState()
{
}

LightState::~LightState()
{
}

// OFF LIGHT STATE
void OffLightState::InState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	// Do Nothing Stay Off
}

LightState* OffLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	if (Light->GetIsPlayerNear())
		return OnNearLightState::GetInstance();

	return this;
}

OffLightState* OffLightState::GetInstance()
{
	static OffLightState Instance;
	return &Instance;
}

// ON NEAR LIGHT STATE
void OnNearLightState::InState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	if (!Light->GetIsLightOn())
		Light->SetIsLightOn(true);
}

LightState* OnNearLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	if()

	if (!Light->GetIsPlayerNear())
		return OnLightState::GetInstance();


	return this;
}

OnNearLightState* OnNearLightState::GetInstance()
{
	static OnNearLightState Instance;
	return &Instance;
}

// ON LIGHT STATE
void OnLightState::InState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
}

LightState* OnLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
}

OnLightState* OnLightState::GetInstance()
{
	static OnLightState Instance;
	return &Instance;
}

// FADING LIGHT STATE
void FadingLightState::InState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
}

LightState* FadingLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
}

FadingLightState* FadingLightState::GetInstance()
{
	static FadingLightState Instance;
	return &Instance;
}

// ALWAYS ON STATE
void AlwaysOnLightState::InState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
}

LightState* AlwaysOnLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
}

AlwaysOnLightState* AlwaysOnLightState::GetInstance()
{
	static AlwaysOnLightState Instance;
	return &Instance;
}
