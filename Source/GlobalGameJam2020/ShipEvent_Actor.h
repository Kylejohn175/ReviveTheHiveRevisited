// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipEvent_Actor.generated.h"

UENUM(BlueprintType)
enum EventRoom
{
	RIGHTENGINE_ROOM,
	LEFTENGINE_ROOM,
	ELECTRICITY_ROOM,
	FUEL_ROOM,
	NAVIGATION_ROOM,
	OPERATIONS_ROOM,
	OXYGEN_ROOM,
	PRESSURE_ROOM,
	SHIELDS_ROOM,
	GUN_ROOM,
	LEFTTHRUSTER_ROOM,
	RIGHTTHRUSTER_ROOM,
	OTHER_ROOM
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShipBreakEvent, EventRoom,  eventLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShipFixEvent, EventRoom, eventLocation);

UCLASS()
class GLOBALGAMEJAM2020_API AShipEvent_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipEvent_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EventDispatchers")
		FShipBreakEvent OnShipBreakEvent;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EventDispatchers")
		FShipFixEvent OnShipFixEvent;
};