// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pawns/PlayerPawn.h"

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

