// Marc Portet 2017 - Batora07

#pragma once

#include "GameFramework/Actor.h"
#include "EnemyController.generated.h"

UCLASS()
class HACKINGGAMENIER_API AEnemyController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox;

	UPROPERTY(EditAnywhere)
		float Speed = -200.0f;
	
};
