#include "GameTestGameModeBase.h"
#include "Pawns/EnemyPawn.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"

AGameTestGameModeBase::AGameTestGameModeBase()
{
    
}

void AGameTestGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameTestGameModeBase::IncrementScore, 1.0f, true);

    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

    if (NavSystem)
    {
        // The number of retries to find a valid spawn point
        const int NumRetries = 10;

        for (int i = 0; i < NumberOfEnemies; i++)
        {
            FNavLocation ResultLocation;

            for (int j = 0; j < NumRetries; j++)
            {
                // Get a random point in the navigable radius
                if (NavSystem->GetRandomPointInNavigableRadius(SpawnAreaCenter, 1000, ResultLocation))
                {
                    // Check if the spawn point is too close to the player
                    APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
                    if (PlayerPawn && FVector::Dist(PlayerPawn->GetActorLocation(), ResultLocation) >= 200)
                    {
                        ResultLocation.Location.Z += 44;
                        GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, ResultLocation.Location, FRotator::ZeroRotator);
                        break;
                    }
                }
            }
        }
    }

}

void AGameTestGameModeBase::IncrementScore()
{
    PlayerScore++;
}

void AGameTestGameModeBase::GameOver()
{
    GetWorldTimerManager().ClearTimer(TimerHandle);

    // Restart the level after 2 seconds
    FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(UnusedHandle, this, &AGameTestGameModeBase::RestartLevel, 2.0f, false);
}

void AGameTestGameModeBase::RestartLevel()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}




