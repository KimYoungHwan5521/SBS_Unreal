// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FPS_PRACTICE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	// meta : ��Ÿ������ �߰� Allow Private Access : �����̺��� ���� �����ϰ� �𸮾󿡰� ����!
	//							[SerializableField] ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
 	TObjectPtr<class UCameraComponent> MainCamera;

	// StaticMeshComponent -> ���밡 ���� -> �߾Ӽ��� ��Ʈ��
	// SkeletalMeshComponent -> ���밡 ���� -> �߾Ӽ��� ��ũ��
	// �� �� ���� ����� �� �ְ� -> UPrimitiveComponent : ���� ���󿡼� �޽ø� �����ϴ� ������Ʈ
	// "����"��� �ý����� Ŀ���� ������Ʈ �����!
	// ������ �⺻���� ���ؼ� ���ð��� ���⸶�� ������ �� ����. -> �Լ��� �������̵� �ؼ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UWeaponComponent> MainWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UWeaponComponent> SubWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UWeaponComponent> CurrentWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UWeaponComponent> OldWeapon = nullptr;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	virtual void EndHolsterAnim(UAnimMontage* AnimMontage, bool bInterrupted);
	// �ִϸ��̼� ��Ÿ�� �����߿� Ư�� Ÿ�̹��� ���� ���
	// ex : ������ ����߿� �������� �Ϸ�Ǵ� Ÿ�̹�
	//					  FName : �𸮾󿡼� ����� �˻��ϴ� �뵵�� ����ϴ� ���ڿ�
	UFUNCTION()
	virtual void OnHolsterNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	UFUNCTION()
	virtual void EndDrawAnim(UAnimMontage* AnimMontage, bool bInterrupted);
	UFUNCTION()
	virtual void OnDrawNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	virtual void OnLook(const FInputActionValue& Value);
	UFUNCTION()
	virtual void OnMove(const FInputActionValue& Value);
	UFUNCTION()
	virtual void OnRun(const FInputActionValue& Value);
	UFUNCTION()
	virtual void OnJump();
	UFUNCTION()
	virtual void OnShot();
	UFUNCTION()
	virtual void OnReload();
	UFUNCTION()
	virtual void OnMainWeapon();
	UFUNCTION()
	virtual void OnSubWeapon();
	UFUNCTION()
	virtual void OnInteraction();

public:
	//		  �������� ȣ�Ⱑ��, �������� �������̵� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, category = "Weapon")
	bool ChangeWeapon(class UWeaponComponent* newWeapon);
	//						_Implementation : �������� �������̵� ���� ������ �� �Լ� ����
	virtual bool ChangeWeapon_Implementation(class UWeaponComponent* newWeapon);

};
