// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoTurret.h"

#include "TankPawn.h"


bool AAutoTurret::IsAimed()
{
	return false;
}

void AAutoTurret::RotateToTarget()
{
	if(!Target)
		return;
	Tower->RotateTower(Target->GetActorLocation());
	if(IsAimed())
	Tower->Fire();
}

bool AAutoTurret::IsTargetInRange()
{
	return (GetActorLocation() - Target->GetActorLocation()).Size() <= TargetingRange;
}

void AAutoTurret::TargetEliminated()
{
}

void AAutoTurret::OnSensorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,5, FColor::Red,"ENEMY HERE!!!");
	
	if(!Cast<ATankPawn>(OtherActor))
		return;

	Target = OtherActor;
}

// Sets default values
AAutoTurret::AAutoTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret mesh");
	TowerMesh->SetupAttachment(RootComponent);

	TowerSlot = CreateDefaultSubobject<UArrowComponent>("Turret slot");
	TowerSlot -> SetupAttachment(TowerMesh);

	FoeDetector = CreateDefaultSubobject<USphereComponent>("Foe Detector");
	FoeDetector->SetupAttachment(RootComponent);
	FoeDetector->SetSphereRadius(TargetingRange);
	FoeDetector->OnComponentBeginOverlap.AddDynamic(this, &AAutoTurret::OnSensorOverlap); // <------------------- НЕ ГЕНЕРИТ СОБЫТИЯ
	FoeDetector->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void AAutoTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TargetingHandler,this,&AAutoTurret::RotateToTarget,TargetingSpeed, true, TargetingSpeed);
	auto towerSpawnPointTransform = TowerSlot->GetComponentTransform();
	auto tankTower = GetWorld()->SpawnActor<ATankTowerType>(TowerType, towerSpawnPointTransform);
	tankTower->AttachToComponent(TowerSlot, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called every frame
void AAutoTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

