// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KillLogWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PRACTICE_API UKillLogWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim, AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetAnimation> KillLogAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UTextBlock> Kill_Display;

	FWidgetAnimationDynamicEvent EndEvent;

protected:
	// ���Ͱ� ó�� ���� �� �� : BeginPlay
	// ������ û�� ���� �� �� : Construct
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void RemoveKillLog() { RemoveFromParent(); }

	UFUNCTION(BlueprintCallable, Category = "Log")
	void BindName(const FText& KillerName, const FText& VictimName);
};
