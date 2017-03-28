// Marc Portet 2017 - Batora07

#include "HackingGameNier.h"
#include "GameWidget.h"

void UGameWidget::Load() {
	// SCORE TEXT
	const FName TextBlockName = FName(TEXT("GameTextBlock"));
	if (ScoreText == nullptr) {
		ScoreText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
	//LIFE TEXT
	const FName LifeBlockName = FName(TEXT("LifeTextBlock"));
	if (LifeText == nullptr) {
		LifeText = (UTextBlock*)(WidgetTree->FindWidget(LifeBlockName));
	}
}

// Ui Text on Score text block
void UGameWidget::SetScore(int score) {
	if (ScoreText != nullptr) {
		ScoreText->SetText(FText::FromString(FString(TEXT("Score : ")) + FString::FromInt(score)));
	}
}

// UI Text on Life text block
void UGameWidget::SetLife(int life) {
	if (LifeText != nullptr) {
		LifeText->SetText(FText::FromString(FString(TEXT("Life : ")) + FString::FromInt(life)));
	}
}

// UI Text on Game Over
void UGameWidget::OnGameOver(int score) {
	if (ScoreText != nullptr) {
		ScoreText->SetText(FText::FromString(FString(TEXT("Score : ")) + FString::FromInt(score) + TEXT("\nPress R to restart")));
	}
	if (LifeText != nullptr) {
		LifeText->SetText(FText::FromString(FString(TEXT("Life : ")) + FString::FromInt(0)));
	}
}

	