// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnemyPawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class GAMETEST_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ResumeMovement();
	void StopMovement();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UFloatingPawnMovement* FloatingPawnMovement;
	APawn* PlayerPawn = nullptr;
};
