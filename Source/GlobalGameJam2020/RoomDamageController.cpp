// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomDamageController.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "GameFramework/Actor.h"

// Sets default values
ARoomDamageController::ARoomDamageController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isDamaging = false;
	roomDamageValue = 10;
	timeToDamage = 20;
}

// Called when the game starts or when spawned
void ARoomDamageController::BeginPlay()
{
	Super::BeginPlay();
	
	// Finding the ship event source in the scene
	AActor* foundActor = UGameplayStatics::GetActorOfClass(this->GetWorld(), AShipEvent_Actor::StaticClass());
	shipEventHandler = (AShipEvent_Actor*)foundActor;

	currentDamageTimer = timeToDamage;

	shipEventHandler->OnShipBreakEvent.AddDynamic(this, &ARoomDamageController::RoomBreaking);
	shipEventHandler->OnShipFixEvent.AddDynamic(this, &ARoomDamageController::RoomFixed);
}

// Called every frame
void ARoomDamageController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDamaging)
	{
		currentDamageTimer -= DeltaTime;
		if (currentDamageTimer <= 0)
		{
			// Broadcast the damage done to the ship
			FString roomName = UEnum::GetValueAsString<EventRoom>((EventRoom)roomType);
			shipEventHandler->OnShipDamage.Broadcast(roomName, this->roomDamageValue);

			UE_LOG(LogTemp, Warning, TEXT("Room Broken (%s), Time Ran Out"));

			// Reset the room
			shipEventHandler->OnShipFixEvent.Broadcast(roomType);
		}
	}
}


void ARoomDamageController::RoomBreaking(EventRoom breakingRoomType)
{
	if (breakingRoomType == roomType)
	{
		FString roomName = UEnum::GetValueAsString<EventRoom>((EventRoom)roomType);
		UE_LOG(LogTemp, Warning, TEXT("Room Breaking (%s), Ready To Damage"));

		this->isDamaging = true;
	}
}
void ARoomDamageController::RoomFixed(EventRoom fixedRoomType)
{
	if (fixedRoomType == roomType)
	{
		FString roomName = UEnum::GetValueAsString<EventRoom>(roomType.GetValue());
		UE_LOG(LogTemp, Warning, TEXT("Room Fixed (%s), Reset"));

		this->isDamaging = false;
		currentDamageTimer = timeToDamage;
	}
}