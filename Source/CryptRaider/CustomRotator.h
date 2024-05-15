// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ActivableInterface.h"

#include "CustomRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UCustomRotator : public UActorComponent, public IActivableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomRotator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldRotate(bool should);

	UFUNCTION(BlueprintCallable)
	void SetTarget(USceneComponent* newTarget);


	virtual void SetActive(bool active) override;

private:
	UPROPERTY(EditAnywhere)
	FVector RotationOffset;

	UPROPERTY(EditAnywhere)
	float RotationTime = 4;

	UPROPERTY(EditAnywhere)
	bool shouldRotate = false;

	USceneComponent* target;
	FRotator OriginalRotation;

	bool activated = false;

};
