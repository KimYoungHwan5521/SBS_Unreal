// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "WeaponComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/DamageEvents.h"
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

void UWeaponComponent::Shot_Implementation(FVector CameraLocation, FVector ShotLocation)
{
	// LineTrace
	// ����Ƽ�� RayCast
	// �𸮾��� Trace�� Ư¡ : ��ü�� ��� ���찳�� ����� ��ó�� �� �о
	// Trace Channel : Ž�� ����
	FHitResult Hit;
	FCollisionQueryParams ShotQueryParams;
	ShotQueryParams.AddIgnoredActor(GetOwner());

	// ������Ʈ�� ���� : ������Ʈ�� �����ϰ��ִ� ��ü(Actor)
	//						�� -> �̽� �޾����� ���� ����
	// ������ ���� : �ش� ���͸� �����ϴ� ����
	//						���� -> ���ְ� ������ ��� / �Ÿ�, Ż�� : ���� �����ϴ� ����

	// Owner�� ���� : ���� ��Ʈ��ũ ���ӿ��� �� ������Ʈ�� �ٷ� �� �ִ� �������� ������ �ִ°�?

	if (GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, ShotLocation, ECollisionChannel::ECC_Visibility, ShotQueryParams))
	{
		//Hit.GetActor()->TakeDamage();
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, AActor::GetDebugName(Hit.GetActor()));

		if (AActor* AsActor = Hit.GetActor())
		{
			FVector ShotDirection = (Hit.Location - (GetComponentLocation() + MuzzleOffset));
			AController* Instigator = nullptr;
			if (AActor* Owner = GetOwner())
			{
				Instigator = Owner->GetInstigatorController();
			}
			// AnyDamage	: �ϰų�
			// PointDamage	: Ư���� ��ġ�� �¾Ҵ�
			// RadialDamage	: ��� ������ 
			// Instigate By
			AsActor->ReceivePointDamage(30, nullptr, Hit.Location, Hit.Normal, Hit.Component.Get(), Hit.BoneName, ShotDirection, Instigator, GetOwner(), Hit);
			FPointDamageEvent DamageEvent(30, Hit, ShotDirection, nullptr);
			AsActor->TakeDamage(30, DamageEvent, Instigator, GetOwner());
		}

		UNiagaraSystem* WantHitEffect;
		// ���� ����� ĳ���͸� FleshHitEffect, �ƴϸ� GroundHitEffect
		if (ACharacter* AsCharacter = Cast<ACharacter>(Hit.GetActor()))
		{
			WantHitEffect = UMyGameInstance::GetFleshHitEffect();
		}
		else
		{
			WantHitEffect = UMyGameInstance::GetGroundHitEffect();
		}

		HitEffect(WantHitEffect, Hit);

	}
	
}

void UWeaponComponent::HitEffect_Implementation(UNiagaraSystem * WantEffect, FHitResult Hit)
{
	if (IsValid(WantEffect))
	{
		//���̾ư��� �ý��� �����
		//																						FindLookAtRotation : ���忡 �����ϴ� �繰�� �ٶ�
		//																											(0, 0, 0)�� �ִ� ���� ����
		//																						FindRelativeLookAtRotation : ź��Ʈ ������ ��Ÿ���� ����
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), WantEffect, Hit.Location, UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, Hit.Normal));
	}
}