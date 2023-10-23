// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = OriginalLocation + MoveOffset;
	float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;


	if (ShouldMove)
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);
	}

	APawn* CharacterPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FVector MyCharacterPosition = CharacterPawn->GetActorLocation();
	float distanceFromCharacter = FVector::Distance(OriginalLocation, MyCharacterPosition);


	//TArray <UActorComponent*> components = CharacterPawn->GetComponentsByClass(UMainCharacter::StaticClass());

	//for (UActorComponent* component : components)
	//{
	//	UMainCharacter* MainCharacter = Cast<UMainCharacter>(component);
	//	if (MainCharacter)
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Found Component"));
	//	}
	//}

	if (distanceFromCharacter < 1000)
	{

	}

	UActorComponent* component =  CharacterPawn->GetComponentByClass(UMainCharacter::StaticClass());
	if (component)
	{
		UMainCharacter* MainCharacter = Cast<UMainCharacter>(component);
		if (MainCharacter)
		{
			MainCharacter->SayHello();

		}
	}

}

