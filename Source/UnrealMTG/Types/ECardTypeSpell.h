#pragma once

UENUM(BlueprintType, Category = "Card Type")
namespace ECardTypeSpell
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		Adventure UMETA(DisplayName = "Adventure"),
		Arcane UMETA(DisplayName = "Arcane"),
		Trap UMETA(DisplayName = "Trap")
	};
}
