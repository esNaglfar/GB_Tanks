// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPawn.h"
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
	
}

void ATankPawn::MoveForward(float forwardAxis)
{
	ForwardScale = forwardAxis;
}


void ATankPawn::Rotate(float rotationValue)
{
	RotationScale = rotationValue;
}

void ATankPawn::Fire()
{
	if(!TankTower)
		return;
	TankTower->Fire();
}

void ATankPawn::AlterFire()
{
	if(!TankTower)
		return;
	TankTower->AlterFire();
}

void ATankPawn::ChangeTower(TSubclassOf<ATankTowerType> TowerType)
{
	if(TankTower)
	TankTower->Destroy();
	TankTower = SpawnTower(TowerType);
}

ATankTowerType* ATankPawn::SpawnTower(TSubclassOf<ATankTowerType> TowerType)
{
	auto towersSawnPointTransform = TurretSpawnPoint->GetComponentTransform();
	auto tankTower = GetWorld()->SpawnActor<ATankTowerType>(TowerType, towersSawnPointTransform);
	tankTower->AttachToComponent(TurretSpawnPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
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

void ATankPawn::RotateTower(float DeltaTime)
{
	
	FVector mousePos = TankController->GetMousePos();
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
	FRotator currentRotation = TurretSpawnPoint->GetComponentRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	TurretSpawnPoint->SetWorldRotation(FMath::Lerp(currentRotation,targetRotation,TowerAccelerationSpeed*DeltaTime));
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
		CurrentSpeed += Acceleration * CurrentSpeed / FMath::Abs(CurrentSpeed) * -StoppingPower * GetWorld()->DeltaTimeSeconds;
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
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//MoveOld(DeltaTime); // movement with no acceleration
	
	Move(DeltaTime); // movement with acceleration
	RotateTank(DeltaTime); // Rotation of Body
	RotateTower(DeltaTime); //Rotation of Tower

	GEngine->AddOnScreenDebugMessage(400, 10,FColor::Yellow, FString::Printf(TEXT(" Ammo : %f / %f"), CurrentHealth, MaxHealth));
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
