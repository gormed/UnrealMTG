#pragma once

#include "CoreMinimal.h"
#include "EStackSide.h"
#include "ECardFace.h"

#include "FMoveAction.generated.h"

USTRUCT(BlueprintType)
struct FMoveAction
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG Action")
	TEnumAsByte<EStackSide::Type> StackSide = EStackSide::Type::Top;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG Action")
	TEnumAsByte<ECardFace::Type> CardFace = ECardFace::Type::FaceUp;
};
