#pragma once

UENUM(BlueprintType, Category = "Card Color")
namespace ECardColorFragment
{
	enum Type
	{
		White UMETA(DisplayName = "White"),
		Red UMETA(DisplayName = "Red"),
		Blue UMETA(DisplayName = "Blue"),
		Green UMETA(DisplayName = "Green"),
		Black UMETA(DisplayName = "Black"),
		Colorless UMETA(DisplayName = "Colorless")
	};
}
