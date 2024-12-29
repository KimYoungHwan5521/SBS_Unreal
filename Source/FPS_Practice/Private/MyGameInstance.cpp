// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "NiagaraSystem.h"

UNiagaraSystem* UMyGameInstance::GroundHitEffect;
UNiagaraSystem* UMyGameInstance::FleshHitEffect;

UMyGameInstance::UMyGameInstance()
{
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> FleshHitFinder(TEXT("/Game/Niagara/NS_BulletHitBleed"));
	if (FleshHitFinder.Succeeded())
	{
		FleshHitEffect = FleshHitFinder.Object;
	}
}