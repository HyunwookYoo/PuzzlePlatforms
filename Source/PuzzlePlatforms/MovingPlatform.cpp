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
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		FVector GlobalDirection = GetTransform().InverseTransformPosition(TargetLocation);
		FVector Direction;
		float SizeOfVector;
		TargetLocation.ToDirectionAndLength(OUT Direction, OUT SizeOfVector);

		Location += Direction * Speed * DeltaTime;
		SetActorLocation(Location);
	}
}
