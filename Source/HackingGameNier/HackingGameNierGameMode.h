// Marc Portet 2017 - Batora07

#pragma once

#include "GameFramework/GameMode.h"
#include "HackingGameNierGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HACKINGGAMENIER_API AHackingGameNierGameMode : public AGameMode
{
	GENERATED_BODY()

	float MINIMUM_INTERVAL = 0.5f; 
	float MAXIMUM_INTERVAL = 2.0f; // maximum interval before enemy spawning
	float TIME_TO_MINIMUM_INTERVAL = 30.0f;  // the game is going to wait 30s before it's going to be as hard as possible

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController> EnemyBlueprint;

	int PlayerLife = 3;

	float EnemyTimer;
	float GameTimer;

	void DecrementLife();
	void IncrementScore();
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	
protected: 
	int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;
	
};
