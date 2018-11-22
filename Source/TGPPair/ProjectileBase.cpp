// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(60.0f, true);
	RootComponent = CollisionSphere;

	Movespeed = 20.0f;
	bulletDeathTimer = 0.0f;
	bulletDeathMaxTime = 2.0f;
	willDestroyItself = true;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isMoving)
	{
		AddActorLocalOffset(FVector(Movespeed, 0.0f, 0.0f));
		bulletDeathTimer += DeltaTime;

		if (bulletDeathTimer >= bulletDeathMaxTime && willDestroyItself)
		{
			Destroy();
		}
	}
}

