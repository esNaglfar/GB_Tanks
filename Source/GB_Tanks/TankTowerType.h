// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "TankTowerType.generated.h"

class ATankPawn;

UENUM()
enum class ETurretFiretype
{
	FireProjectile = 0 UMETA(DisplayName = "Turret fires projectile with ballistics"),
	FireTrace = 1 UMETA(DisplayName = "Turrets fires linetrace")
};

UCLASS()
class GB_TANKS_API ATankTowerType : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankTowerType();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Components")
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Components")
	UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Combat")
	ETurretFiretype Firetype = ETurretFiretype::FireProjectile;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Combat")
	float RateOfFire = 1.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Combat")
	float AlterRateOfFire = 1.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Combat")
	float Damage = 1.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Rotation")
	float RotationAcceleration = 4.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Combat")
	int MaxAmmo = 20;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Combat")
	int CurrentAmmo;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Combat")
	int FireAmmoConsumption = 1;
	
	bool bCanFire = true;
	bool bCanAlterFire = false;
	FTimerHandle TimerHandle;

	void Fire();
	void AlterFire();
	void ChangeAlterFire();
	void SetTankPawn(ATankPawn* Pawn);
	void ResetFireState();
	void RotateTower();
	void MakeShot(FString text);
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	ATankPawn* TankPawn;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


