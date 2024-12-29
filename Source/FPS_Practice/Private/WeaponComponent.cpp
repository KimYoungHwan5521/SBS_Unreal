// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::Holstering_Implementation()
{

}

void UWeaponComponent::Draw_Implementation()
{

}

void UWeaponComponent::Reload_Implementation()
{

}

void UWeaponComponent::Shot_Implementation(FVector ShotLocation)
{
	// LineTrace
	// 유니티의 RayCast
	// 언리얼의 Trace의 특징 : 물체를 들고 지우개로 지우는 것처럼 싹 밀어감
	// Trace Channel : 탐지 범위
	FHitResult Hit;
	FCollisionQueryParams ShotQueryParams;
	ShotQueryParams.AddIgnoredActor(GetOwner());

	// 컴포넌트의 오너 : 컴포넌트를 소유하고있는 객체(Actor)
	//						간 -> 이식 받았으면 오너 변경
	// 액터의 오너 : 해당 액터를 소유하는 액터
	//						하인 -> 가주가 죽으면 상속 / 매매, 탈취 : 직접 조정하는 형식

	// Owner의 개념 : 내가 네트워크 게임에서 이 오브젝트를 다룰 수 있는 소유권을 가지고 있는가?

	if (GetWorld()->LineTraceSingleByChannel(Hit, GetComponentLocation() + MuzzleOffset, ShotLocation, ECollisionChannel::ECC_Visibility, ShotQueryParams))
	{
		//Hit.GetActor()->TakeDamage();
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, AActor::GetDebugName(Hit.GetActor()));

		//나이아가라 시스템 만들기
		//																						FindLookAtRotation : 월드에 존재하는 사물을 바라봄
		//																											(0, 0, 0)에 있는 것을 보자
		//																						FindRelativeLookAtRotation : 탄젠트 방향을 나타내는 벡터
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TestEffects, Hit.Location, UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, Hit.Normal));

	}
	
}