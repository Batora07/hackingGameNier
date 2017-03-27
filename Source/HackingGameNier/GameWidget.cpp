// Marc Portet 2017 - Batora07

#include "HackingGameNier.h"
#include "GameWidget.h"

void UGameWidget::Load() {
	const FName TextBlockName = FName(TEXT("GameTextBlock"));

	if (ScoreText == nullptr) {
		ScoreText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}

void UGameWidget::SetScore(int score) {
	if (ScoreText != nullptr) {
		ScoreText->SetText(FText::FromString(FString(TEXT("Score : ")) + FString::FromInt(score)));
	}
}

void UGameWidget::OnGameOver(int score) {
	if (ScoreText != nullptr) {
		ScoreText->SetText(FText::FromString(FString(TEXT("Score : ")) + FString::FromInt(score) + TEXT("\nPress R to restart")));
	}
}