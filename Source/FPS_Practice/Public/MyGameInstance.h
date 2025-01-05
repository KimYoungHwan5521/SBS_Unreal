// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
class UNiagaraSystem;

UCLASS()
class FPS_PRACTICE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	static UNiagaraSystem* FleshHitEffect;
	static UNiagaraSystem* GroundHitEffect;

public:
	UMyGameInstance();
	//~UMyGameInstance();

public:
	inline static UNiagaraSystem* GetFleshHitEffect() { return FleshHitEffect; }
	inline static UNiagaraSystem* GetGroundHitEffect() { return GroundHitEffect; }

};
