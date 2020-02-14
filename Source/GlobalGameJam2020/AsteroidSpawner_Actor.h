// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid_Actor.h"
#include "AsteroidSpawner_Actor.generated.h"

UCLASS()
class GLOBALGAMEJAM2020_API AAsteroidSpawner_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidSpawner_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Total Zone Parameters
	UPROPERTY(EditAnywhere, Category = "Zone Start Parameters")
		FVector spawnStartPos;
	UPROPERTY(EditAnywhere, Category = "Zone Start Parameters")
		FVector2D startSpawnTimer;
	UPROPERTY(EditAnywhere, Category = "Zone Start Parameters")
		FIntPoint startSpawnRate;

	UPROPERTY(EditAnywhere, Category = "Zone End Parameters")
		FVector spawnEndPos;
	UPROPERTY(EditAnywhere, Category = "Zone End Parameters")
		FVector2D endSpawnTimer;
	UPROPERTY(EditAnywhere, Category = "Zone End Parameters")
		FIntPoint endSpawnRate;


	// Spawning Zone Parameters (Spawns in front of the player ship)
	UPROPERTY(EditAnywhere)
		float spawnStartDistance;
	UPROPERTY(EditAnywhere)
		float spawnStartRadius;
	UPROPERTY(EditAnywhere)
		float spawnEndDistance;
	UPROPERTY(EditAnywhere)
		float spawnEndRadius;

	UPROPERTY(EditAnywhere)
		AActor* playerShip;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAsteroid_Actor> asteroidBP;

	float currentSpawnTime;

	void HandleSpawnTimer(float DeltaTime);
	void SpawnAsteroids(int numberToSpawn);
	
};