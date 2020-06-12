#pragma once

#include "CoreMinimal.h"

#include "ECardType.h"

#include "ECardSupertype.h"

#include "ECardTypeCreature.h"
#include "ECardTypeArtifact.h"
#include "ECardTypeSpell.h"
#include "ECardTypeEnchantment.h"
#include "ECardTypePlaneswalker.h"
#include "ECardTypeLand.h"

#include "FCardTypeDef.generated.h"

USTRUCT(BlueprintType)
struct FCardTypeDef
{
	GENERATED_BODY();

public:

	/// The card type as a <Supertype> <Type> - <Subtype> string
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	FString TypeLine;

	/// First type of a permanent
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	TEnumAsByte<ECardType::Type> Type = ECardType::Type::None;

	/// Optional supertype of a permanent
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	TEnumAsByte<ECardSupertype::Type> Supertype = ECardSupertype::Type::None;

	// Optional subtype of a permanent

	/// Optional creature subtype
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	TEnumAsByte<ECardTypeCreature::Type> CreatureType = ECardTypeCreature::Type::None;

	/// Optional artifact subtype
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	TEnumAsByte<ECardTypeArtifact::Type> ArtifactType = ECardTypeArtifact::Type::None;

	/// Optional spell subtype
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	TEnumAsByte<ECardTypeSpell::Type> SpellType = ECardTypeSpell::Type::None;

	/// Optional enchantment subtype
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	TEnumAsByte<ECardTypeEnchantment::Type> EnchantmentType = ECardTypeEnchantment::Type::None;

	/// Optional planeswalker subtype
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	TEnumAsByte<ECardTypePlaneswalker::Type> PlaneswalkerType = ECardTypePlaneswalker::Type::None;

	/// Optional land subtype
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Type")
	TEnumAsByte<ECardTypeLand::Type> LandType = ECardTypeLand::Type::None;
};
