// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSController.h"

void AFPSController::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	// 여기에는 캐릭터에 관련된 내용이 아닌 일반적인 내용의 키 바인딩!

}