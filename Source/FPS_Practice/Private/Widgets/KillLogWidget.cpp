// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/KillLogWidget.h"
#include "Animation/WidgetAnimation.h"

void UKillLogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EndEvent.BindDynamic(this, &UKillLogWidget::RemoveKillLog);

	BindToAnimationFinished(KillLogAnimation, EndEvent);
	
	PlayAnimation(KillLogAnimation);
}