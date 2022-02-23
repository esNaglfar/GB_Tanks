// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TankTurretAsset.generated.h"
class ATankTowerType;
UCLASS()
class GB_TANKS_API ATankTurretAsset : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankTurretAsset();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Components")
	USphereComponent* Collision;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* TowerMesh;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Settings")
	TSubclassOf<ATankTowerType> TowerType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Floating")
	float FloatAmplitude = 20.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Floating")
	float FloatSpeed = 3.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Floating")
	float FloatRotationSpeed = 40.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void FloatAndRotate(float DeltaTime);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

