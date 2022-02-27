// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include <DrawDebugHelpers.h>
#include "TankPawn.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("ForwardAxis",this,&AMainPlayerController::OnMoveForward);
	InputComponent->BindAxis("Rotation",this,&AMainPlayerController::OnRotate);
	InputComponent->BindAction("Fire", IE_Pressed,this ,&AMainPlayerController::OnFire);
	InputComponent->BindAction("AlterFire", IE_Pressed,this ,&AMainPlayerController::OnAlterFireOn);
	InputComponent->BindAction("AlterFire", IE_Released,this ,&AMainPlayerController::OnAlterFireOff);
	InputComponent->BindAxis("NextTurret",this ,&AMainPlayerController::OnNextTurret);
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<ATankPawn>(GetPawn());
	this->SetShowMouseCursor(true);
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector MouseDirection;
	DeprojectMousePositionToWorld(MousePosition,MouseDirection);
	auto Z = FMath::Abs(PlayerPawn->GetActorLocation().Z - MousePosition.Z);
	MousePosition = MousePosition - MouseDirection * Z / MouseDirection.Z;
}

void AMainPlayerController::OnMoveForward(float Value)
{
	PlayerPawn->MoveForward(Value);
	
}

void AMainPlayerController::OnRotate(float Value)
{
	PlayerPawn->Rotate(Value);
	
}

void AMainPlayerController::OnFire()
{
	PlayerPawn->Fire();
}

void AMainPlayerController::OnAlterFireOn()
{
	PlayerPawn->AlterFireOn();
}

void AMainPlayerController::OnAlterFireOff()
{
	PlayerPawn->AlterFireOff();
}

void AMainPlayerController::OnNextTurret(float Value)
{
	PlayerPawn->ChangeTowerByInput(Value);
}

