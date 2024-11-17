// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWeaponComponent.h"

void UMainWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Mesh = NewObject<UStaticMeshComponent>();
	Mesh->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

	Mesh->SetStaticMesh(WeaponMesh);
}

void UMainWeaponComponent::Holstering_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Black, FString::Printf(TEXT("MHolstering")));
}

void UMainWeaponComponent::Draw_Implementation()
{
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Black, FString::Printf(TEXT("MDraw")));

}

void UMainWeaponComponent::Reload_Implementation()
{
	GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Black, FString::Printf(TEXT("MReload")));

}

void UMainWeaponComponent::Shot_Implementation(FVector ShotLocation)
{
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Black, FString::Printf(TEXT("MShot")));

}