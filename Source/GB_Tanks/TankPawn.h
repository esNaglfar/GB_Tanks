// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankTowerType.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"

class AMainPlayerController;

UCLASS(Blueprintable)
class GB_TANKS_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TankBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UArrowComponent* TurretSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret type")
	TSubclassOf<ATankTowerType> TankTowerType;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	//UStaticMeshComponent* TankTower;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* GameCamera;


	void MoveForward(float forwardAxis);
	void MoveRight(float rightAxis);
	void Rotate(float rotationValue);
	

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float fFMovementSpeed = 350.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float fRMovementSpeed = 350.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Rotation")
	float fRotationSpeed = 60.f;
	float fRotationScale = 0.f;
	float fFScale = 0.f;
	float fRScale = 0.f;

	// -- new movement

	
	float currentSpeed = 0.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float maxSpeed = 350.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float minSpeed = -250.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float acceleration = 200.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float stoppingPower = 4.f;
	//

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Rotation")
	float towerAcceleration = 2.f;
	
	AMainPlayerController* controller;

private:
	void Move(float DeltaTime);
	void RotateTower(float DeltaTime);
	void RotateTank(float DeltaTime);
	void Stop();

	ATankTowerType* TankTower;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsPositive(float value);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
