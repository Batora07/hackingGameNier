// Marc Portet 2017 - Batora07

#include "HackingGameNier.h"
#include "BulletController.h"
#include "EnemyController.h"
#include "HackingGameNierGameMode.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletController::OnOverlap);
}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation();
	float YawAngle = GetActorRotation().Yaw;
	
	//NewLocation.Y += Speed * DeltaTime * YawAngle.Yaw;
	// V.x = cos(A)
	// V.y = sin(A)
	
	float radian = (PI * YawAngle) / 180.0f;

	float Vx = cos(radian) * Speed;
	float Vy = sin(radian) * Speed;
	NewLocation.X += Vx * DeltaTime;
	NewLocation.Y += Vy * DeltaTime;
	SetActorLocation(NewLocation);

	if (NewLocation.X > 1500.0f || NewLocation.X < -1500.0f || NewLocation.Y > 1500.0f || NewLocation.Y < -1500.0f) {
		this->Destroy();
	}

}

void ABulletController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor->IsA(AEnemyController::StaticClass())) {
		this->Destroy();
		OtherActor->Destroy();

		((AHackingGameNierGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
	}
}

