// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "TankTowerType.generated.h"


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
	float Damage = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};