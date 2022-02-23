// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTowerType.h"

// Sets default values
ATankTowerType::ATankTowerType()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Default root");

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret mesh");
	TurretMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("Projectile spawn point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

// Called when the game starts or when spawned
void ATankTowerType::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankTowerType::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

