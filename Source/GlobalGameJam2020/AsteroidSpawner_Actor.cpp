// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidSpawner_Actor.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

#include "Engine/World.h"

#include "Math/RandomStream.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAsteroidSpawner_Actor::AAsteroidSpawner_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsteroidSpawner_Actor::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugSphere(GetWorld(), spawnStartPos, 100, 10, FColor::Red, true);
	DrawDebugCircle(GetWorld(), spawnStartPos, spawnStartRadius, 100, FColor::Red, true, -1.0f, (uint8)'\000', 0.0f, FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 1.0f), true);

	DrawDebugSphere(GetWorld(), spawnStartPos + FVector(0.0f, spawnZoneSize, 0.0f), 100, 10, FColor::Red, true);
	DrawDebugCircle(GetWorld(), spawnStartPos + FVector(0.0f, spawnZoneSize, 0.0f), spawnEndRadius, 100, FColor::Red, true, -1.0f, (uint8)'\000', 0.0f, FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 1.0f), true);

	SpawnAsteroids();
}

void AAsteroidSpawner_Actor::SpawnAsteroids()
{
	for (int i = 0; i < numberOfAsteroids; i++)
	{
		// Initialising Randomisation Possibility
		FRandomStream randomizer = FRandomStream();
		randomizer.GenerateNewSeed();
		float yPoint = randomizer.FRandRange(0.0f, 1.0f);

		// Y Position
		FVector yPos = FVector::ZeroVector;
		yPos.Y = (yPoint * spawnZoneSize) + spawnStartPos.Y;

		// X & Z Position
		float currentPointRadius = ((spawnEndRadius - spawnStartRadius) * yPoint) + spawnStartRadius;

		randomizer.GenerateNewSeed();
		float xPoint = randomizer.FRandRange(-1.0f, 1.0f);
		randomizer.GenerateNewSeed();
		float zPoint = randomizer.FRandRange(-1.0f, 1.0f);


		FVector xzPos = FVector::ZeroVector;
		xzPos.X = xPoint;
		xzPos.Z = zPoint;

		if (xzPos.Size() > 1)
		{
			xzPos.Normalize();
		}
		xzPos *= currentPointRadius;

		// New Position
		FVector newPos = xzPos + yPos;
		AAsteroid_Actor* newAsteroid = GetWorld()->SpawnActor<AAsteroid_Actor>(asteroidBP, FVector::ZeroVector, FRotator::ZeroRotator);
		if (newAsteroid)
		{
			FString debug = "New Asteroid: " + newPos.ToString();
			GLog->Log(debug);

			newAsteroid->SetActorLocation(newPos);
		}
	}
}


// Called every frame
void AAsteroidSpawner_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

