// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWeaponComponent.h"

void USubWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh = NewObject<UStaticMeshComponent>(this))
	{
		Mesh->RegisterComponent();
		Mesh->SetHiddenInGame(true);

		Mesh->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Mesh->SetRelativeTransform(WeaponTransform, false, nullptr, ETeleportType::TeleportPhysics);

		if (Mesh->SetStaticMesh(WeaponMesh))
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, L"Weapon Mesh Compile");
		}

	}
}

void USubWeaponComponent::Holstering_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Black, FString::Printf(TEXT("SHolstering")));
}

void USubWeaponComponent::Draw_Implementation()
{
	Hidden(false);
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