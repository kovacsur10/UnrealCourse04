// Copyright to Máté Kovács 2017

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

private:
	ATank();

	virtual void BeginPlay() override;
};
