// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/Vector.h"
#include "MovingPlatform.h"

#define OUT

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		if (FVector::Dist(Location, GlobalStartLocation) >= FVector::Dist(GlobalStartLocation, GlobalTargetLocation))
		{
			FVector Temp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Temp;
		}
	
		Location += DeltaTime  * Speed * Direction;
		SetActorLocation(Location);
	}
}
