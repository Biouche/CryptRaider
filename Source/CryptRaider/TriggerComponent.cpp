// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* acceptableActor = GetAcceptableActor();
	if (acceptableActor != nullptr)
	{
		UPrimitiveComponent* comp = Cast<UPrimitiveComponent>(acceptableActor->GetRootComponent());

		if (comp != nullptr)
		{
			comp->SetSimulatePhysics(false);
		}
		comp->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

		UE_LOG(LogTemp, Log, TEXT("Unlocking"));
		mover->SetShouldMove(true);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Relocking"));
		mover->SetShouldMove(false);
	}
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);

	for (AActor* actor : actors)
	{
		if (actor->ActorHasTag(UnlockingTag))
		{
			return actor;
		}

	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* newMover)
{
	mover = newMover;
}