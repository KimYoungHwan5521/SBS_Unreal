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
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector DamageDirection;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UKillLogWidget> KillLogClass;

protected:
	// Transient : 임시 변수 -> 직렬화 해제
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetAnimation> Anim_EnemyHit;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetAnimation> Anim_EnemyHit_Critical;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetAnimation> Anim_Be_Hit;
	
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
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UVerticalBox> VB_Kill_Log;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void HitAnimation(bool bIsCritical, bool bIsDead);
	virtual void HitAnimation_Implementation(bool bIsCritical, bool bIsDead);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Animation")
	void DamageAnimation(bool bIsCritical, FVector Direction);
	virtual void DamageAnimation_Implementation(bool bIsCritical, FVector Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KillLog")
	void ShowKillLog(const FText& KillerName, const FText& VictimName);
	virtual void ShowKillLog_Implementation(const FText& KillerName, const FText& VictimName);

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
