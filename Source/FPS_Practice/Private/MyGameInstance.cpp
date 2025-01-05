// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "NiagaraSystem.h"

UNiagaraSystem* UMyGameInstance::GroundHitEffect;
UNiagaraSystem* UMyGameInstance::FleshHitEffect;

UMyGameInstance::UMyGameInstance()
{
	// 함수 안의 static : 이 함수 안에서만 쓸 수 있는 static 
	// 이 함수가 두 번째 호출 될 때에도 새로 만들어지지 않음
	// 언리얼이 "파일 경로"로 찾는 경우는 무조건 빌드가 끝난 직후 또는 게임 실행할 때!
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FleshHitFinder(TEXT("/Game/Niagara/NS_BulletHitBleed"));
	if (FleshHitFinder.Succeeded())
	{
		FleshHitEffect = FleshHitFinder.Object;
		// UE_LOG
		//				Verbosity
		//			    Log			: 내역을 출력로그에 출력(콘솔 출력 x) (흰색)
		//			    Warning		: 경고! 큰일은 안났지만 날 가능성이 있음 (노랑색)
		//			    Error		: 큰일남 (빨강색)
		//			    Display		: 콘솔과 로그파일 출력이 모두 진행 (흰색)
		//			    Fatal		: 치명적인 결함 발생! -> 꺼짐
		//			    Verbose		: 말이 많다 -> 자세히 알려주렴
		//			    VeryVerbose	: 말이 아주 많다 -> 좀 더 자세히 알려주렴
		UE_LOG(LogTemp, Log, TEXT("FleshHitEffect loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to load FleshHitEffect"));
	}


	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> GroundHitFinder(TEXT("/Game/Niagara/NS_BulletHit"));
	if (GroundHitFinder.Succeeded())
	{
		GroundHitEffect = GroundHitFinder.Object;
		UE_LOG(LogTemp, Log, TEXT("GroundHitEffect loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to load GroundHitEffect"));
	}

}