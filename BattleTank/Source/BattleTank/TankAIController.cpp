// Copyright to Máté Kovács 2017

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller begin play!"));
}

void ATankAIController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank =GetPawn();

	if (ensure(PlayerTank != nullptr) && ensure(ControlledTank != nullptr)) {
		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn != nullptr) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (ensure(PossessedTank == nullptr)) {
			return;
		}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath() {
	if (GetPawn() != nullptr) {
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}