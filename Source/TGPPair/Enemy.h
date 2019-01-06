// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleComponent.h" 
#include "DestructibleMesh.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class TGPPAIR_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int health = 100;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Hurt(int amount) 
	{
		
		health -= amount;
		if (health <= 0) //
			CompShipMeshComponent->ApplyRadiusDamage(10000, FVector(0, 0, 0), 2000, 2000, true);

	};
	UPROPERTY(EditAnywhere)
		UDestructibleComponent* CompShipMeshComponent;
	APlayerCharacter* player;
};
