// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/PlayerPawn.h"
#include "Pawns/EnemyPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPawn::MoveForward(float Value)
{
	MoveInDirection(GetActorForwardVector(), Value);
}

void APlayerPawn::MoveRight(float Value)
{
	MoveInDirection(GetActorRightVector(), Value);
}

void APlayerPawn::LookUp(float Value)
{
	if (Controller && (Value != 0.0f))
	{
		AddControllerPitchInput(Value);
	}
}

void APlayerPawn::LookRigth(float Value)
{
	if (Controller && (Value != 0.0f))
	{
		AddControllerYawInput(Value);
	}
}

void APlayerPawn::MoveInDirection(const FVector& Direction, float Value)
{
	if (Controller && (Value != 0.0f))
	{
		AddMovementInput(Direction, Value);
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyPawn::StaticClass(), FoundEnemies);

	for (AActor* Actor : FoundEnemies)
	{
		AEnemyPawn* Enemy = Cast<AEnemyPawn>(Actor);

		// Get the vector from the player to the enemy
		FVector EnemyDirection = Enemy->GetActorLocation() - GetActorLocation();
		EnemyDirection.Normalize();

		// Get the player's forward vector
		FVector Forward = GetActorForwardVector();

		// Calculate the angle between the player's forward vector and the vector to the enemy
		float DotProduct = FVector::DotProduct(Forward, EnemyDirection);
		float Angle = FMath::Acos(DotProduct) * (180.0f / PI);

		// If the enemy is within the player's FOV
		if (Angle < PlayerFOV)
		{
			// Perform a raycast to check if there are any obstructions
			FHitResult HitResult;
			FVector Start = GetActorLocation();
			FVector End = Enemy->GetActorLocation();

			// If there are no obstructions, stop the enemy
			if (!GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
			{
				Enemy->StopMovement();
			}
			// If there are obstructions, the enemy can move again
			else
			{
				Enemy->ResumeMovement();
			}
		}
		// If the enemy is not within the player's FOV, the enemy can move again
		else
		{
			Enemy->ResumeMovement();
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &APlayerPawn::LookUp);
	PlayerInputComponent->BindAxis(FName("LookRigth"), this, &APlayerPawn::LookRigth);

}

