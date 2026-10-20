// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AInteractiveLight;

/**
 * 
 */
class OPENWORLDMAP_API LightState
{
protected:
	LightState();
	virtual ~LightState();

public:
	virtual void InState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear) = 0;
	virtual LightState* NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear) = 0;
};


class OPENWORLDMAP_API OffLightState : public LightState
{

public:
	virtual void InState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	virtual LightState* NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	static OffLightState* GetInstance();
};


class OPENWORLDMAP_API OnNearLightState : public LightState
{

public:
	virtual void InState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	virtual LightState* NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	static OnNearLightState* GetInstance();
};


class OPENWORLDMAP_API OnLightState : public LightState
{

public:
	virtual void InState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	virtual LightState* NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	static OnLightState* GetInstance();
};


class OPENWORLDMAP_API FadingLightState : public LightState
{

public:
	virtual void InState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	virtual LightState* NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	static FadingLightState* GetInstance();
};


class OPENWORLDMAP_API AlwaysOnLightState : public LightState
{

public:
	virtual void InState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	virtual LightState* NextState(AInteractiveLight* Light, float DeltaTime, float TimeInState,
		bool AllLightsOn, bool IsPlayerNear);
	static AlwaysOnLightState* GetInstance();
};