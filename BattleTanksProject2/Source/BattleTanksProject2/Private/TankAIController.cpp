// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTanksProject2.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto PlayerDetected = GetPlayerTank();

	if (!PlayerDetected) {
		UE_LOG(LogTemp, Warning, TEXT("AI Not Detecting Player Tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI detects %s"), *(GetPlayerTank()->GetName()))
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

		//TODO move towards the player
		GetAITank()->AimAt(GetPlayerTank()->GetActorLocation());

		//TODO fire if ready

}

ATank* ATankAIController::GetAITank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerTank);
}



