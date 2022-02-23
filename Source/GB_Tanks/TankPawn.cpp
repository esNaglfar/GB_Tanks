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
	fFScale = forwardAxis;
}

void ATankPawn::MoveRight(float rightAxis)
{
	fRScale = rightAxis;
}

void ATankPawn::Rotate(float rotationValue)
{
	fRotationScale = rotationValue;
}

void ATankPawn::Move(float DeltaTime)
{
	auto location = GetActorLocation();
	auto currentacceleration = fFScale > 0 ? acceleration : acceleration * -0.75f;
	
	if (currentSpeed >= minSpeed && currentSpeed <= maxSpeed && fFScale != 0.f)
	{
		currentSpeed += currentacceleration * DeltaTime;
	}
	if(fFScale == 0.f || (IsPositive(currentSpeed) != IsPositive(fFScale)))
	{
		Stop();
	}
	
	FVector direction = GetActorForwardVector() * currentSpeed * DeltaTime ;
	SetActorLocation(location + direction);

	//GEngine->AddOnScreenDebugMessage(-1,0.0f,FColor::Yellow,FString::Printf(TEXT("Current acceleration : %f"), currentacceleration));
	//GEngine->AddOnScreenDebugMessage(-1,0.0f,FColor::Yellow,FString::Printf(TEXT("Current speed : %f"), currentSpeed));
}

void ATankPawn::RotateTower(float DeltaTime)
{
	
	FVector mousePos = controller->GetMousePos();
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
	FRotator currentRotation = TurretSpawnPoint->GetComponentRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	TurretSpawnPoint->SetWorldRotation(FMath::Lerp(currentRotation,targetRotation,towerAcceleration*DeltaTime));
}

void ATankPawn::RotateTank(float DeltaTime)
{
	float YawRotation = GetActorRotation().Yaw + fRotationSpeed * DeltaTime * fRotationScale;
	FRotator rotator = FRotator(0.f, YawRotation,0.f);
	SetActorRotation(rotator);
}

void ATankPawn::Stop()
{
	if(currentSpeed != 0.f)
	{
		currentSpeed += acceleration * currentSpeed / FMath::Abs(currentSpeed) * -stoppingPower * GetWorld()->DeltaTimeSeconds;
		if (FMath::Abs(currentSpeed) <= 4) currentSpeed = 0.f;
	}
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
	controller = Cast<AMainPlayerController>(GetController());
	
	auto towertSpawnPointTransform = TurretSpawnPoint->GetComponentTransform();
	TankTower = GetWorld()->SpawnActor<ATankTowerType>(TankTowerType, towertSpawnPointTransform);
	TankTower->AttachToComponent(TurretSpawnPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

bool ATankPawn::IsPositive(float value)
{
	return FMath::Abs(value) / value > 0 ? true : false;
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//MoveOld(DeltaTime); // movement with no acceleration
	
	Move(DeltaTime); // movement with acceleration
	RotateTank(DeltaTime); // Rotation of Body
	RotateTower(DeltaTime); //Rotation of Tower
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
