// Marc Portet 2017 - Batora07

#pragma once

#include "GameFramework/Actor.h"
#include "BulletController.generated.h"

UCLASS()
class HACKINGGAMENIER_API ABulletController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox;
	
	UPROPERTY(EditAnywhere)
		float Speed = 400.0f;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
