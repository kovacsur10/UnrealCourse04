// Copyright to Máté Kovács 2017

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;
	
private:
	float AcceptanceRadius = 3000.f;
};
