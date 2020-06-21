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

TArray<ACard*> UAbstractStackActorComponent::ViewCards(
	AMTGPlayerCharacter* character,
	int32 count = 1,
	TEnumAsByte<EStackSide::Type> side = EStackSide::Type::Top)
{
	TArray<ACard*> show;
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
				for (int32 Index = 0; Index != Cards.Num(); ++Index)
				{
					show.Emplace(Cards[Index]);
				}
				return show;
			case EStackSide::Type::Bottom:
				for (int32 Index = Cards.Num(); Index != -1; --Index)
				{
					show.Emplace(Cards[Index]);
				}
				return show;
			default:
				UE_LOG(LogMTGAction, Error, TEXT("Invalid stack side (%s)!"), *GetName());
				return show;
		}
	}
	return show;
}

TArray<ACard*> UAbstractStackActorComponent::DrawCards(
	AMTGPlayerCharacter* character,
	int32 count = 1,
	TEnumAsByte<EStackSide::Type> side = EStackSide::Type::Top)
{
	TArray<ACard*> draw;
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
			for (int32 Index = 0; Index != Cards.Num(); ++Index)
			{
				draw.Emplace(Cards[Index]);
				Cards.RemoveAt(Index);
			}
			return draw;
		case EStackSide::Type::Bottom:
			for (int32 Index = Cards.Num(); Index != -1; --Index)
			{
				draw.Emplace(Cards[Index]);
				Cards.RemoveAt(Index);
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
	const TArray<ACard*>& putCards,
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
			for (int32 Index = 0; Index != putCards.Num(); ++Index)
			{
				Cards.Emplace(putCards[Index]);
			}
			return true;
		case EStackSide::Type::Bottom:
			for (int32 Index = 0; Index != putCards.Num(); ++Index)
			{
				Cards.Emplace(putCards[Index]);
			}
			return true;
		default:
			UE_LOG(LogMTGAction, Error, TEXT("Invalid stack side (%s)!"), *GetName());
			return false;
		}
	}
	return false;
}
