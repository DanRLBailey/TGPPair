// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class TGPPAIR_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	class USphereComponent* CollisionSphere;
	
	/*Speed at which the bullet moves*/ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Movespeed;

	float bulletDeathTimer;

	/*How long the bullet will live for before destroying itself*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
	float bulletDeathMaxTime;

	/*Whether or not the bullet will destroy itself*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
	bool willDestroyItself;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
	int damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults)
	bool isMoving;
};
