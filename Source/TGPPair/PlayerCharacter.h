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
	void Jump();
	void FireButtonPress();
	void FireButtonRelease();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponFire();


	//Variables
	FVector CurrentVelocity;
	
	/*UPROPERTY(EditAnywhere)
	USceneComponent* VisibleComponent;*/

	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCamera;

	float weaponTimer;

	/*What is the player's fire rate?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float weaponMaxTimer;

	bool isFiring;
};
