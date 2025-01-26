// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "FPSInGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PRACTICE_API UFPSInGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// 이 위젯은 실제 위젯에 연결되어있음
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UImage> IMG_Portrait;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UProgressBar> PB_HPBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UTextBlock> CurrentHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UTextBlock> MaxHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UImage> IMG_WeaponImage;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UTextBlock> WeaponName;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UTextBlock> CurrentMagazine;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UTextBlock> MagazineCapacity;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Status")
	void ShowHealth(float CurrentHPf, float MaxHPf);
	virtual void ShowHealth_Implementation(float CurrentHPf, float MaxHPf);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Status")
	void ShowAmmo(int CurrentAmmof, int MaxAmmof);
	virtual void ShowAmmo_Implementation(int CurrentAmmof, int MaxAmmof);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Status")
	void ShowPortrait(const FSlateBrush& WantBrush);
	virtual void ShowPortrait_Implementation(const FSlateBrush& WantBrush);

	// FString : 맘대로 바꿀 수 있는 진짜 글자
	// FText : UI에 표시하기 위한 글자
	// FName : 검색을 위한 글자
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Status")
	void ShowGunName(const FText& NewName);
	virtual void ShowGunName_Implementation(const FText& NewName);
};
