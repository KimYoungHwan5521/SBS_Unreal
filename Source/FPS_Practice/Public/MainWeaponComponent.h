// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "MainWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPS_PRACTICE_API UMainWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

protected:
	// 모양을 렌더링 해줄 기능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Mesh;

	// 등록할 모양
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	FTransform WeaponTransform;
protected:
	virtual void BeginPlay() override;

public:

	virtual void Holstering_Implementation() override;
	virtual void Draw_Implementation() override;
	virtual void Reload_Implementation() override;
	virtual void Shot_Implementation(FVector CameraLocation, FVector ShotLocation) override;
	virtual void Hidden_Implementation(bool bIsHidden) override;

};
