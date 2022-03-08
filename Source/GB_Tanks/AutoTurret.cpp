// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoTurret.h"

#include "TankPawn.h"


void AAutoTurret::Death()
{
	Tower->Destroy();
	Destroy();
}

void AAutoTurret::DamageTaken(float Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), Amount, HealthSystem->GetHealth());
}

bool AAutoTurret::IsAimed()
{
	auto TurretDirection = Tower->GetActorForwardVector();
	auto EnemyDirection = (Target->GetActorLocation() - GetActorLocation());
	EnemyDirection.Normalize();

	auto angle = FMath::Acos(FVector::DotProduct(TurretDirection,EnemyDirection));

	return angle < Accuracy ? true : false;
}

void AAutoTurret::RotateToTarget()
{
	if(!Tower)
		return;
	if(!Target.IsValid())
		return;
	Tower->RotateTower(Target->GetActorLocation());
	if(IsAimed() && IsTargetInRange())
	Tower->Fire();
}

bool AAutoTurret::IsTargetInRange()
{
	return FVector::Distance(GetActorLocation(), Target->GetActorLocation()) <= TargetingRange;
}

bool AAutoTurret::InLineOfSight()
{
	FHitResult HitResult;

	FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("SightTrace")), true, this);
	Params.bTraceComplex = true;
	Params.bReturnPhysicalMaterial = false;
	Params.bDebugQuery = true;

	FVector start = Tower->GetActorLocation();
	FVector end = Target->GetActorLocation();
	
	if(GetWorld()->LineTraceSingleByChannel(HitResult, start,end, ECC_Visibility, Params))
	{
		return (HitResult.GetActor() == Target) ? true : false;
	}
		return false;
}

void AAutoTurret::TargetEliminated()
{
	
}

void AAutoTurret::GetClosestTarget()
{
	float MinimalRange = 9999999.f;
	for(auto target: Targets)
	{
		float Distance = FVector::Distance(GetActorLocation(), target->GetActorLocation());
		if (Distance < MinimalRange)
		{
			MinimalRange = Distance;
			Target = target;
		}
	}
}

void AAutoTurret::TakeDamage(FDamageInfo Info)
{
	HealthSystem->TakeDamage(Info.DamageAmount);
}

void AAutoTurret::CountScore(FScoreInfo Info)
{
	Score += Info.Points;
	GEngine->AddOnScreenDebugMessage(-1,5, FColor::Green, Info.DestroyedTarget->GetName() + " was killed by " + Info.DestroyerOwner->GetName() + " with " + Info.Destroyer->GetName());
}

int AAutoTurret::GetPoints()
{
	return Points;
}

void AAutoTurret::OnSensorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(static ATankPawn* target = Cast<ATankPawn>(OtherActor))
	{
		if(!target)
			return;
		Targets.AddUnique(target);
		if(!Target.IsValid())
		{
			GetClosestTarget();
		}
	}
}

void AAutoTurret::OnSensorEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)

{
	if(static auto target = Cast<ATankPawn>(OtherActor))
	{
		Targets.Remove(target);
	}
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

	HealthSystem = CreateDefaultSubobject<UHealthSystem>("Health system");
	
	HealthSystem->OnDie.AddUObject(this, &AAutoTurret::Death);
	HealthSystem->OnDamage.AddUObject(this, &AAutoTurret::DamageTaken);
}

// Called when the game starts or when spawned
void AAutoTurret::BeginPlay()
{
	Super::BeginPlay();
	
	auto towerSpawnPointTransform = TowerSlot->GetComponentTransform();
	Tower = GetWorld()->SpawnActor<ATankTowerType>(TowerType, towerSpawnPointTransform);
	Tower->AttachToComponent(TowerSlot, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Tower->bIsTurret = true;
	GetWorld()->GetTimerManager().SetTimer(TargetingHandler,this,&AAutoTurret::RotateToTarget,TargetingSpeed, true, TargetingSpeed);

	FoeDetector->OnComponentBeginOverlap.AddDynamic(this, &AAutoTurret::OnSensorOverlap);
	FoeDetector->OnComponentEndOverlap.AddDynamic(this, &AAutoTurret::OnSensorEndOverlap);

	Target = nullptr;
}

// Called every frame
void AAutoTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1,0,FColor::Yellow,FString::Printf(TEXT("%i"),Targets.Num()));
}

