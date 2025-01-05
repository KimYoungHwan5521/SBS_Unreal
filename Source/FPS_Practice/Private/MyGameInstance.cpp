// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "NiagaraSystem.h"

UNiagaraSystem* UMyGameInstance::GroundHitEffect;
UNiagaraSystem* UMyGameInstance::FleshHitEffect;

UMyGameInstance::UMyGameInstance()
{
	// �Լ� ���� static : �� �Լ� �ȿ����� �� �� �ִ� static 
	// �� �Լ��� �� ��° ȣ�� �� ������ ���� ��������� ����
	// �𸮾��� "���� ���"�� ã�� ���� ������ ���尡 ���� ���� �Ǵ� ���� ������ ��!
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FleshHitFinder(TEXT("/Game/Niagara/NS_BulletHitBleed"));
	if (FleshHitFinder.Succeeded())
	{
		FleshHitEffect = FleshHitFinder.Object;
		// UE_LOG
		//				Verbosity
		//			    Log			: ������ ��·α׿� ���(�ܼ� ��� x) (���)
		//			    Warning		: ���! ū���� �ȳ����� �� ���ɼ��� ���� (�����)
		//			    Error		: ū�ϳ� (������)
		//			    Display		: �ְܼ� �α����� ����� ��� ���� (���)
		//			    Fatal		: ġ������ ���� �߻�! -> ����
		//			    Verbose		: ���� ���� -> �ڼ��� �˷��ַ�
		//			    VeryVerbose	: ���� ���� ���� -> �� �� �ڼ��� �˷��ַ�
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