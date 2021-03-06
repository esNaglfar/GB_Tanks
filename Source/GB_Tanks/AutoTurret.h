// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destroyable.h"
#include "HealthSystem.h"
#include "Scorable.h"
#include "TankTowerType.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "AutoTurret.generated.h"

UCLASS()
class GB_TANKS_API AAutoTurret : public AActor, public IDestroyable, public IScorable
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
	float Accuracy = 0.35f;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Components")
	float TargetingRange = 900.f;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Components")
	float TargetingSpeed = 0.01f;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category="Components")
	UHealthSystem* HealthSystem;
	
	UPROPERTY()
	TWeakObjectPtr<ATankPawn> Target;

	int Points = 3;
	int Score = 0;
	
	UFUNCTION()
	void Death();

	UFUNCTION()
	void DamageTaken(float Amount);

	UPROPERTY()
	ATankTowerType* Tower;

	FTimerHandle TargetingHandler;
	
	bool IsAimed();
	void RotateToTarget();
	bool IsTargetInRange();
	bool InLineOfSight();
	void TargetEliminated();
	void GetClosestTarget();

	virtual void TakeDamage(FDamageInfo Info) override;

	virtual void CountScore(FScoreInfo Info) override;
	virtual int GetPoints() override;
	
	UFUNCTION()
	void OnSensorOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSensorEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Sets default values for this actor's properties
	AAutoTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<ATankPawn*> Targets;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
