// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"
#include "PlayerCharacter.h"
#include "FPSController.h"

AInGameMode::AInGameMode()
{
	// ������ ã��ʹٸ�  ��θ� ã�ƾ��Ѵ�.
	// ConstructorHelpers : ������ �����ڿ����� �� �� �ִ� ��η� ���ã�� Ŭ����

	// static : �ν��Ͻ��� ��� ���� �ƴ϶� ���α׷� �������� �����ϴ� ��� ����
	static ConstructorHelpers::FClassFinder<ACharacter> CharacterFinder(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	if (CharacterFinder.Succeeded()) DefaultPawnClass = CharacterFinder.Class;

	static ConstructorHelpers::FClassFinder<AController> ControllerFinder(TEXT("/Game/Blueprints/BP_FPSController"));
	PlayerControllerClass = ControllerFinder.Class;
	
}
