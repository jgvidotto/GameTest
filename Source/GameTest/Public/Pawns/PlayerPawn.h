// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class GAMETEST_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRigth(float Value);
	void MoveInDirection(const FVector& Direction, float Value);

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	float PlayerFOV = 90.0f;;
};
