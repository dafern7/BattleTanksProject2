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
	
};
