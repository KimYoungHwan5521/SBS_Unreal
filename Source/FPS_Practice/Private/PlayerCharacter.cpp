// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 선택 x 강요 o
	// A : Class(Actor)
	// F : Struct
	// U : Unreal Object를 상속하는 클래스
	// T : Templet
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine

	// Unity : Instantiate
	// Unreal 
	// CreateDefaultSubobject : 기본 컴포넌트 생성 : "생성자"에서 만들어져서 무조건 언리얼 엔진상에서 존재
	// NewObject : UObject를 상속받는 오브젝트를 생성할 때
	// SpawnActor : Instantiate랑 똑같음
	// 
	// 언리얼은 모든 플랫폼 모든 나라에서 실행
	// 1byte의 character로는 커버 안됨
	// 2byte의 character : L"ㅎㅇ"
	// 언리얼에서 쓰는 텍스트 : TEXT("ㅎㅇ")
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	
	MainCamera->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	// 상속받은  자식 클래스에서 변경을 허용하려면
	MainCamera->bEditableWhenInherited = true;
	// 캐릭터가 바라보는 방향 : Control Direction
	// 회전하는 방향 : Rotation
	MainCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

