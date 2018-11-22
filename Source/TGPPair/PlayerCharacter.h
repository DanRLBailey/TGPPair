// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TGPPAIR_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Functions
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void MoveCameraX(float AxisValue);
	void MoveCameraY(float AxisValue);
	void PlayerJump();
	void FireButtonPress();
	void FireButtonRelease();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerJump();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponFire(int damage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponCharge(int damage, FVector projectileSize);


	//Variables
	FVector CurrentVelocity;
	
	/*UPROPERTY(EditAnywhere)
	USceneComponent* VisibleComponent;*/

	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float projectileDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float projectileMaxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float projectileMinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float projectileChargeTime;

	UPROPERTY(BlueprintReadOnly)
	bool isFiring;

	UPROPERTY(BlueprintReadWrite)
	bool isChargingProjectile;
};
