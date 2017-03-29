// Copyright to Máté Kovács 2017

#include "BattleTank.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller begin play!"));
}

ATank* ATankAIController::GetPlayerTank() const {
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController != nullptr) {
		return Cast<ATank>(playerController);
	} else {
		return nullptr;
	}
}

void ATankAIController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	if (GetPlayerTank() != nullptr) {
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}