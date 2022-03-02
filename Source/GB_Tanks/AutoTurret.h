// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankTowerType.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
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

	UPROPERTY(BlueprintReadWrite,VisibleDefaultsOnly,Category="Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(BlueprintReadWrite,VisibleDefaultsOnly,Category="Components")
	TSubclassOf<ATankTowerType> TowerType;

	
	
	
	// Sets default values for this actor's properties
	AAutoTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
