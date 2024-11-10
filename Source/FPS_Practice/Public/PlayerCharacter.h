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
	// meta : 메타데이터 추가 Allow Private Access : 프라이빗에 접근 가능하게 언리얼에게 오픈!
	//							[SerializableField] 같은 것
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
 	TObjectPtr<class UCameraComponent> MainCamera;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

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

};
