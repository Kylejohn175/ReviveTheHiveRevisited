// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomDamageController.h"

// Sets default values
ARoomDamageController::ARoomDamageController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isDamaging = false;
}

// Called when the game starts or when spawned
void ARoomDamageController::BeginPlay()
{
	Super::BeginPlay();
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
			shipEventHandler->OnShipDamage.Broadcast(this->roomType, this->roomDamageValue);
		}
	}
}


void ARoomDamageController::RoomBreaking(EventRoom breakingRoomType)
{
	if (breakingRoomType == roomType)
	{
		isDamaging = true;
	}
}
void ARoomDamageController::RoomFixed(EventRoom fixedRoomType)
{
	if (fixedRoomType == roomType)
	{
		isDamaging = false;
	}
}