// Copyright to Máté Kovács 2017

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent == nullptr)) {
		return;
	}
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (GetPawn() == nullptr) { 
		return;
	}
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent == nullptr)) {
		return;
	}

	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation) {
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	} else {
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult hitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera)) {
		HitLocation = hitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn != nullptr) {
		auto ControlledTank = Cast<ATank>(InPawn);
		if (ensure(ControlledTank == nullptr)) {
			return;
		}
		ControlledTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath() {
	StartSpectatingOnly();
}