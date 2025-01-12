// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "WeaponComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_PRACTICE_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offset")
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UNiagaraSystem* TestEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UNiagaraSystem* CharacterHitEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DrawMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> HolsterMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> FireMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> ReloadMontage;

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Blueprint������ Holstering�� ����� �������̵� �� �� �ֵ��� 
	// BlueprintCallable : �������Ʈ���� �Լ� ȣ�� ����
	// BlueprintGetter : �������Ʈ���� ���� get ����
	// BlueprintPure : const �Լ��� ���
	// BlueprintImplementableEvent : �������Ʈ���� �Լ��� ���弼��
	// BluprintNativeEvent : �������Ʈ���� �Լ��� ���� �� �ִµ�, �� ����� C++�� ����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Holstering();
	// Func_Implementation()�� �������ߵ�!
	virtual void Holstering_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Draw();
	virtual void Draw_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Reload();
	virtual void Reload_Implementation();
		
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Shot(FVector CameraLocation, FVector ShotLocation);
	virtual void Shot_Implementation(FVector CameraLocation, FVector ShotLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Hidden(bool bIsHidden);
	virtual void Hidden_Implementation(bool bIsHidden) {};

	UFUNCTION(NetMulticast, Unreliable, Category = "Effect")
	void HitEffect(class UNiagaraSystem* WantEffect, FHitResult Hit);
	virtual void HitEffect_Implementation(class UNiagaraSystem* WantEffect, FHitResult Hit);
};
