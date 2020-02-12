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
	UPROPERTY(EditAnywhere)
		FVector spawnStartPos;
	UPROPERTY(EditAnywhere)
		float spawnStartRadius;

	UPROPERTY(EditAnywhere)
		float spawnZoneSize;
	UPROPERTY(EditAnywhere)
		float spawnEndRadius;

	UPROPERTY(EditAnywhere)
		int numberOfAsteroids;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AAsteroid_Actor> asteroidBP;

	void SpawnAsteroids();
};