#pragma once

#include "CoreMinimal.h"

#include "FCardManaCost.generated.h"

USTRUCT(BlueprintType)
struct FCardManaCost
{
	GENERATED_BODY();

public:

	/// Mana costs in the common {} notation
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Mana Costs")
	FString ManaCostLine;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Mana Costs")
	int32 White = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Mana Costs")
	int32 Red = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Mana Costs")
	int32 Blue = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Mana Costs")
	int32 Green = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Mana Costs")
	int32 Black = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Mana Costs")
	int32 Colorless = 0;
};
