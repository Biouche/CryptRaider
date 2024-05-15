// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomRotator.h"

// Sets default values for this component's properties
UCustomRotator::UCustomRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomRotator::BeginPlay()
{
	Super::BeginPlay();



}


// Called every frame
void UCustomRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!target)
		UE_LOG(LogTemp, Display, TEXT("[UCustomRotator] No target "));
	if (target && shouldRotate)
	{
		if (!activated)
		{
			activated = true;

			OriginalRotation = target->GetRelativeRotation();
		}

		// Rotation
		FVector currentRotation = target->GetRelativeRotation().Euler();
		FVector targetRotation = OriginalRotation.Euler() + RotationOffset;

		float rotationSpeed = FVector::Distance(OriginalRotation.Euler(), targetRotation) / RotationTime;
		FVector newRotation = FMath::VInterpConstantTo(currentRotation, targetRotation, DeltaTime, rotationSpeed);


		target->SetRelativeRotation(FRotator::MakeFromEuler(newRotation));
	}
}

void UCustomRotator::SetTarget(USceneComponent* newTarget)
{
	target = newTarget;
}

void UCustomRotator::SetShouldRotate(bool should)
{
	shouldRotate = should;
}

void UCustomRotator::SetActive(bool active)
{
	shouldRotate = active;
}

