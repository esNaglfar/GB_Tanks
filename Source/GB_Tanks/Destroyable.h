// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Destroyable.generated.h"

USTRUCT()
struct FDamageInfo
{
	GENERATED_BODY()
public:
	float DamageAmount;
	AActor* DamageSource;
	AActor* DamageSourceOwner;
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDestroyable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GB_TANKS_API IDestroyable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void TakeDamage(FDamageInfo Info) = 0;	
};
