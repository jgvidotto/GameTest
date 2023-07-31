// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameTestGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class GAMETEST_API AGameTestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    AGameTestGameModeBase();

    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    TSubclassOf<class AEnemyPawn> EnemyClass;

    UPROPERTY(EditAnywhere, Category = "Gameplay")
    FVector SpawnAreaCenter;

    UPROPERTY(EditAnywhere, Category = "Gameplay")
    int32 NumberOfEnemies = 4;
};
