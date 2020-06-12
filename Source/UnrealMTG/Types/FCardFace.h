#pragma once

#include "CoreMinimal.h"

#include "ECardObjectType.h"
#include "ECardColorFragment.h"

#include "FCardTypeDef.h"
#include "FCardManaCost.h"

#include "FCardFace.generated.h"

USTRUCT(BlueprintType)
struct FCardFace
{
	GENERATED_BODY();

public:

	/// Scryfall object: 'card_face'
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	TEnumAsByte<ECardObjectType::Type> ObjectType = ECardObjectType::Type::CardFace;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	FString Name;

	/// The card costs as a struct
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	FCardManaCost ManaCost;

	/// The card type as a struct
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	FCardTypeDef Type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	FString OracleText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	TArray<TEnumAsByte<ECardColorFragment::Type>> CardColors;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	TArray<TEnumAsByte<ECardColorFragment::Type>> ColorIdentity;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	int32 Power = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Face")
	int32 Toughness = 0;
};
