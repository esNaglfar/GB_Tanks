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

void ATankTowerType::Fire()
{
	if(CurrentAmmo <= 0)
		return;
	if(!bCanFire)
		return;
	
	GEngine->AddOnScreenDebugMessage(-1, 3,FColor::Green, TEXT(" BANG BANG BANG "));
	CurrentAmmo = FMath::Clamp(CurrentAmmo - FireAmmoConsumption, 0, MaxAmmo);
}

void ATankTowerType::AlterFire()
{
	if(CurrentAmmo <= 0)
		return;
	if(!bCanFire)
		return;
	
	GEngine->AddOnScreenDebugMessage(-1, 3,FColor::Green, TEXT(" PEW PEW PEW "));
	CurrentAmmo = FMath::Clamp(CurrentAmmo - FireAmmoConsumption, 0, MaxAmmo);
}

// Called when the game starts or when spawned
void ATankTowerType::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
}

// Called every frame
void ATankTowerType::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(500, 10,FColor::Yellow, FString::Printf(TEXT(" Ammo : %i / %i"), CurrentAmmo, MaxAmmo));

}

