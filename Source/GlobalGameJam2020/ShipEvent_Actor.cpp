// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipEvent_Actor.h"

#include "Math/RandomStream.h"

// Sets default values
AShipEvent_Actor::AShipEvent_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShipEvent_Actor::BeginPlay()
{
	Super::BeginPlay();

	currentBreakTime = timeBetweenShipBreakages;
}

// Called every frame
void AShipEvent_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentBreakTime -= DeltaTime;
	if (currentBreakTime < 0)
	{
		// Initialising Randomisation Possibility
		FRandomStream randomizer = FRandomStream();
		randomizer.GenerateNewSeed();

		// Getting new random break event
		int r = randomizer.RandRange(0, 11);
		EventRoom breakingRoom = (EventRoom)r;
		FString roomName = UEnum::GetValueAsString<EventRoom>(breakingRoom);

		UE_LOG(LogTemp, Log, TEXT("New Room Broken: %s"), *roomName);

		OnShipBreakEvent.Broadcast(breakingRoom);
		currentBreakTime = timeBetweenShipBreakages;
	}
}

