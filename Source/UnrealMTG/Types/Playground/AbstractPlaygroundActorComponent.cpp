// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractPlaygroundActorComponent.h"

#include "MTGBattlefieldActorComponent.h"
#include "MTGCommadActorComponent.h"
#include "MTGExileActorComponent.h"
#include "MTGGraveyardActorComponent.h"
#include "MTGHandActorComponent.h"
#include "MTGLibraryActorComponent.h"
#include "MTGStackActorComponent.h"

// Sets default values for this component's properties
UAbstractPlaygroundActorComponent::UAbstractPlaygroundActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbstractPlaygroundActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbstractPlaygroundActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

template<class T>
bool UAbstractPlaygroundActorComponent::CheckPlaygroundComponent(
	T*& outType
) {
	T* playgoundType = Cast<T>(this);
	if (playgoundType == NULL)
	{
		UE_LOG(LogMTGAction, Error, TEXT("The playgoundType is not of the required type!"));
		outType = NULL;
		return false;
	}
	outType = playgoundType;
	return this->IsA(T::StaticClass());
}

bool UAbstractPlaygroundActorComponent::MoveCards(
	UAbstractPlaygroundActorComponent* source,
	TSet<ACard*> moveCards,
	FMoveAction action
) {
	// return false for a invalid source!
	if (source == NULL)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid source, make sure it is not NULL (%s)!"), *GetName());
		return false;
	}
	// return false for a invalid moveCards!
	if (moveCards.Num() == 0)
	{
		UE_LOG(LogMTGAction, Error, TEXT("No moveCards given to move (%s)!"), *GetName());
		return false;
	}
	if (source->OwningCharacter == OwningCharacter) {
		UMTGBattlefieldActorComponent* battlefield;
		UMTGCommadActorComponent* command;
		UMTGExileActorComponent* exile;
		UMTGGraveyardActorComponent* graveyard;
		UMTGHandActorComponent* hand;
		UMTGLibraryActorComponent* library;
		UMTGStackActorComponent* stack;

		if (source->CheckPlaygroundComponent<UMTGBattlefieldActorComponent>(battlefield)) {
			return battlefield->CastCards(this, moveCards, action.CardFace);
		}
		if (source->CheckPlaygroundComponent<UMTGCommadActorComponent>(command)) {
			return command->CastCards(this, moveCards, action.CardFace);
		}
		if (source->CheckPlaygroundComponent<UMTGExileActorComponent>(exile)) {
			return exile->PutCards(this, moveCards, action.StackSide);
		}
		if (source->CheckPlaygroundComponent<UMTGGraveyardActorComponent>(graveyard)) {
			return graveyard->PutCards(this, moveCards, action.StackSide);
		}
		if (source->CheckPlaygroundComponent<UMTGLibraryActorComponent>(library)) {
			return library->PutCards(this, moveCards, action.StackSide);
		}
		if (source->CheckPlaygroundComponent<UMTGHandActorComponent>(hand)) {
			
		}
		if (source->CheckPlaygroundComponent<UMTGStackActorComponent>(stack)) {
			
		}
	}
	return false;
}