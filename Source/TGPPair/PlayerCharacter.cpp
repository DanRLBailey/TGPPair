// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 88.0f));

	// Create a camera and a visible object
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	//VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	//VisibleComponent->SetupAttachment(RootComponent);

	//Setup Variables
	isFiring = false;
	projectileMaxDamage = 1.0f;
	projectileMinDamage = 0.1f;
	projectileChargeTime = 1.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	projectileDamage = projectileMinDamage;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isFiring)
	{
		FVector size = FVector(0.01f, 0.01f, 0.01f);
		int damage = projectileDamage * 100;
		FVector projectileSize = damage * size;
		OnWeaponCharge(damage, projectileSize);

		if (isChargingProjectile)
		{
			projectileDamage += (DeltaTime / projectileChargeTime);

			if (projectileDamage >= projectileMaxDamage)
			{
				projectileDamage = projectileMaxDamage;
			}
		}
	}
	else
	{
		projectileDamage = projectileMinDamage;
		isChargingProjectile = false;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &APlayerCharacter::MoveSide);
	PlayerInputComponent->BindAxis("MouseInputX", this, &APlayerCharacter::MoveCameraX);
	PlayerInputComponent->BindAxis("MouseInputY", this, &APlayerCharacter::MoveCameraY);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::PlayerJump);
	InputComponent->BindAction("FireWeapon", IE_Pressed, this, &APlayerCharacter::FireButtonPress);
	InputComponent->BindAction("FireWeapon", IE_Released, this, &APlayerCharacter::FireButtonRelease);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		//Find forward vector
		FRotator Rotation = Controller->GetControlRotation();

		//Add movement in direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::MoveSide(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		// add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::MoveCameraX(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::MoveCameraY(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::PlayerJump()
{
	Jump();
	OnPlayerJump();
}

void APlayerCharacter::FireButtonPress()
{
	isFiring = true;
}

void APlayerCharacter::FireButtonRelease()
{
	isFiring = false;
	projectileDamage = projectileDamage * 100;
	OnWeaponFire(projectileDamage);
}