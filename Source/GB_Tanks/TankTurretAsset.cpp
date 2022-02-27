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

	AssetMesh->OnComponentBeginOverlap.AddDynamic(this, &ATankTurretAsset::OnComponentBeginOverlap);
	AssetMesh->SetCollisionProfileName(FName("OverlapAll"));
	AssetMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AssetMesh->SetGenerateOverlapEvents(true);
	
}


// Called when the game starts or when spawned
void ATankTurretAsset::BeginPlay()
{
	Super::BeginPlay();
}

void ATankTurretAsset::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,20,FColor::Green,"Hit!!!");
	
	Cast<ATankPawn>(OtherActor)->ChangeTower(TowerType);
	
	this->Destroy();
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

