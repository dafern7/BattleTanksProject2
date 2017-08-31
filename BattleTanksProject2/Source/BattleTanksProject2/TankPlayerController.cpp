// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTanksProject2.h"


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}
	


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
	UE_LOG(LogTemp, Error, TEXT("Cannot find a tank"))
	}
	else {
	UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing %s"), *(ControlledTank->GetName()))
	}
	UE_LOG(LogTemp, Warning, TEXT("Player Controller Ready"))
}

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //OutParameter
	if (GetSightRayHitLocation(HitLocation)) {  ///this will ray trace and trace
		GetControlledTank()->AimAt(HitLocation);
	}
	
	
		

}
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation); //viewportsize multiplied by the fraction of the screen that the is located
	///need to find the location of the dot relative to the actual screen, not just the viewport("deproject")
	///these are used for deprojection

	
	FVector WorldDirection;
	if (GetWorldDirection(ScreenLocation, WorldDirection)) {

		GetLookVectorHitLocation(WorldDirection, HitLocation);
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString())
	}
	///line trace along the world direction to catch landscape
	return true;
}

bool ATankPlayerController::GetWorldDirection(FVector2D ScreenLocation, FVector& WorldDirection) const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		WorldDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + WorldDirection*LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		return false;
	}
}