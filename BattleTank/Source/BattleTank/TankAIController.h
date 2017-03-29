// Copyright to Máté Kovács 2017

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;
	
private:
	ATank* GetPlayerTank() const;
};
