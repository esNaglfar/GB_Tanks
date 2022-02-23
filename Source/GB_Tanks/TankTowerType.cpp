// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTowerType.h"

#include "MainPlayerController.h"
#include "TankPawn.h"
#include "Kismet/KismetMathLibrary.h"

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

	MakeShot("BANG!!!!");

}

void ATankTowerType::AlterFire()
{
	if(CurrentAmmo <= 0)
		return;
	if(!bCanFire)
		return;
	if(!bCanAlterFire)
		return;

	
	MakeShot("PEW PEW PEW!!!!");
}

void ATankTowerType::ChangeAlterFire()
{
	bCanAlterFire = !bCanAlterFire;
}

void ATankTowerType::SetTankPawn(ATankPawn* Pawn)
{
	TankPawn = Pawn;
}

void ATankTowerType::ResetFireState()
{
	bCanFire = true;
}

void ATankTowerType::RotateTower()
{
	if(!TankPawn)
		return;
	FVector mousePos = TankPawn->TankController->GetMousePos();
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
	FRotator currentRotation = GetActorRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	SetActorRotation(FMath::Lerp(currentRotation,targetRotation,RotationAcceleration*GetWorld()->GetDeltaSeconds()));
}


void ATankTowerType::MakeShot(FString text) // text for a while...
{
	bCanFire = false;
	GEngine->AddOnScreenDebugMessage(-1, 1/RateOfFire,FColor::Green, text);
	CurrentAmmo = FMath::Clamp(CurrentAmmo - FireAmmoConsumption, 0, MaxAmmo);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,
		FTimerDelegate::CreateUObject(this,&ATankTowerType::ResetFireState),
		1/RateOfFire,
		false,
		1/RateOfFire);
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

	RotateTower();
	AlterFire();
	
	GEngine->AddOnScreenDebugMessage(500, 10,FColor::Yellow, FString::Printf(TEXT(" Ammo : %i / %i"), CurrentAmmo, MaxAmmo));
	GEngine->AddOnScreenDebugMessage(499, 10,FColor::Yellow, FString::Printf(TEXT(" Reload timer : %f"),
		GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle) + 1.f));

}

