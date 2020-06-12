#pragma once

#include "CoreMinimal.h"

#include "ECardObjectType.h"
#include "ECardComponentType.h"

#include "FCardTypeDef.h"

#include "FCardPart.generated.h"

USTRUCT(BlueprintType)
struct FCardPart
{
	GENERATED_BODY();

public:

	/// Scryfall object: 'card_part'
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Part")
	TEnumAsByte<ECardObjectType::Type> ObjectType = ECardObjectType::Type::None;

	/// Scryfall component
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Part")
	TEnumAsByte<ECardComponentType::Type> ComponentType = ECardComponentType::Type::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Part")
	FString Name;

	/// The card type as a struct
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Part")
	FCardTypeDef Type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Part")
	FString URI;
};
