// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/EnemyPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FloatingPawnMovement = FindComponentByClass<UFloatingPawnMovement>();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyPawn::ResumeMovement()
{
	if (PlayerPawn && FloatingPawnMovement)
	{
		FVector Direction = (PlayerPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FloatingPawnMovement->AddInputVector(Direction);
	}
}

void AEnemyPawn::StopMovement()
{
	if (FloatingPawnMovement)
	{
		FloatingPawnMovement->StopMovementImmediately();
	}
}

