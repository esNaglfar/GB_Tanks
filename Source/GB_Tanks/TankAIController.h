// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class GB_TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Move")
	FString WaypointTag = "Default";

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Move", Meta=(MakeEditWidget = true))
	TArray<FVector> WayPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move")
	float MovementAccuracy = 10.f;

private:

	int32 CurrentPointIndex = 0;
	

	
};
