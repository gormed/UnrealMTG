#pragma once

UENUM(BlueprintType, Category = "Deck Type")
namespace EMTGDeck
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		Standard UMETA(DisplayName = "Standard")
	};
}