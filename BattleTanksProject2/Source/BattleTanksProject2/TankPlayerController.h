// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKSPROJECT2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void Tick(float DeltaTime) override;
	void BeginPlay() override;

private:

	ATank* GetControlledTank() const;
	void AimTowardsCrosshair(); //start tank moving barrel so a shot will hit where crosshair intersects
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;

	//deprojecting
	bool GetWorldDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;
	bool GetLookVectorHitLocation(FVector WorldDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
