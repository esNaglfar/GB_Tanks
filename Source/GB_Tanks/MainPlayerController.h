// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class ATankPawn;

/**
 * 
 */
UCLASS()
class GB_TANKS_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void SetupInputComponent() override;
	

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void OnMoveForward(float value);
	void OnMoveRight(float value);
	void OnRotate(float value);

public:
	FVector GetMousePos() {return MousePosition;}

private:
	UPROPERTY()
	ATankPawn* playerPawn;
	FVector MousePosition;
};


