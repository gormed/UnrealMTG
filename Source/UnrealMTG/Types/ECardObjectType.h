#pragma once

UENUM(BlueprintType, Category = "Scryfall Meta")
namespace ECardObjectType
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		Card UMETA(DisplayName = "Card"),
		RelatedCard UMETA(DisplayName = "Related Card"),
		CardFace UMETA(DisplayName = "Card Face"),
		CardPart UMETA(DisplayName = "Card Part"),
	};
}
