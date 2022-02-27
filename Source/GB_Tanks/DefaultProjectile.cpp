// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultProjectile.h"

// Sets default values
ADefaultProjectile::ADefaultProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ADefaultProjectile::OnMeshOverlapBegin);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	
}

void ADefaultProjectile::Launch()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ADefaultProjectile::Move, MoveRate, true, MoveRate);
}

void ADefaultProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("%s hitted the %s. "), *GetName(), *OtherActor->GetName());
	OtherActor->Destroy();
	this->Destroy();
}

void ADefaultProjectile::Move()
{
	FVector targetPos = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(targetPos);
}

// Called when the game starts or when spawned
void ADefaultProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

