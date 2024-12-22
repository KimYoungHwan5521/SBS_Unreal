// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Components/PrimitiveComponent.h"

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
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetComponentLocation() + MuzzleOffset, ShotLocation, ECollisionChannel::ECC_Visibility))
	{
		//Hit.GetActor()->TakeDamage();
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, AActor::GetDebugName(Hit.GetActor()));

		//나이아가라 시스템 만들기
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TestEffects, Hit.Location);
	}
	
}