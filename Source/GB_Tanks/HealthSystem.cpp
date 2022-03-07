// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"

#include "TankPawn.h"

// Sets default values for this component's properties
UHealthSystem::UHealthSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealthSystem::TakeDamage(float Amount)
{
	Health = FMath::Clamp(Health - Amount,0.f,MaxHealth);

	if(Health <= 0)
	{
		if(!OnDie.IsBound())
			return;
		OnDie.Broadcast();
	}
	else
	{
		if(!OnDamage.IsBound())
			return;
		OnDamage.Broadcast(Amount);
	}
}

float UHealthSystem::GetHealth() const
{
	return Health;
}

float UHealthSystem::GetHealthState() const
{
	return  Health / MaxHealth;
}

void UHealthSystem::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount,0.f,MaxHealth);
}


// Called when the game starts
void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}


// Called every frame
void UHealthSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

