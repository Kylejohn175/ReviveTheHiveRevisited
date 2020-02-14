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

	DrawDebugSphere(GetWorld(), spawnEndPos, 100, 10, FColor::Red, true);

	DrawDebugLine(GetWorld(), spawnStartPos, spawnEndPos, FColor::Red, true);
}


// Called every frame
void AAsteroidSpawner_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Start of The Spawn Zone
	FVector spawnZoneStart = playerShip->GetActorLocation();
	spawnZoneStart.Y += spawnStartDistance;
	DrawDebugCircle(GetWorld(), spawnZoneStart, spawnStartRadius, 100, FColor::Red, false, 0.0f, (uint8)'\000', 0.0f, FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 1.0f), true);

	// End of The Spawn Zone
	FVector spawnZoneEnd = playerShip->GetActorLocation();
	spawnZoneEnd.Y += spawnEndDistance;
	DrawDebugCircle(GetWorld(), spawnZoneEnd, spawnEndRadius, 100, FColor::Red, false, 0.0f, (uint8)'\000', 0.0f, FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 1.0f), true);

	DrawDebugLine(GetWorld(), spawnZoneStart, spawnZoneEnd, FColor::Red, false, 0.0f, (uint8)'\000', 0.0f);

	// Asteroid Spawning
	HandleSpawnTimer(DeltaTime);
}


void AAsteroidSpawner_Actor::HandleSpawnTimer(float DeltaTime)
{
	currentSpawnTime -= DeltaTime;
	if (currentSpawnTime < 0)
	{
		// Getting Ship Point Along The Spawnable Zone
		float point = (spawnStartPos.Y - playerShip->GetActorLocation().Y) / (spawnStartPos.Y - spawnEndPos.Y);
		point = FMath::Clamp<float>(point, 0.0f, 1.0f);

		// Initialising Randomisation Possibility
		FRandomStream randomizer = FRandomStream();
		randomizer.GenerateNewSeed();

		// Calculating Number of Asteroids to Spawn
		FVector2D asteroidRange = (endSpawnRate - startSpawnRate);
		asteroidRange.X *= point;
		asteroidRange.Y *= point;

		int asteroidsToSpawn = randomizer.RandRange(asteroidRange.X, asteroidRange.Y);
		SpawnAsteroids(asteroidsToSpawn);


		// Resetting Spawn Timer
		FVector2D timerRange = ((endSpawnTimer - startSpawnTimer) * point) + startSpawnTimer;
		currentSpawnTime = randomizer.FRandRange(timerRange.X, timerRange.Y);
	}
}


void AAsteroidSpawner_Actor::SpawnAsteroids(int numberToSpawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Asteroids: %d"), numberToSpawn);

	// Getting Ship Point Along The Spawnable Zone
	float point = (spawnStartPos.Y - playerShip->GetActorLocation().Y) / (spawnStartPos.Y - spawnEndPos.Y);
	point = FMath::Clamp<float>(point, 0.0f, 1.0f);

	// spawning asteroids
	for (int i = 0; i < numberToSpawn; i++)
	{
		// Setting Up Randomisation Possibility
		FRandomStream randomizer = FRandomStream();
		randomizer.GenerateNewSeed();
		float yPoint = randomizer.FRandRange(0.0f, 1.0f);

		// Y Position
		FVector yPos = FVector::ZeroVector;
		yPos.Y = (((spawnEndDistance - spawnStartDistance) * point) + spawnStartDistance) + playerShip->GetActorLocation().Y;

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
			newAsteroid->SetActorLocation(newPos);
		}
	}
}