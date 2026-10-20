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
	if (Light->GetIsLightOn())
		Light->SetIsLightOn(false);
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
	{
		Light->SetIsLightOn(true);
	}
	Light->SetSpotLightIntensity(Light->LightMaxIntensity);
}

LightState* OnNearLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	if (Light->GameInstance->AreAllLightsOn())
		return AlwaysOnLightState::GetInstance();

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
	Light->SetSpotLightIntensity(Light->LightMaxIntensity);
}

LightState* OnLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	if (Light->GameInstance->AreAllLightsOn())
		return AlwaysOnLightState::GetInstance();

	if (Light->GetIsPlayerNear())
		return OnNearLightState::GetInstance();

	if (TimeInState >= LightTime)
		return FadingLightState::GetInstance();

	return this;
}

OnLightState* OnLightState::GetInstance()
{
	static OnLightState Instance;
	return &Instance;
}

// FADING LIGHT STATE
void FadingLightState::InState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	Light->FadeLight(TimeInState);
}

LightState* FadingLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	if (Light->GameInstance->AreAllLightsOn())
	{
		return AlwaysOnLightState::GetInstance();
	}

	if (Light->GetIsPlayerNear())
	{
		return OnNearLightState::GetInstance();
	}

	return this;
}

FadingLightState* FadingLightState::GetInstance()
{
	static FadingLightState Instance;
	return &Instance;
}

// ALWAYS ON STATE
void AlwaysOnLightState::InState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	Light->SetSpotLightIntensity(Light->LightMaxIntensity);
}

LightState* AlwaysOnLightState::NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState, bool AllLightsOn, bool IsPlayerNear)
{
	// stay here forever because they are all on
	return this;
}

AlwaysOnLightState* AlwaysOnLightState::GetInstance()
{
	static AlwaysOnLightState Instance;
	return &Instance;
}
