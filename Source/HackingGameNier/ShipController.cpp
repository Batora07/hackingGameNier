// Marc Portet 2017 - Batora07

#include "HackingGameNier.h"
#include "ShipController.h"
#include "BulletController.h"
#include "EnemyController.h"
#include "HackingGameNierGameMode.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	CollisionBox->bGenerateOverlapEvents = true;
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShipController::OnOverlap);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + Speed * CurrentVelocity * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveX", this, &AShipController::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AShipController::Move_YAxis);
	InputComponent->BindAxis("Turn", this, &AShipController::Turn);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AShipController::OnShoot);
	InputComponent->BindAction("Restart", IE_Pressed, this, &AShipController::OnRestart).bExecuteWhenPaused = true;
}

void AShipController::Move_XAxis(float AxisValue) {
	CurrentVelocity.X = AxisValue * 100.0f;
}

void AShipController::Move_YAxis(float AxisValue) {
	CurrentVelocity.Y = AxisValue * 100.0f;
}

void AShipController::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void AShipController::OnShoot() {
	UWorld* World = GetWorld();
	if (World) {
		FVector Location = GetActorLocation();
		World->SpawnActor<ABulletController>(BulletBlueprint, Location, GetActorRotation());
	}
}

void AShipController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// colliding with an enemy
	if (OtherActor->IsA(AEnemyController::StaticClass())) {
		//  Player Life > 1 => life--
		if (((AHackingGameNierGameMode*)GetWorld()->GetAuthGameMode())->PlayerLife > 1) {
			// The player looses a pod corresponding as a life
			RootComponent->GetChildrenComponents(true, ChildArray);
			// remove pod life3
			if (((AHackingGameNierGameMode*)GetWorld()->GetAuthGameMode())->PlayerLife == 3) {
				// get pod life3
				if (ChildArray[2] != NULL)
				{
					USceneComponent* ChildComp = ChildArray[2];
					ChildArray[2]->SetVisibility(false, true);
					//UE_LOG(LogTemp, Warning, TEXT("Component: %s"), *ChildComp->GetName());
				}
			}
			// remove pod life2
			else if (((AHackingGameNierGameMode*)GetWorld()->GetAuthGameMode())->PlayerLife == 2) {
				// Get pod life2
				if (ChildArray[1] != NULL)
				{
					USceneComponent* ChildComp = ChildArray[1];
					ChildArray[1]->SetVisibility(false, true);
					//UE_LOG(LogTemp, Warning, TEXT("Component: %s"), *ChildComp->GetName());
				}
			}
			((AHackingGameNierGameMode*)GetWorld()->GetAuthGameMode())->DecrementLife();
		}
		// Player died
		else {
			Died = true;
			this->SetActorHiddenInGame(true);
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			((AHackingGameNierGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver();
		}
	}
}

void AShipController::OnRestart() {
	if (Died) {
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}