#pragma once

#include "CoreMinimal.h"

#include "FMTGDeckPlayset.generated.h"

class ACard;

USTRUCT(BlueprintType)
struct FMTGDeckPlayset
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG Deck")
	TSubclassOf<ACard> CardClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG Deck")
	int32 Count;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG Deck")
	TSet<ACard*> Cards;
};
