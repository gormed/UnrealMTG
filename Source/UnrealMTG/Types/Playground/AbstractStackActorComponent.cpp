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
	AMTGPlayerCharacter* Character, 
	bool& bSuccessful,
	const int32 Count /* = 1 */,
	const TEnumAsByte<EStackSide::Type> Side /* = EStackSide::Top */ 
) {
	TSet<ACard*> show;
	bSuccessful = false;

	if (Character == NULL)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid character, make sure it is not NULL (%s)!"), *GetName());
		return show;
	}	
	if (Count <= 0)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid count, must be greater 0 (%s)!"), *GetName());
		return show;
	}
	if (OwningCharacter == Character)
	{
		switch (Side) {
		default:
		case EStackSide::Top:
			for (auto It = Cards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				show.Emplace(card);
			}
			break;
		case EStackSide::Bottom:
			for (auto It = Cards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				show.Emplace(card);
			}
			break;
		}
		bSuccessful = true;
		OnCardsViewed.Broadcast(Character, Count, Side, show);
	}
	return show;
}

TSet<ACard*> UAbstractStackActorComponent::RemoveCards( 
	AMTGPlayerCharacter* Character, 
	bool& bSuccessful, 
	const int32 Count /* = 1 */, 
	const TEnumAsByte<EStackSide::Type> Side /* = EStackSide::Top */
) {
	TSet<ACard*> draw;
	bSuccessful = false;

	if (Character == NULL)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid character, make sure it is not NULL (%s)!"), *GetName());
		return draw;
	}
	if (Count <= 0)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid count, must be greater 0 (%s)!"), *GetName());
		return draw;
	}
	if (OwningCharacter == Character)
	{
		switch (Side) {
		default:
		case EStackSide::Top:
			for (auto It = Cards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				draw.Emplace(card);
				Cards.Remove(card);
			}
			break;
		case EStackSide::Bottom:
			for (auto It = Cards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				draw.Emplace(card);
				Cards.Remove(card);
			}
			break;
		}
		bSuccessful = true;
		OnCardsRemoved.Broadcast(Character, Count, Side, draw);
	}
	return draw;
}

void UAbstractStackActorComponent::PutCards( 
	UAbstractPlaygroundActorComponent* Source, 
	const TSet<ACard *>& PutCards, 
	bool& bSuccessful,
	const TEnumAsByte<EStackSide::Type> Side /* = EStackSide::Top */ 
) {	
	bSuccessful = false;
	// return false for a invalid source!
	if (Source == NULL)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid source, make sure it is not NULL (%s)!"), *GetName());
		return;
	}
	// return false for a invalid card!
	if (PutCards.Num() == 0)
	{
		UE_LOG(LogMTGAction, Error, TEXT("Invalid card, make sure it is not NULL (%s)!"), *GetName());
		return;
	}
	if (OwningCharacter == Source->OwningCharacter)
	{
		switch (Side) {
		default:
		case EStackSide::Top:
			for (auto It = PutCards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				Cards.Emplace(card);
			}
			break;
		case EStackSide::Bottom:
			for (auto It = PutCards.CreateConstIterator(); It; ++It)
			{
				ACard* card = *It;
				Cards.Emplace(card);
			}
			break;
		}
		bSuccessful = true;
		OnCardsPut.Broadcast(Source, PutCards, Side);
	}
	return;
}
