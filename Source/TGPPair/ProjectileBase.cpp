// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"
#include "Engine.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(60.0f, true);
	RootComponent = CollisionSphere;*/
	isMoving = true;
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
		Movespeed = (40.0f - (damage * 0.35));

		AddActorLocalOffset(FVector(Movespeed, 0.0f, 0.0f));
		bulletDeathTimer += DeltaTime;


		TArray<FHitResult>OutHits;
		FVector ActorLocation = GetActorLocation();
		FCollisionShape MyColSphere = FCollisionShape::MakeSphere(50.f);

		bool isHit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, ECC_WorldStatic, MyColSphere);
		if (isHit)
		{
			for (auto& Hit : OutHits)
			{
				if (GEngine)
				{
					//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, ("actor hit. %s" ,Hit.Actor->GetName()));
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit result: %s", *Hit.Actor->GetName())));
				}
				if (Hit.Actor == NULL || Hit.Actor->GetName() == "")
					continue;
				if (Hit.Actor->GetName().Contains("enemy", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					if (Hit.Actor->GetName().Equals(this->GetName(), ESearchCase::IgnoreCase))
						continue;
					
					Cast<AEnemy>(Hit.Actor)->Hurt(damage);
					
					Destroy();
				}
			}

		}


		if (bulletDeathTimer >= bulletDeathMaxTime && willDestroyItself)
		{
			isMoving = false;
			Destroy();
		}
	}
	
}