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
	InputComponent->BindAction("AlterFire", IE_Pressed,this ,&AMainPlayerController::OnAlterFire);
	InputComponent->BindAction("NextTurret", IE_Pressed,this ,&AMainPlayerController::OnNextTurret);
	InputComponent->BindAction("PrevTurret", IE_Pressed,this ,&AMainPlayerController::OnPrevTurret);
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	playerPawn = Cast<ATankPawn>(GetPawn());
	this->SetShowMouseCursor(true);
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePosition,mouseDirection);
	FVector PawnPos = playerPawn->GetActorLocation();
	MousePosition.Z = PawnPos.Z;
	FVector Dir = MousePosition - PawnPos;
	Dir.Normalize();
	MousePosition = PawnPos + Dir * 1000.f;
}

void AMainPlayerController::OnMoveForward(float value)
{
	playerPawn->MoveForward(value);
	
}

void AMainPlayerController::OnRotate(float value)
{
	playerPawn->Rotate(value);
	
}

void AMainPlayerController::OnFire()
{
	playerPawn->Fire();
}

void AMainPlayerController::OnAlterFire()
{
	playerPawn->AlterFire();
}

void AMainPlayerController::OnPrevTurret()
{
	
}

void AMainPlayerController::OnNextTurret()
{
}

