// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankTowerType.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "AutoTurret.generated.h"

UCLASS()
class GB_TANKS_API AAutoTurret : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,VisibleDefaultsOnly,Category="Components")
	UStaticMeshComponent* TowerMesh;

	UPROPERTY(BlueprintReadWrite,VisibleDefaultsOnly,Category="Components")
	UArrowComponent* TowerSlot;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Components")
	TSubclassOf<ATankTowerType> TowerType;

	UPROPERTY(BlueprintReadWrite,VisibleDefaultsOnly,Category="Components")
	USphereComponent* FoeDetector;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Components")
	float Accuracy = 10.f;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Components")
	float TargetingRange = 350.f;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Components")
	float TargetingSpeed = 0.01f;
	
	UPROPERTY()
	AActor* Target;

	UPROPERTY()
	ATankTowerType* Tower;
	

	FTimerHandle TargetingHandler;

	bool IsAimed();
	void RotateToTarget();
	bool IsTargetInRange();

	void TargetEliminated();

	void OnSensorOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Sets default values for this actor's properties
	AAutoTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
