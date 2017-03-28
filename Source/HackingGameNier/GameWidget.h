// Marc Portet 2017 - Batora07

#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class HACKINGGAMENIER_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Load();

	void SetScore(int score);
	void SetLife(int life);
	void OnGameOver(int score);

	UPROPERTY()
		UTextBlock* ScoreText;
	
	UPROPERTY()
		UTextBlock* LifeText;
};
