// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWeaponComponent.h"


void USubWeaponComponent::Holstering_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Black, FString::Printf(TEXT("SHolstering")));
}

void USubWeaponComponent::Draw_Implementation()
{
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Black, FString::Printf(TEXT("SDraw")));
}

void USubWeaponComponent::Reload_Implementation()
{
	GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Black, FString::Printf(TEXT("SReload")));
}

void USubWeaponComponent::Shot_Implementation(FVector ShotLocation)
{
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Black, FString::Printf(TEXT("SShot")));
}