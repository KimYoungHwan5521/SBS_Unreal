// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWeaponComponent.h"

void UMainWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// 만든다는 것 : 메모리를 할당받아서 값을 채워 넣는 것
	// 언리얼에서 제일 두려워 하는 것 : 메모리 누수
	// 언리얼에서 메모리 누수를 어떻게 관리할까?
	// 내가 가지고있는 오브젝트는 나만 관리 할 수 있음.
	// 언리얼에서는 오브젝트를 관리할 "주인"을 정의하게 되어있다. -> 언리얼에서 직접 관리하는 액터
	if (Mesh = NewObject<UStaticMeshComponent>(this))
	{
		// 등록하기
		Mesh->RegisterComponent();

		Mesh->SetHiddenInGame(true);

		Mesh->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

		// 액터의 위치를 옮기는 것		SetActorLocation
		// 컴포넌트의 위치를 옮기는 것	SetWorldLocation	SetRelativeLocation
		//			  회전, 크기까지	SetWorldTransform	SetRelativeTransform
		//													Relative = 유니티의 Local
		//															ETeleportType : 속도를 초기화 할지 안할지
		Mesh->SetRelativeTransform(WeaponTransform, false, nullptr, ETeleportType::TeleportPhysics);

		// 모양 넣어주기
		if(Mesh->SetStaticMesh(WeaponMesh))
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, L"Weapon Mesh Compile");
		}

	}
}

void UMainWeaponComponent::Holstering_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Black, FString::Printf(TEXT("MHolstering")));
}

void UMainWeaponComponent::Draw_Implementation()
{

	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Black, FString::Printf(TEXT("MDraw")));
}

void UMainWeaponComponent::Reload_Implementation()
{
	GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Black, FString::Printf(TEXT("MReload")));

}

void UMainWeaponComponent::Shot_Implementation(FVector CameraLocation, FVector ShotLocation)
{
	// in CPP -> 부모를 이름으로 부름
	// UWeaponComponent::Shot(ShotLocation);
	// in Unreal -> 부모를 Super라고 부름
	Super::Shot_Implementation(CameraLocation, ShotLocation);
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Black, FString::Printf(TEXT("MShot")));
}

void UMainWeaponComponent::Hidden_Implementation(bool bIsHidden)
{
	Mesh->SetHiddenInGame(bIsHidden);
}