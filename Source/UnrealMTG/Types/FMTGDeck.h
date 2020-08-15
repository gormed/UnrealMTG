#pragma once

#include "CoreMinimal.h"
#include "EMTGDeck.h"
#include "FMTGDeckPlayset.h"

#include "FMTGDeck.generated.h"

class ACard;

USTRUCT(BlueprintType)
struct FMTGDeck
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MTG Deck")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MTG Deck")
	TSet<FMTGDeckPlayset> CardMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MTG Deck")
	TEnumAsByte<EMTGDeck::Type> DeckType = EMTGDeck::Type::Standard;

	FMTGDeck() {
		Name = "Untitled";
	}
};
