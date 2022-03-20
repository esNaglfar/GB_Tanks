// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destroyable.h"
#include "HealthSystem.h"
#include "Scorable.h"
#include "TankAIController.h"
#include "TankTowerType.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"

class AMainPlayerController;



UCLASS(Blueprintable)
class GB_TANKS_API ATankPawn : public APawn, public IDestroyable, public IScorable
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
	TSubclassOf<ATankTowerType> TankTowerTypeBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* GameCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret type")
	TArray<TSubclassOf<ATankTowerType>> TankTowers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Componetns")
	UHealthSystem* HealthSystem;

	int Score = 0;
	int Points = 12;
	
	void MoveForward(float ForwardAxis);
	void Rotate(float RotationValue);
	void Fire();
	void AlterFireOn();
	void AlterFireOff();
	void ChangeTower(TSubclassOf<ATankTowerType> TowerType);

	void TargetDestroyed(AActor* target);

	
	UFUNCTION()
	void OnDamageTaken(float Amount);
	UFUNCTION()
	void OnDeath();

	virtual void TakeDamage(FDamageInfo Info) override;
	virtual void CountScore(FScoreInfo Info) override;
	virtual int GetPoints() override;

	
	UFUNCTION()
	void RotateTower();

	void ChangeTowerByInput(float Value);

	TArray<ATankTowerType> PersistentTankTowers;
	
	ATankTowerType* SpawnTower(TSubclassOf<ATankTowerType> TowerType);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Rotation")
	float RotationSpeed = 60.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Rotation")
	float TowerRotationTimeDelta = 0.015f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float MaxSpeed = 350.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float MinSpeed = -250.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float Acceleration = 200.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Movement|Speed")
	float StoppingPower = 4.f;

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Combat|Health")
	float MaxHealth = 500.f;

	
	AMainPlayerController* PController;
	ATankAIController* AIController;


	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Misc")
	ATankTowerType* TankTower;

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Move(float DeltaTime);
	void RotateTank(float DeltaTime);
	
	void Stop();

	float RotationScale = 0.f;
	float ForwardScale = 0.f;
	float CurrentSpeed = 0.f;
	float CurrentHealth = MaxHealth;
	float CurrentTowerIndex = 0;
	FTimerHandle RotationHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
