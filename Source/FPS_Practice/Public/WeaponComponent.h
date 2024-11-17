// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_PRACTICE_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Blueprint에서도 Holstering을 맘대로 오버라이드 할 수 있도록 
	// BlueprintCallable : 블루프린트에서 함수 호출 가능
	// BlueprintGetter : 블루프린트에서 값만 get 가능
	// BlueprintPure : const 함수로 취급
	// BlueprintImplementableEvent : 블루프린트에서 함수를 만드세요
	// BluprintNativeEvent : 블루프린트에서 함수를 만들 수 있는데, 안 만들면 C++로 실행
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Holstering();
	// Func_Implementation()을 만들어줘야됨!
	virtual void Holstering_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Draw();
	virtual void Draw_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Reload();
	virtual void Reload_Implementation();
		
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void Shot(FVector ShotLocation);
	virtual void Shot_Implementation(FVector ShotLocation);

};
