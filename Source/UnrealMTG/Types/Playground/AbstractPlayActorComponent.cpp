// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractPlayActorComponent.h"

// Sets default values for this component's properties
UAbstractPlayActorComponent::UAbstractPlayActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbstractPlayActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbstractPlayActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UAbstractPlayActorComponent::CastCards(
	class UAbstractPlaygroundActorComponent* source,
	TArray<class ACard*> cards,
	TEnumAsByte<ECardFace::Type> face
) {

}