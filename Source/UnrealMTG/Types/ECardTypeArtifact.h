#pragma once

UENUM(BlueprintType, Category = "Card Type")
namespace ECardTypeArtifact
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		Clue UMETA(DisplayName = "Clue"),
		Contraption UMETA(DisplayName = "Contraption"),
		Equipment UMETA(DisplayName = "Equipment"),
		Food UMETA(DisplayName = "Food"),
		Fortification UMETA(DisplayName = "Fortification"),
		Gold UMETA(DisplayName = "Gold"),
		Treasure UMETA(DisplayName = "Treasure"),
		Vehicle UMETA(DisplayName = "Vehicle")
	};
}
