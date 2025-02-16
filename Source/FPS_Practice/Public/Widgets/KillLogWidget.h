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

	FWidgetAnimationDynamicEvent EndEvent;

protected:
	// 액터가 처음 시작 될 때 : BeginPlay
	// 위젯이 청므 시작 될 때 : Construct
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void RemoveKillLog() { RemoveFromParent(); }
};
