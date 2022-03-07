// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPawn.h"

#include <variant>

#include "MainPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	RootComponent = CollisionComponent;

	TankBase = CreateDefaultSubobject<UStaticMeshComponent>("TankBase");
	TankBase->SetupAttachment(RootComponent);

	TurretSpawnPoint = CreateDefaultSubobject<UArrowComponent>("TankTower");
	TurretSpawnPoint->SetupAttachment(TankBase);
	
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	CameraArm->SetupAttachment(RootComponent);

	GameCamera = CreateDefaultSubobject<UCameraComponent>("GameCamera");
	GameCamera->SetupAttachment(CameraArm);
	GameCamera->bUsePawnControlRotation = false;
	CameraArm->bInheritPitch = false;
	CameraArm->bInheritYaw = false;
	CameraArm->bInheritRoll = false;
	CameraArm->TargetArmLength = 2500.f;
	CameraArm->bDoCollisionTest = false;

}

void ATankPawn::MoveForward(float ForwardAxis)
{
	ForwardScale = ForwardAxis;
}

void ATankPawn::Rotate(float RotationValue)
{
	RotationScale = RotationValue;
}

void ATankPawn::Fire()
{
	if(!TankTower)
		return;
	TankTower->Fire();
}

void ATankPawn::AlterFireOn()
{
	if(!TankTower)
		return;
	TankTower->AlterFireOn();
}

void ATankPawn::AlterFireOff()
{
	if(!TankTower)
		return;
	TankTower->AlterFireOff();
}

void ATankPawn::ChangeTower(TSubclassOf<ATankTowerType> TowerType)
{
	if(TankTower)
	TankTower->Destroy();
	TankTower = SpawnTower(TowerType);
}

void ATankPawn::TakeDamage(FDamageInfo Info)
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red, "Taking damage");
}

void ATankPawn::RotateTower()
{
	TankTower->RotateTower(TankController->GetMousePos());
}

void ATankPawn::ChangeTowerByInput(float Value)
{
	if (Value == 0)
		return;
	if(TankTowers.Num() == 0)
		return;
	
	CurrentTowerIndex = FMath::Clamp(CurrentTowerIndex + Value, 0.f, TankTowers.Num() - 1.f);
	
	ChangeTower(TankTowers[CurrentTowerIndex]);
}

ATankTowerType* ATankPawn::SpawnTower(TSubclassOf<ATankTowerType> TowerType)
{
	auto towerSpawnPointTransform = TurretSpawnPoint->GetComponentTransform();
	auto tankTower = GetWorld()->SpawnActor<ATankTowerType>(TowerType, towerSpawnPointTransform);
	tankTower->AttachToComponent(TurretSpawnPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	tankTower->SetTankPawn(this);
	return tankTower;
}

void ATankPawn::Move(float DeltaTime)
{
	
	auto location = GetActorLocation();
	auto currentacceleration = ForwardScale > 0 ? Acceleration : Acceleration * -0.75f;
	
	if (CurrentSpeed >= MinSpeed && CurrentSpeed <= MaxSpeed && ForwardScale != 0.f)
	{
		CurrentSpeed += currentacceleration * DeltaTime;
	}
	if(ForwardScale == 0.f || (FMath::Sign(CurrentSpeed) != FMath::Sign(ForwardScale)))
	{
		Stop();
	}
	
	FVector direction = GetActorForwardVector() * CurrentSpeed * DeltaTime ;
	SetActorLocation(location + direction);
}

void ATankPawn::RotateTank(float DeltaTime)
{
	float YawRotation = GetActorRotation().Yaw + RotationSpeed * DeltaTime * RotationScale * (ForwardScale >=0 ? 1 : -1);
	FRotator rotator = FRotator(0.f, YawRotation,0.f);
	SetActorRotation(rotator);
}

void ATankPawn::Stop()
{
	if(CurrentSpeed != 0.f)
	{
		CurrentSpeed += Acceleration * FMath::Sign(CurrentSpeed) * -StoppingPower * GetWorld()->DeltaTimeSeconds;
		if (FMath::Abs(CurrentSpeed) <= 4) CurrentSpeed = 0.f;
	}
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
	TankController = Cast<AMainPlayerController>(GetController());

	if(!TankTowerTypeBase)
		return;
	ChangeTower(TankTowerTypeBase);

	GetWorld()->GetTimerManager().SetTimer(RotationHandle,this, &ATankPawn::RotateTower,TowerRotationTimeDelta, true
		, TowerRotationTimeDelta);
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//MoveOld(DeltaTime); // movement with no acceleration
	
	Move(DeltaTime); // movement with acceleration
	RotateTank(DeltaTime); // Rotation of Body

	GEngine->AddOnScreenDebugMessage(498, 10,FColor::Yellow, FString::Printf(TEXT(" Health : %f / %f"), CurrentHealth, MaxHealth));
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
