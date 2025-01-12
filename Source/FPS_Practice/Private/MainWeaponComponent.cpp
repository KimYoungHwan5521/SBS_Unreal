// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWeaponComponent.h"

void UMainWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ����ٴ� �� : �޸𸮸� �Ҵ�޾Ƽ� ���� ä�� �ִ� ��
	// �𸮾󿡼� ���� �η��� �ϴ� �� : �޸� ����
	// �𸮾󿡼� �޸� ������ ��� �����ұ�?
	// ���� �������ִ� ������Ʈ�� ���� ���� �� �� ����.
	// �𸮾󿡼��� ������Ʈ�� ������ "����"�� �����ϰ� �Ǿ��ִ�. -> �𸮾󿡼� ���� �����ϴ� ����
	if (Mesh = NewObject<UStaticMeshComponent>(this))
	{
		// ����ϱ�
		Mesh->RegisterComponent();

		Mesh->SetHiddenInGame(true);

		Mesh->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

		// ������ ��ġ�� �ű�� ��		SetActorLocation
		// ������Ʈ�� ��ġ�� �ű�� ��	SetWorldLocation	SetRelativeLocation
		//			  ȸ��, ũ�����	SetWorldTransform	SetRelativeTransform
		//													Relative = ����Ƽ�� Local
		//															ETeleportType : �ӵ��� �ʱ�ȭ ���� ������
		Mesh->SetRelativeTransform(WeaponTransform, false, nullptr, ETeleportType::TeleportPhysics);

		// ��� �־��ֱ�
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
	// in CPP -> �θ� �̸����� �θ�
	// UWeaponComponent::Shot(ShotLocation);
	// in Unreal -> �θ� Super��� �θ�
	Super::Shot_Implementation(CameraLocation, ShotLocation);
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Black, FString::Printf(TEXT("MShot")));
}

void UMainWeaponComponent::Hidden_Implementation(bool bIsHidden)
{
	Mesh->SetHiddenInGame(bIsHidden);
}