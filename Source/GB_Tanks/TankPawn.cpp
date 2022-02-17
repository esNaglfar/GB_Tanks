// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "TankPawn.h"
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

	TankTower = CreateDefaultSubobject<UStaticMeshComponent>("TankTower");
	TankTower->SetupAttachment(TankBase);
	
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	CameraArm->SetupAttachment(RootComponent);

	GameCamera = CreateDefaultSubobject<UCameraComponent>("GameCamera");
	GameCamera->SetupAttachment(CameraArm);
	GameCamera->bUsePawnControlRotation = false;
	CameraArm->bInheritPitch = false;
	CameraArm->bInheritYaw = false;
	CameraArm->bInheritRoll = false;
	
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

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	controller = Cast<AMainPlayerController>(GetController());
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto location = GetActorLocation();
	
	auto direction = (GetActorForwardVector() * fFMovementSpeed * fFScale) + (GetActorRightVector() * fRMovementSpeed * fRScale);
	
	SetActorLocation(location + direction  * DeltaTime, false);

	fRotationScale = fFScale >= 0 ? fRotationScale : fRotationScale * -1;
	
	float YawRotation = GetActorRotation().Yaw + fRotationSpeed * DeltaTime * fRotationScale;
	
	FRotator rotator = FRotator(0.f, YawRotation,0.f);

	SetActorRotation(rotator);

	FVector mousePos = controller->GetMousePos();
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
	FRotator currentRotation = TankTower->GetComponentRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;


	
	TankTower->SetWorldRotation(FMath::Lerp(currentRotation,targetRotation,towerAcceleration*DeltaTime));

	
	
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
