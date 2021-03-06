// Fill out your copyright notice in the Description page of Project Settings.

#include "MTGLibraryActorComponent.h"

#include "UnrealMTG/ACard.h"

// Sets default values for this component's properties
UMTGLibraryActorComponent::UMTGLibraryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMTGLibraryActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMTGLibraryActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UMTGLibraryActorComponent::Init(TSet<ACard*> Deck)
{
	for (auto Card : Deck) {
		Card->OwningCharacter = OwningCharacter;
	}
	Cards.Append(Deck);
	return true;
}

