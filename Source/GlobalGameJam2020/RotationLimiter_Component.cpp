// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationLimiter_Component.h"
#include "GameFramework/Actor.h"

#include "math.h"

// Sets default values for this component's properties
URotationLimiter_Component::URotationLimiter_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotationLimiter_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	startRotation = this->GetOwner()->GetActorRotation();
}


// Called every frame
void URotationLimiter_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FRotator actorRotation = this->GetOwner()->GetActorRotation();

	// XAxis (Roll)
	if (actorRotation.Roll > (startRotation.Roll + rotationLimit))
	{
		actorRotation.Roll = FMath::Lerp(startRotation.Roll + rotationLimit, actorRotation.Roll, 0.02f);
	}
	else if (actorRotation.Roll < (startRotation.Roll - rotationLimit))
	{
		actorRotation.Roll = FMath::Lerp(startRotation.Roll - rotationLimit, actorRotation.Roll, 0.02f);
	}

	// YAxis (Pitch)
	if (actorRotation.Pitch > (startRotation.Pitch + rotationLimit))
	{
		actorRotation.Pitch = FMath::Lerp(startRotation.Pitch + rotationLimit, actorRotation.Pitch, 0.02f);
	}
	else if (actorRotation.Pitch < (startRotation.Pitch - rotationLimit))
	{
		actorRotation.Pitch = FMath::Lerp(startRotation.Pitch - rotationLimit, actorRotation.Pitch, 0.02f);
	}

	// ZAxis (Yaw)
	if (actorRotation.Yaw > (startRotation.Yaw + rotationLimit))
	{
		actorRotation.Yaw = FMath::Lerp(startRotation.Yaw + rotationLimit, actorRotation.Yaw, 0.02f);
	}
	else if (actorRotation.Yaw < (startRotation.Yaw - rotationLimit))
	{
		actorRotation.Yaw = FMath::Lerp(startRotation.Yaw - rotationLimit, actorRotation.Yaw, 0.02f);
	}

	this->GetOwner()->SetActorRotation(actorRotation);
}

