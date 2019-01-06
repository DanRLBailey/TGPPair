// Fill out your copyright notice in the Description page of Project Settings.

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
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CompShipMeshComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Sphere_DM"));
	const ConstructorHelpers::FObjectFinder<UDestructibleMesh> MeshObj(TEXT("DestructibleMesh'/Game/Enemy/Cube_DM.Cube_DM'"));
	CompShipMeshComponent->AttachToComponent(this->GetDefaultAttachComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	CompShipMeshComponent->SetDestructibleMesh(MeshObj.Object);

}
// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), FoundActors);
	player = (APlayerCharacter*)FoundActors[0];
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (health >= 0)
	{
		if (player->GetActorLocation().X > this->GetActorLocation().X + 30)
		{
			this->SetActorLocation(this->GetActorLocation() + FVector(5, 0, 0), false, NULL, ETeleportType::None);
		}
		else if (player->GetActorLocation().X < this->GetActorLocation().X - 30)
		{
			this->SetActorLocation(this->GetActorLocation() + FVector(-5, 0, 0), false, NULL, ETeleportType::None);
		}

		if (player->GetActorLocation().Y > this->GetActorLocation().Y + 30)
		{
			this->SetActorLocation(this->GetActorLocation() + FVector(0, 5, 0), false, NULL, ETeleportType::None);
		}
		else if (player->GetActorLocation().Y < this->GetActorLocation().Y - 30)
		{
			this->SetActorLocation(this->GetActorLocation() + FVector(0, -5, 0), false, NULL, ETeleportType::None);
		}
	}
}

