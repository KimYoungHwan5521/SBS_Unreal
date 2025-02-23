// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/KillLogWidget.h"
#include "Animation/WidgetAnimation.h"

#include "Components/TextBlock.h"

void UKillLogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EndEvent.BindDynamic(this, &UKillLogWidget::RemoveKillLog);

	BindToAnimationFinished(KillLogAnimation, EndEvent);
	
	PlayAnimation(KillLogAnimation);
}


void UKillLogWidget::BindName(const FText& KillerName, const FText& VictimName)
{
	FString CombinedString = KillerName.ToString() + TEXT(" has killed ") + VictimName.ToString();
	Kill_Display->SetText(FText::FromString(CombinedString));
}