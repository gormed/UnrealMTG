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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG Deck")
	TMap<TSubclassOf<ACard>, FMTGDeckPlayset> CardMap;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG Deck")
	TEnumAsByte<EMTGDeck::Type> DeckType = EMTGDeck::Type::Standard;
};
