#pragma once

#include "CoreMinimal.h"
#include "FMTGDeckPlayset.generated.h"

class ACard;

USTRUCT(BlueprintType)
struct FMTGDeckPlayset
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MTG Deck")
	ACard* Representative;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MTG Deck")
	int32 Count;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MTG Deck")
	TSet<ACard*> Cards;

	FMTGDeckPlayset() {
		Representative = NULL;
		Count = 0;
	}
};
