#pragma once

#include "CoreMinimal.h"

#include "FCardSearchData.generated.h"

USTRUCT(BlueprintType)
struct FCardSearchData
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Search")
	FString CardId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Search")
	FString CardName;

	FCardSearchData() {
		CardId = "";
		CardName = "";
	}
};
