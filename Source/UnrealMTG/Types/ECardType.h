#pragma once

UENUM(BlueprintType, Category = "Card Type")
namespace ECardType
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		Artifact UMETA(DisplayName = "Artifact"),
		Creature UMETA(DisplayName = "Creature"),
		Enchantment UMETA(DisplayName = "Enchantment"),
		Instant UMETA(DisplayName = "Instant"),
		Land UMETA(DisplayName = "Land"),
		Planeswalker UMETA(DisplayName = "Planeswalker"),
		Tribal UMETA(DisplayName = "Tribal"),
		Sorcery UMETA(DisplayName = "Sorcery"),
		VariantCardTypes UMETA(DisplayName = "Variant Card Types"),
		Phenomenon UMETA(DisplayName = "Phenomenon"),
		Vanguards UMETA(DisplayName = "Vanguards"),
		Schemes UMETA(DisplayName = "Schemes")
	};
}
