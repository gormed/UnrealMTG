// Fill out your copyright notice in the Description page of Project Settings.

#include "MTGHandActorComponent.h"

#include "UnrealMTG/ACard.h"
#include "UnrealMTG/UnrealMTG.h"

// Sets default values for this component's properties
UMTGHandActorComponent::UMTGHandActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMTGHandActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMTGHandActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMTGHandActorComponent::ShowHand(TArray<AMTGPlayerCharacter*> ToCharacters)
{

}

void UMTGHandActorComponent::HideHand()
{

}

bool UMTGHandActorComponent::CastCards(UAbstractPlaygroundActorComponent* Target, const TSet<ACard*> CastCards, const FMoveAction Action)
{
	if (!Target) {
		UE_LOG(LogMTGAction, Display, TEXT("UMTGHandActorComponent: Failed to cast cards, invalid target"));
		return false;
	}
	if (Target->OwningCharacter == OwningCharacter) {
		for (auto Card : CastCards)
		{
			Cards.Remove(Card);
			Card->CurrentZone = Target;
		}
		Target->Cards.Append(CastCards);
		OnCastCards.Broadcast(Target, CastCards);
		return true;
	}
	return false;
}

bool UMTGHandActorComponent::DrawCards(UAbstractPlaygroundActorComponent* Source, const TSet<ACard*> CardsToDraw, const FMoveAction Action)
{
	if (!Source) {
		UE_LOG(LogMTGAction, Display, TEXT("UMTGHandActorComponent: Failed to draw cards, invalid source"));
		return false;
	}
	if (Source->OwningCharacter == OwningCharacter) {
		for (auto Card : CardsToDraw)
		{
			Source->Cards.Remove(Card);
			Card->CurrentZone = this;
		}
		Cards.Append(CardsToDraw);
		OnDrawCards.Broadcast(Source, CardsToDraw);
		return true;
	}
	return false;
}
