// Fill out your copyright notice in the Description page of Project Settings.


#include "WaypointMark.h"

// Sets default values
AWaypointMark::AWaypointMark()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	Mark = CreateDefaultSubobject<UStaticMeshComponent>("Mark");
	Mark->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWaypointMark::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaypointMark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

