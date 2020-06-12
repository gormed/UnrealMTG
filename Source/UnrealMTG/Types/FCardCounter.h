#pragma once

#include "CoreMinimal.h"

#include "FCardCounter.generated.h"

USTRUCT(BlueprintType)
struct FCardCounter
{
	GENERATED_USTRUCT_BODY();

public:

	// The cards power if it is a creature
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Counter")
	int32 Power = 0;

	// The cards toughness if it is a creature
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Counter")
	int32 Toughness = 0;
};
