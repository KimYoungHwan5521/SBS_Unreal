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
	//							블루프린트 이벤트도 등록 가능
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Status")
	FHealthChange OnHealthChanged;
	FAmmoChange OnAmmoChange;

private:
	// meta : 메타데이터 추가 Allow Private Access : 프라이빗에 접근 가능하게 언리얼에게 오픈!
	//							[SerializableField] 같은 것
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
 	TObjectPtr<class UCameraComponent> MainCamera;

	// StaticMeshComponent -> 뼈대가 없음 -> 중앙선이 민트색
	// SkeletalMeshComponent -> 뼈대가 있음 -> 중앙선이 핑크색
	// 이 두 개를 사용할 수 있게 -> UPrimitiveComponent : 실제 세상에서 메시를 렌더하는 컴포넌트
	// "무기"라는 시스템의 커스텀 컴포넌트 만들기!
	// 무기의 기본값을 통해서 세팅값을 무기마다 설정할 수 있음. -> 함수도 오버라이딩 해서 쓰면
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
	// 변수를 리플리케이트 받을 수 있는 함수를 준비
	//										언리얼에서는 배열 <> 이렇게(리스트)
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// 모두가 똑같은 값을 복제해서 사용하는 멀티플레이어 용도의 변수
	// Replicated : 그냥 변수를 동기화 하는 것 only
	// ReplicatedUsing : 변수를 동기화 할 때 함수가 돌아간다.
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
	// 애니메이션 몽타주 진행중에 특정 타이밍이 오는 경우
	// ex : 재장전 모션중에 재장전이 완료되는 타이밍
	//					  FName : 언리얼에서 대상을 검색하는 용도로 사용하는 문자열
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
	// 네트워크를 타고 가는 함수는 반환 값이 없어야 함
	// Server, Client, NetMulticast
	// NetMulticast
	// Server에서 실행한 경우 : 모두가 알게 됨
	// Client에서 실행한 경우 : 본인만 앎
	// 
	// Reliable : 신뢰할 수 있는
	// TCP : Transmission Control Protocol 전송 제어 프로토콜
	// UnReliable : 신뢰할 수 없는
	UFUNCTION(Server, Unreliable, Category = "Weapon")
	void TriggerWeapon(FVector CameraLocation, FVector ShotLocation);
	virtual void TriggerWeapon_Implementation(FVector CameraLocation, FVector ShotLocation);

	//		  블프에서 호출가능, 블프에서 오버라이드 가능
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, category = "Weapon")
	bool ChangeWeapon(class UWeaponComponent* newWeapon);
	//						_Implementation : 블프에서 오버라이드 하지 않으면 이 함수 실행
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
