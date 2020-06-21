// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractStackActorComponent.h"

// Sets default values for this component's properties
UAbstractStackActorComponent::UAbstractStackActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbstractStackActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbstractStackActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TSet<ACard*> UAbstractStackActorComponent::ViewCards(
	AMTGPlayerCharacter* character,
	int32 count = 1,
	TEnumAsByte<EStackSide::Type> side = EStackSide::Type::Top)
{
	TSet<ACard*> show;
	// return false for a invalid character!
	if (character == NULL)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid character, make sure it is not NULL (%s)!"), *GetName());
		return show;
	}	
	if (count <= 0)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid count, must be greater 0 (%s)!"), *GetName());
		return show;
	}
	if (OwningCharacter == character)
	{
		switch (side) {
			case EStackSide::Type::Top:
				for (auto It = Cards.CreateConstIterator(); It; ++It)
				{
					ACard* card = *It;
					show.Emplace(card);
				}
				return show;
			case EStackSide::Type::Bottom:
				for (auto It = Cards.CreateConstIterator(); It; ++It)
				{
					ACard* card = *It;
					show.Emplace(card);
				}
				return show;
			default:
				UE_LOG(LogMTGAction, Error, TEXT("Invalid stack side (%s)!"), *GetName());
				return show;
		}
	}
	return show;
}

TSet<ACard*> UAbstractStackActorComponent::DrawCards(
	AMTGPlayerCharacter* character,
	int32 count = 1,
	TEnumAsByte<EStackSide::Type> side = EStackSide::Type::Top)
{
	TSet<ACard*> draw;
	// return false for a invalid character!
	if (character == NULL)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid character, make sure it is not NULL (%s)!"), *GetName());
		return draw;
	}
	if (count <= 0)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid count, must be greater 0 (%s)!"), *GetName());
		return draw;
	}
	if (OwningCharacter == character)
	{
		switch (side) {
		case EStackSide::Type::Top:
			for (auto It = Cards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				draw.Emplace(card);
				Cards.Remove(card);
			}
			return draw;
		case EStackSide::Type::Bottom:
			for (auto It = Cards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				draw.Emplace(card);
				Cards.Remove(card);
			}
			return draw;
		default:
			UE_LOG(LogMTGAction, Error, TEXT("Invalid stack side (%s)!"), *GetName());
			return draw;
		}
	}
	return draw;
}

bool UAbstractStackActorComponent::PutCards(
	UAbstractPlaygroundActorComponent* source,
	const TSet<ACard*>& putCards,
	TEnumAsByte<EStackSide::Type> side = EStackSide::Type::Top)
{	
	// return false for a invalid source!
	if (source == NULL)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid source, make sure it is not NULL (%s)!"), *GetName());
		return false;
	}
	// return false for a invalid card!
	if (putCards.Num() == 0)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid card, make sure it is not NULL (%s)!"), *GetName());
		return false;
	}
	if (OwningCharacter == source->OwningCharacter)
	{
		switch (side) {
		case EStackSide::Type::Top:
			for (auto It = putCards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				Cards.Emplace(card);
			}
			return true;
		case EStackSide::Type::Bottom:
			for (auto It = putCards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				Cards.Emplace(card);
			}
			return true;
		default:
			UE_LOG(LogMTGAction, Error, TEXT("Invalid stack side (%s)!"), *GetName());
			return false;
		}
	}
	return false;
}
