// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTowerType.h"


#include "DrawDebugHelpers.h"
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

void ATankTowerType::AlterFireOn()
{
	if(!bCanFire)
		return;
	
	bIsAlterFire = true;
	GEngine->AddOnScreenDebugMessage(1,2,FColor::Yellow,"ALTER ON");
	GetWorld()->GetTimerManager().SetTimer(AlterFireHandle, this, &ATankTowerType::Fire, AlterRateOfFire, true,0.f);
	
}

void ATankTowerType::AlterFireOff()
{
	bIsAlterFire = false;
	GEngine->AddOnScreenDebugMessage(1,2,FColor::Yellow,"ALTER OFF");
	GetWorld()->GetTimerManager().ClearTimer(AlterFireHandle);
}


void ATankTowerType::SetTankPawn(ATankPawn* Pawn)
{
	TankPawn = Pawn;
}

void ATankTowerType::ResetFireState()
{
	bCanFire = true;
}


void ATankTowerType::RotateTower(FVector LookAtPoint)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LookAtPoint);
	FRotator currentRotation = GetActorRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	SetActorRotation(FMath::Lerp(currentRotation,targetRotation,RotationAcceleration*GetWorld()->GetDeltaSeconds()));
}


void ATankTowerType::MakeShot(FString text) // text for a while...
{
	if(!bIsAlterFire)
	bCanFire = false;

	if(Firetype == ETurretFiretype::FireProjectile)
	{
		auto projectile = GetWorld()->SpawnActor<ADefaultProjectile>(
			Projectile,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation()
			);

		if(projectile)
			projectile->Launch();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "LASER PEW");
		FHitResult hitResult;
		
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector() * LaserAtackRange + start;

		if(GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0,5.f);
			if(hitResult.Actor.Get())
			{
				hitResult.GetActor()->Destroy();
			}
		}
		
	}
	GEngine->AddOnScreenDebugMessage(-1, 1/RateOfFire,FColor::Green, text);
	
	CurrentAmmo = FMath::Clamp(CurrentAmmo - FireAmmoConsumption, 0, MaxAmmo);
	
	if(!bIsAlterFire)
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,
		FTimerDelegate::CreateUObject(this,&ATankTowerType::ResetFireState),
		1/RateOfFire,
		false,
		1/RateOfFire);
}

void ATankTowerType::AddAmmo(int amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + amount,0,MaxAmmo);
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

	//RotateTower();
	
	GEngine->AddOnScreenDebugMessage(500, 10,FColor::Yellow, FString::Printf(TEXT(" Ammo : %i / %i"), CurrentAmmo, MaxAmmo));
	GEngine->AddOnScreenDebugMessage(499, 10,FColor::Yellow, FString::Printf(TEXT(" Reload timer : %f"),
		GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle)));

}

