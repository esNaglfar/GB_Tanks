// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destroyable.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GB_TANKS_API UHealthSystem : public UActorComponent
{
	GENERATED_BODY()

		DECLARE_EVENT(FHealthSystem, FOnDie)
		DECLARE_EVENT_OneParam(FHealthSystem, FOnHealthChanged, float)

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Health")
	float MaxHealth = 100.f;
	
	UPROPERTY()
	float Health;

public:	
	// Sets default values for this component's properties
	UHealthSystem();

	FOnDie OnDie;
	FOnHealthChanged OnDamage;

	void TakeDamage(float Amount);
	float GetHealth() const;
	float GetHealthState() const;
	void AddHealth(float Amount);
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
