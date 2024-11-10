// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"
#include "PlayerCharacter.h"
#include "FPSController.h"

AInGameMode::AInGameMode()
{
	// 파일을 찾고싶다면  경로를 찾아야한다.
	// ConstructorHelpers : 무조건 생성자에서만 쓸 수 있는 경로로 대상찾는 클래스

	// static : 인스턴스에 담는 것이 아니라 프로그램 전역에서 관리하는 대상 변수
	static ConstructorHelpers::FClassFinder<ACharacter> CharacterFinder(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	if (CharacterFinder.Succeeded()) DefaultPawnClass = CharacterFinder.Class;

	static ConstructorHelpers::FClassFinder<AController> ControllerFinder(TEXT("/Game/Blueprints/BP_FPSController"));
	PlayerControllerClass = ControllerFinder.Class;
	
}
