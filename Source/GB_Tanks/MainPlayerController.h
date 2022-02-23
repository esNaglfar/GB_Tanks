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
	
	void OnMoveForward(float Value);
	void OnRotate(float Value);
	void OnFire();
	void OnAlterFire();
	void OnNextTurret(float Value);

public:
	FVector GetMousePos() {return MousePosition;}

private:
	UPROPERTY()
	ATankPawn* PlayerPawn;
	FVector MousePosition;
};


