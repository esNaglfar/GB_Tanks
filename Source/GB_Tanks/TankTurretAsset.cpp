// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurretAsset.h"

#include "TankPawn.h"

// Sets default values
ATankTurretAsset::ATankTurretAsset()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	Collision = CreateDefaultSubobject<USphereComponent>("Collision sphere");
	Collision->SetupAttachment(RootComponent);
	
	AssetMesh = CreateDefaultSubobject<UStaticMeshComponent>("Asset Mesh");
	AssetMesh->SetupAttachment(RootComponent);

	Collision->SetCollisionProfileName(FName("OverlapAll"));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetGenerateOverlapEvents(true);

	
}


// Called when the game starts or when spawned
void ATankTurretAsset::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ATankTurretAsset::OnComponentBeginOverlap);
}

void ATankTurretAsset::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!TowerType)
		return;
	if (const auto TankPawn = Cast<ATankPawn>(OtherActor))
	{
		TankPawn->ChangeTower(TowerType);
		this->Destroy();
	}
}

void ATankTurretAsset::FloatAndRotate(float DeltaTime)
{
	auto CurRotation = GetActorRotation();
	CurRotation.Yaw = CurRotation.Yaw + FloatRotationSpeed * DeltaTime;
	SetActorRotation(CurRotation);
}


// Called every frame
void ATankTurretAsset::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FloatAndRotate(DeltaTime);
}

