// Marc Portet 2017 - Batora07

#include "HackingGameNier.h"
#include "HackingGameNierGameMode.h"
#include "ShipController.h"
#include "EnemyController.h"
#include "GameWidget.h"

void AHackingGameNierGameMode::BeginPlay() {
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);

	((UGameWidget*)CurrentWidget)->Load();
}

void AHackingGameNierGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;

	if (EnemyTimer <= 0.0f) {
		float difficultyPercentage = FMath::Min(GameTimer/TIME_TO_MINIMUM_INTERVAL, 1.0f);
		EnemyTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL) * difficultyPercentage; // interpolate between values to make the game easier or harder
		
		UWorld* World = GetWorld();
		// Spawning enemies
		if (World) {
			FVector Location = FVector(600.0f, FMath::RandRange(-800.0f, 800.0f), 70.0f);
			World->SpawnActor<AEnemyController>(EnemyBlueprint, Location, FRotator::ZeroRotator);
		}
	}

}

void AHackingGameNierGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}

void AHackingGameNierGameMode::DecrementLife() {
	if (PlayerLife > 0) {
		PlayerLife--;
		((UGameWidget*)CurrentWidget)->SetLife(PlayerLife);
	}
}

void AHackingGameNierGameMode::IncrementScore() {
	Score += 100;
	((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void AHackingGameNierGameMode::OnGameOver() {
	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}