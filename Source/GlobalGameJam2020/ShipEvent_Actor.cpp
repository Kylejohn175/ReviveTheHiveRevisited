// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipEvent_Actor.h"

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
}

// Called every frame
void AShipEvent_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EventRoom brokenRoom = EventRoom::ELECTRICITY_ROOM;
	OnShipFixEvent.Broadcast(brokenRoom);
}

