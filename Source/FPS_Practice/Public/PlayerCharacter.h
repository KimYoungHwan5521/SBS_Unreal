// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChange, float, CurrentHPf, float, MaxHPf);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAmmoChange, int, CurrentAmmof, int, MaxAmmof);

UCLASS()
class FPS_PRACTICE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Status")
	FText CharacterName;

protected:
	//							�������Ʈ �̺�Ʈ�� ��� ����
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Status")
	FHealthChange OnHealthChanged;
	FAmmoChange OnAmmoChange;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UFPSInGameWidget> InGameWidgetInstance = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class UFPSInGameWidget> InGameWidgetClass = nullptr;

protected:
	// ������ ���ø�����Ʈ ���� �� �ִ� �Լ��� �غ�
	//										�𸮾󿡼��� �迭 <> �̷���(����Ʈ)
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// ��ΰ� �Ȱ��� ���� �����ؼ� ����ϴ� ��Ƽ�÷��̾� �뵵�� ����
	// Replicated : �׳� ������ ����ȭ �ϴ� �� only
	// ReplicatedUsing : ������ ����ȭ �� �� �Լ��� ���ư���.
	UPROPERTY(BlueprintReadOnly, /*ReplicatedUsing = OnMoveRep,*/ Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector LastReplicatedMoveDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnHPRep, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnHPRep, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float MaxHP;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UFUNCTION()
	//virtual void OnMoveRep();
	virtual void OnHPRep();

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
	// ��Ʈ��ũ�� Ÿ�� ���� �Լ��� ��ȯ ���� ����� ��
	// Server, Client, NetMulticast
	// NetMulticast
	// Server���� ������ ��� : ��ΰ� �˰� ��
	// Client���� ������ ��� : ���θ� ��
	// 
	// Reliable : �ŷ��� �� �ִ�
	// TCP : Transmission Control Protocol ���� ���� ��������
	// UnReliable : �ŷ��� �� ����
	UFUNCTION(Server, Unreliable, Category = "Weapon")
	void TriggerWeapon(FVector CameraLocation, FVector ShotLocation);
	virtual void TriggerWeapon_Implementation(FVector CameraLocation, FVector ShotLocation);

	//		  �������� ȣ�Ⱑ��, �������� �������̵� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, category = "Weapon")
	bool ChangeWeapon(class UWeaponComponent* newWeapon);
	//						_Implementation : �������� �������̵� ���� ������ �� �Լ� ����
	virtual bool ChangeWeapon_Implementation(class UWeaponComponent* newWeapon);

	UFUNCTION(Client, Unreliable, Category = "Animation")
	void HitTrigger(FVector HitLocation, float Damage, bool bIsCritical, bool bIsDead);
	virtual void HitTrigger_Implementation(FVector HitLocation, float Damage, bool bIsCritical, bool bIsDead);

	UFUNCTION(Client, Unreliable, Category = "Animation")
	void DamageTrigger(FVector HitLocation, float Damage, bool bIsCritical, bool bIsDead);
	virtual void DamageTrigger_Implementation(FVector HitLocation, float Damage, bool bIsCritical, bool bIsDead);

	UFUNCTION(NetMulticast, Reliable, Category = "Score")
	void KillNotify(APlayerCharacter* DamageCauser, APlayerCharacter* Victim);
	void KillNotify_Implementation(APlayerCharacter* DamageCauser, APlayerCharacter* Victim);

protected:
	virtual float InternalTakePointDamage(float Damage, struct FPointDamageEvent const& PointDamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};
