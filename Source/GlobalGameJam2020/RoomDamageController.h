// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipEvent_Actor.h"
#include "RoomDamageController.generated.h"

UCLASS()
class GLOBALGAMEJAM2020_API ARoomDamageController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomDamageController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		AShipEvent_Actor* shipEventHandler;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EventRoom> roomType;

	// Event Handling
	UFUNCTION()
		void RoomBreaking(EventRoom breakingRoomType);
	UFUNCTION()
		void RoomFixed(EventRoom fixedRoomType);

	// Damage Details
	UPROPERTY(EditAnywhere)
		bool isDamaging;
	UPROPERTY(EditAnywhere)
		float timeToDamage;
	float currentDamageTimer;
	UPROPERTY(EditAnywhere)
		float roomDamageValue;
};
