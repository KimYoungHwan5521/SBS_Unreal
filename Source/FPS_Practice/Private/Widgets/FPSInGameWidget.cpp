// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FPSInGameWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UFPSInGameWidget::ShowHealth_Implementation(float CurrentHPf, float MaxHPf)
{
	if (MaxHPf == 0) MaxHPf = 1;
	CurrentHP->SetText(FText::AsNumber(CurrentHPf));
	MaxHP->SetText(FText::AsNumber(MaxHPf));
	PB_HPBar->SetPercent(CurrentHPf / MaxHPf);
}

void UFPSInGameWidget::ShowAmmo_Implementation(int CurrentAmmof, int MaxAmmof)
{
	CurrentMagazine->SetText(FText::Format<int, int>(FTextFormat::FromString(TEXT("{0} / {1}")), CurrentAmmof, MaxAmmof));
}

void UFPSInGameWidget::ShowPortrait_Implementation(const FSlateBrush& WantBrush)
{
	IMG_Portrait->SetBrush(WantBrush);
}

void UFPSInGameWidget::ShowGunName_Implementation(const FText& NewName)
{
	WeaponName->SetText(NewName);
}

void UFPSInGameWidget::HitAnimation_Implementation(bool bIsCritical)
{
	PlayAnimation(bIsCritical ? Anim_EnemyHit_Critical : Anim_EnemyHit, 0);
}

void UFPSInGameWidget::DamageAnimation_Implementation(bool bIsCritical, FVector Direction)
{
	PlayAnimation(bIsCritical ? Anim_Be_Hit : Anim_Be_Hit, 0);
}