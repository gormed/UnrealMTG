#pragma once

UENUM(BlueprintType, Category = "Card Type")
namespace ECardSupertype
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		Basic UMETA(DisplayName = "Basic"),
		Legendary UMETA(DisplayName = "Legendary"),
		Snow UMETA(DisplayName = "Snow"),
		World UMETA(DisplayName = "World")
	};
}
