// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "FPSController.h"
#include "WeaponComponent.h"
#include "MainWeaponComponent.h"
#include "SubWeaponComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���� x ���� o
	// A : Class(Actor)
	// F : Struct
	// U : Unreal Object�� ����ϴ� Ŭ����
	// T : Templet
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine

	// Unity : Instantiate
	// Unreal 
	// CreateDefaultSubobject : �⺻ ������Ʈ ���� : "������"���� ��������� ������ �𸮾� �����󿡼� ����
	// NewObject : UObject�� ��ӹ޴� ������Ʈ�� ������ ��
	// SpawnActor : Instantiate�� �Ȱ���
	// 
	// �𸮾��� ��� �÷��� ��� ���󿡼� ����
	// 1byte�� character�δ� Ŀ�� �ȵ�
	// 2byte�� character : L"����"
	// �𸮾󿡼� ���� �ؽ�Ʈ : TEXT("����")
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	
	MainCamera->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	// ��ӹ���  �ڽ� Ŭ�������� ������ ����Ϸ���
	MainCamera->bEditableWhenInherited = true;
	// ĳ���Ͱ� �ٶ󺸴� ���� : Control Direction
	// ȸ���ϴ� ���� : Rotation
	MainCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//CurrentWeapon = MainWeapon = GetComponentByClass<UWeaponComponent>();
	MainWeapon = FindComponentByTag<UWeaponComponent>(TEXT("MainWeapon"));
	SubWeapon = FindComponentByTag<UWeaponComponent>(TEXT("SubWeapon"));

	ChangeWeapon(MainWeapon);
	if (CurrentWeapon == nullptr)
	{
		ChangeWeapon(SubWeapon);
	}
	
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	// ���� C++���� �θ� �θ��� ���� ����, �θ� �̸����� �ҷ��� ������
	// �����ؾ� �� �� �� ���� �״��
	Super::PossessedBy(NewController);

	// ���� �Է��� ���� ���� �� �ʼ�����
	// �Է� �׼��� �ҷ��� �� �ִ� ���� : ��Ʈ�ѷ��� "�÷��̾�" �̾�� ��
	// Dynamic_Cast : �� Ŭ������ ������ �� Ŭ������ �����ְ�, �ƴϸ� null�� ������
	// �𸮾󿡼��� Cast��� �ϸ� Dynamic_Cast�� ������.
	// asPlayer�� if������ �����ؼ�, if���� ��������! -> &&�� ||�� �Բ� ���� �Ұ���
	// Cast�ϸ� ����� �ּ� or nullptr (0) => 0��  false, 0�̿� true
	if (AFPSController* asPlayer = Cast<AFPSController>(NewController))
	{
		// �÷��̾� ��Ʈ�ѷ����� �����ý��۵��� �ִµ�, EnhancedInput ���� �ý����� ����غ���
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
			// AnimInstance : ������ �� �޽ð� �ִϸ��̼��� ������ �� �ְ� �����ִ� �ν��Ͻ�
			if (UAnimInstance* Anim = CharacterMesh->GetAnimInstance())
			{
				// C#�� delegateó��
				// ���� �־�� ��� �Լ��� �����ϰ�
				Anim->OnPlayMontageNotifyBegin.RemoveAll(this);
				// ��Ƽ���̰� �߻����� �� � �Լ��� ȣ�� ���ٱ�
				//										������ ��Լ�?
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

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �� ��Ʈ�ѷ� ��ȯ
	if (AFPSController* asFPSController = Cast<AFPSController>(Controller))
	{
		// InputComponent ������ EnhancedInputComponent�� �ִ�.
		if (UEnhancedInputComponent* asEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			//															ETriggerEvent
			//															Start :��������
			//															Ongoing : ������ �ߴµ� ���� �ߵ� �ȵ�
			//															Triggered : �ߵ� ��
			//															Canceled : Ʈ���� �Ǳ� ���� ��
			//															Completed : Ʈ���� �� �Ŀ� ��
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
	
	// ���� : Yaw
	// ���� : Pitch
	// ���� : Roll
	AddControllerYawInput(InputVector.X);
	AddControllerPitchInput(InputVector.Y);
}

void APlayerCharacter::OnMove(const FInputActionValue& Value)
{
	FVector2D InputVector  = Value.Get<FVector2D>();
	
	// inputVector�� x���� 1�̶�� -> ������
	// x���� ����
	// y���� �¿�
	// �� ĳ������ �����¿츦 �����ϴϱ� ȸ���� ����
	FRotator MyRotate = GetActorRotation();

	// ȸ������ 4x4��ķ� ��ȯ
	FRotationMatrix44d MyMatrix = FRotationMatrix(MyRotate);

	FVector RightVector = MyMatrix.GetScaledAxis(EAxis::Y);
	FVector ForwardVector = MyMatrix.GetScaledAxis(EAxis::X);

	// GEngine->AddOnScreenDebugMessage = Debug.Log
	// key : �ĺ���ȣ, ���� key�� ����ִ� �޼����� ����� �����, -1�̸� ��������� ����
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

	FVector TargetLocation = EyeLocation + EyeDirection * 1000;
	if (CurrentWeapon)
	{
		CurrentWeapon->Shot(TargetLocation);
	}
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
			// AnimInstance : ������ �� �޽ð� �ִϸ��̼��� ������ �� �ְ� �����ִ� �ν��Ͻ�
			if (UAnimInstance* Anim = CharacterMesh->GetAnimInstance())
			{
				// C#�� delegateó��
				// ���� �־�� ��� �Լ��� �����ϰ�
				Anim->OnPlayMontageNotifyBegin.RemoveAll(this);
				Anim->OnMontageBlendingOut.RemoveAll(this);
				// ��Ƽ���̰� �߻����� �� � �Լ��� ȣ�� ���ٱ�
				//										������ ��Լ�?
				Anim->OnPlayMontageNotifyBegin.AddDynamic(this, &APlayerCharacter::OnHolsterNotify);
				Anim->OnMontageBlendingOut.AddDynamic(this, &APlayerCharacter::EndHolsterAnim);
			}
			PlayAnimMontage(CurrentHolster);
		}
		return true;
	}
	return false;
}
