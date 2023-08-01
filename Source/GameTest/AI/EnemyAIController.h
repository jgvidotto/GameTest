// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "EnemyAIController.generated.h"
/**
 * 
 */
UCLASS()
class GAMETEST_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:

    AEnemyAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    APawn* PlayerPawn = nullptr;
};
