// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultProjectile.h"

#include "Destroyable.h"

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

void ADefaultProjectile::Launch(AActor* _Owner)
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ADefaultProjectile::Move, MoveRate, true, MoveRate);
	Owner = _Owner;
}

void ADefaultProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto target = Cast<IDestroyable>(OtherActor);
	if(!target)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("%s hitted the %s. "), *GetName(), *OtherActor->GetName());
	FDamageInfo Info;
	Info.DamageAmount = Damage;
	Info.DamageSource = this;
	Info.DamageSourceOwner = Owner;
	target->TakeDamage(Info);
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

