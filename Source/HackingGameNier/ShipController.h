// Marc Portet 2017 - Batora07

#pragma once

#include "GameFramework/Pawn.h"
#include "ShipController.generated.h"

UCLASS()
class HACKINGGAMENIER_API AShipController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;
	UPROPERTY(EditAnywhere)
		float Speed = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABulletController> BulletBlueprint;
	
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Turn(float AxisValue);

	// Player pressed fire command => shoot bullet
	void OnShoot();

	// Restart the scene
	void OnRestart();

	FVector CurrentVelocity;
	
	bool Died;

	// Player get hit
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
