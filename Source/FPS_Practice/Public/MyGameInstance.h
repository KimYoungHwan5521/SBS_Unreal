// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PRACTICE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	static class UNiagaraSystem* FleshHitEffect;
	static class UNiagaraSystem* GroundHitEffect;

public:
	UMyGameInstance();
	~UMyGameInstance();
};
