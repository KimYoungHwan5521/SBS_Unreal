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

	// ���⿡�� ĳ���Ϳ� ���õ� ������ �ƴ� �Ϲ����� ������ Ű ���ε�!

}

void AFPSController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (IsValid(InPawn))
	{
		// �� ��ǻ�Ϳ��� �����ϰ� �ִ� �÷��̾���
		if (IsLocalPlayerController())
		{
			InPawn->PossessedBy(this);
		}
	}
}