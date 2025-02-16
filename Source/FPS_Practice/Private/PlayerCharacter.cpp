// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "FPSController.h"
#include "WeaponComponent.h"
#include "MainWeaponComponent.h"
#include "SubWeaponComponent.h"

#include "Widgets/FPSInGameWidget.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "GameFramework/PawnMovementComponent.h"

#include "Net/UnrealNetwork.h"

#include "Engine/DamageEvents.h"

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

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 복제라는 것은 기준이 다양하다.
	// 일단 복제를 해보죠
	//						이 클래스의,		이 변수를,					이 기준으로
	// COND
	//		_InitialOnly		: 처음 한 번만 정보를 받기
	//		_OwnerOnly			: 이 액터의 Owner 한테만
	//		_SkipOwner			: Owner 빼고 나머지 한테만
	//		_SimulatedOnly		: 시뮬레이션 용 액터
	//		_AutonomousOnly		: 자율 액터
	//		_SimulatedOrPhysics	: 시뮬레이션 용 또는 물리 객체
	//		_InitialOrOwner		: 처음 한 번, Owner는 계속
	//		_Custom				: SetCustomActiveOverride 이거를 키거나 끄면서 조절
	//DOREPLIFETIME_CONDITION(APlayerCharacter, LastReplicatedMoveDirection, COND_OwnerOnly);
	
	// 조건 없이도 가능
	DOREPLIFETIME(APlayerCharacter, CurrentHP);
	DOREPLIFETIME(APlayerCharacter, MaxHP);
}

//void APlayerCharacter::OnMoveRep()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), LastReplicatedMoveDirection.Length()));
//}

void APlayerCharacter::OnHPRep()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%f"), CurrentHP));
	if (IsValid(InGameWidgetInstance))
	{
		OnHealthChanged.Broadcast(CurrentHP, MaxHP);
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//CurrentWeapon = MainWeapon = GetComponentByClass<UWeaponComponent>();
	MainWeapon = FindComponentByTag<UWeaponComponent>(TEXT("MainWeapon"));
	/*if (IsValid(MainWeapon))
	{
		MainWeapon->SetIsReplicated(true);
	}*/
	SubWeapon = FindComponentByTag<UWeaponComponent>(TEXT("SubWeapon"));

	ChangeWeapon(MainWeapon);
	if (CurrentWeapon == nullptr)
	{
		ChangeWeapon(SubWeapon);
	}
	//CurrentHP = 100;

	if (AController* MyController = GetController())
	{
		if (MyController->IsLocalPlayerController())
		{
			InGameWidgetInstance = CreateWidget<UFPSInGameWidget>(GetWorld(), InGameWidgetClass);
			if (IsValid(InGameWidgetInstance))
			{
				// AddToPlayerScreen : 플레이어 화면에 띄우기
				// AddToViewport : 화면에 띄우기
				InGameWidgetInstance->AddToPlayerScreen();
				OnHealthChanged.AddDynamic(InGameWidgetInstance, &UFPSInGameWidget::ShowHealth);
				OnHealthChanged.Broadcast(CurrentHP, MaxHP);
			}
		}
	}

}

// 서버에서 해당 캐릭터에 새로운 컨트롤러를 부여했을 때
// 클라이언트에서는 실행x
void APlayerCharacter::PossessedBy(AController* NewController)
{
	// 원래 C++에는 부모를 부르는 말이 없고, 부모를 이름으로 불러야 했으나
	// 빙의해야 할 때 할 일은 그대로
	Super::PossessedBy(NewController);

	// 향상된 입력을 쓰고 싶을 때 필수조건
	// 입력 액션을 불러올 수 있는 상태 : 컨트롤러가 "플레이어" 이어야 함
	// Dynamic_Cast : 그 클래스가 맞으면 그 클래스로 보여주고, 아니면 null을 돌려줌
	// 언리얼에서는 Cast라고 하면 Dynamic_Cast가 나간다.
	// asPlayer를 if문에서 생성해서, if문의 지역변수! -> &&나 ||과 함께 쓰기 불가능
	// Cast하면 대상의 주소 or nullptr (0) => 0은  false, 0이외 true
	if (AFPSController* asPlayer = Cast<AFPSController>(NewController))
	{
		// 플레이어 컨트롤러에는 보조시스템들이 있는데, EnhancedInput 보조 시스템을 등록해보자
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(asPlayer->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(asPlayer->DefaultContext, 0);
		}
	}
}

void APlayerCharacter::EndHolsterAnim(UAnimMontage* AnimMontage, bool bInterrupted)
{
	if (OldWeapon != nullptr) OldWeapon->Hidden(true);
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->Draw();
		PlayAnimMontage(CurrentWeapon->DrawMontage);
		if (USkeletalMeshComponent* CharacterMesh = GetMesh())
		{
			// AnimInstance : 실제로 이 메시가 애니메이션을 진행할 수 있게 도와주는 인스턴스
			if (UAnimInstance* Anim = CharacterMesh->GetAnimInstance())
			{
				// C#의 delegate처럼
				// 전에 넣어둔 모든 함수를 제거하고
				Anim->OnPlayMontageNotifyBegin.RemoveAll(this);
				// 노티파이가 발생했을 때 어떤 함수로 호출 해줄까
				//										누구의 어떤함수?
				Anim->OnPlayMontageNotifyBegin.AddDynamic(this, &APlayerCharacter::OnDrawNotify);

				Anim->OnMontageBlendingOut.RemoveAll(this);
				Anim->OnMontageBlendingOut.AddDynamic(this, &APlayerCharacter::EndDrawAnim);
			}
		}
	}
}

void APlayerCharacter::OnHolsterNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{

}

void APlayerCharacter::EndDrawAnim(UAnimMontage* AnimMontage, bool bInterrupted)
{

}

void APlayerCharacter::OnDrawNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LastReplicatedMoveDirection = GetMovementComponent()->Velocity;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 새 컨트롤러 소환
	if (AFPSController* asFPSController = Cast<AFPSController>(Controller))
	{
		// InputComponent 하위에 EnhancedInputComponent가 있다.
		if (UEnhancedInputComponent* asEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			//															ETriggerEvent
			//															Start :누른순간
			//															Ongoing : 눌리긴 했는데 아직 발동 안됨
			//															Triggered : 발동 됨
			//															Canceled : 트리거 되기 전에 뗌
			//															Completed : 트리거 된 후에 뗌
			asEnhancedInputComponent->BindAction(asFPSController->IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::OnLook);
			asEnhancedInputComponent->BindAction(asFPSController->IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMove);
			asEnhancedInputComponent->BindAction(asFPSController->IA_Run, ETriggerEvent::Started, this, &APlayerCharacter::OnRun);
			asEnhancedInputComponent->BindAction(asFPSController->IA_Run, ETriggerEvent::Completed, this, &APlayerCharacter::OnRun);
			asEnhancedInputComponent->BindAction(asFPSController->IA_Jump, ETriggerEvent::Started, this, &APlayerCharacter::OnJump);
			asEnhancedInputComponent->BindAction(asFPSController->IA_Jump, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);
			asEnhancedInputComponent->BindAction(asFPSController->IA_Shot, ETriggerEvent::Started, this, &APlayerCharacter::OnShot);
			asEnhancedInputComponent->BindAction(asFPSController->IA_Reload, ETriggerEvent::Triggered, this, &APlayerCharacter::OnReload);
			asEnhancedInputComponent->BindAction(asFPSController->IA_MainWeapon, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMainWeapon);
			asEnhancedInputComponent->BindAction(asFPSController->IA_SubWeapon, ETriggerEvent::Triggered, this, &APlayerCharacter::OnSubWeapon);
			asEnhancedInputComponent->BindAction(asFPSController->IA_Interaction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnInteraction);
		}
	}

}
void APlayerCharacter::OnLook(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	
	// 도리 : Yaw
	// 끄덕 : Pitch
	// 갸웃 : Roll
	AddControllerYawInput(InputVector.X);
	AddControllerPitchInput(InputVector.Y);
}

void APlayerCharacter::OnMove(const FInputActionValue& Value)
{
	FVector2D InputVector  = Value.Get<FVector2D>();
	
	// inputVector의 x축이 1이라면 -> 오른쪽
	// x축은 전후
	// y축은 좌우
	// 내 캐릭터의 전후좌우를 봐야하니까 회전을 본다
	FRotator MyRotate = GetActorRotation();

	// 회전값을 4x4행렬로 변환
	FRotationMatrix44d MyMatrix = FRotationMatrix(MyRotate);

	FVector RightVector = MyMatrix.GetScaledAxis(EAxis::Y);
	FVector ForwardVector = MyMatrix.GetScaledAxis(EAxis::X);

	// GEngine->AddOnScreenDebugMessage = Debug.Log
	// key : 식별번호, 같은 key에 들어있는 메세지를 지우고 덮어씌움, -1이면 덮어씌워지지 않음
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Black, FString::Printf(TEXT("F.X : %f"), ForwardVector.X));
	GEngine->AddOnScreenDebugMessage(4, 3.0f, FColor::Black, FString::Printf(TEXT("F.Y : %f"), ForwardVector.Y));
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Black, FString::Printf(TEXT("R.X : %f"), RightVector.X));
	GEngine->AddOnScreenDebugMessage(2, 3.0f, FColor::Black, FString::Printf(TEXT("R.Y : %f"), RightVector.Y));

	AddMovementInput(RightVector * InputVector.X + ForwardVector * InputVector.Y);
}

void APlayerCharacter::OnRun(const FInputActionValue& Value)
{

}

void APlayerCharacter::OnJump()
{
	Jump();
}

void APlayerCharacter::OnShot()
{
	FVector EyeLocation = MainCamera->GetComponentLocation();
	FRotator EyeRotation = MainCamera->GetComponentRotation();
	FVector EyeDirection = EyeRotation.Vector();

	FVector TargetLocation = EyeLocation + EyeDirection * 50000.0f;
	TriggerWeapon(EyeLocation, TargetLocation);
}

void APlayerCharacter::OnReload()
{

}

void APlayerCharacter::OnMainWeapon()
{
	ChangeWeapon(MainWeapon);
}

void APlayerCharacter::OnSubWeapon()
{
	ChangeWeapon(SubWeapon);
}

void APlayerCharacter::OnInteraction()
{

}

void APlayerCharacter::TriggerWeapon_Implementation(FVector CameraLocation, FVector ShotLocation)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Shot(CameraLocation, ShotLocation);
	}

}

bool APlayerCharacter::ChangeWeapon_Implementation(UWeaponComponent* newWeapon)
{
	if (CurrentWeapon != newWeapon)
	{
		UAnimMontage* CurrentHolster = nullptr;

		if (CurrentWeapon != nullptr)
		{
			CurrentWeapon->Holstering();
			CurrentHolster = CurrentWeapon->HolsterMontage;

		}

		OldWeapon = CurrentWeapon;
		CurrentWeapon = newWeapon;

		if (USkeletalMeshComponent* CharacterMesh = GetMesh())
		{
			// AnimInstance : 실제로 이 메시가 애니메이션을 진행할 수 있게 도와주는 인스턴스
			if (UAnimInstance* Anim = CharacterMesh->GetAnimInstance())
			{
				// C#의 delegate처럼
				// 전에 넣어둔 모든 함수를 제거하고
				Anim->OnPlayMontageNotifyBegin.RemoveAll(this);
				Anim->OnMontageBlendingOut.RemoveAll(this);
				// 노티파이가 발생했을 때 어떤 함수로 호출 해줄까
				//										누구의 어떤함수?
				Anim->OnPlayMontageNotifyBegin.AddDynamic(this, &APlayerCharacter::OnHolsterNotify);
				Anim->OnMontageBlendingOut.AddDynamic(this, &APlayerCharacter::EndHolsterAnim);
			}
			PlayAnimMontage(CurrentHolster);
		}
		return true;
	}
	return false;
}

float APlayerCharacter::InternalTakePointDamage(float Damage, struct FPointDamageEvent const& PointDamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float result = Super::InternalTakePointDamage(Damage, PointDamageEvent, EventInstigator, DamageCauser);
	bool bIsCritical = false;

	if (PointDamageEvent.HitInfo.BoneName == TEXT("HEAD"))
	{
		Damage *= 2;
		bIsCritical = true;
	}

	CurrentHP -= Damage;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("HP : %f"), CurrentHP));
	OnHealthChanged.Broadcast(CurrentHP, MaxHP);

	if (APlayerController* AsPlayer = Cast<APlayerController>(EventInstigator))
	{
		if (AsPlayer->GetCharacter())
		{
			if (APlayerCharacter* AsPlayerCharacter = Cast<APlayerCharacter>(AsPlayer->GetCharacter()))
			{
				AsPlayerCharacter->HitTrigger(PointDamageEvent.HitInfo.Location, Damage, bIsCritical, CurrentHP <= 0);

			}
		}
	}
	FVector DamageDirection = FVector::ZeroVector;
	if (IsValid(DamageCauser))
	{
		DamageDirection = DamageCauser->GetActorLocation() - GetActorLocation();
		DamageDirection.GetSafeNormal2D();
	}
	DamageTrigger(DamageDirection, Damage, bIsCritical, CurrentHP <= 0);

	return result;
}

void APlayerCharacter::HitTrigger_Implementation(FVector HitLocation, float Damage, bool bIsCritical, bool bIsDead)
{
	if (IsValid(InGameWidgetInstance))
	{
		InGameWidgetInstance->HitAnimation(bIsCritical, bIsDead);
	}
}

void APlayerCharacter::DamageTrigger_Implementation(FVector HitLocation, float Damage, bool bIsCritical, bool bIsDead)
{
	if (IsValid(InGameWidgetInstance))
	{
		InGameWidgetInstance->DamageAnimation(bIsCritical, HitLocation);
	}
}