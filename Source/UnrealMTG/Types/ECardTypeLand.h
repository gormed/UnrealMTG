#pragma once

UENUM(BlueprintType, Category = "Card Type")
namespace ECardTypeLand
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		Desert UMETA(DisplayName = "Desert"),
		Forest UMETA(DisplayName = "Forest"),
		Gate UMETA(DisplayName = "Gate"),
		Island UMETA(DisplayName = "Island"),
		Lair UMETA(DisplayName = "Lair"),
		Locus UMETA(DisplayName = "Locus"),
		Mine UMETA(DisplayName = "Mine"),
		Mountain UMETA(DisplayName = "Mountain"),
		Plains UMETA(DisplayName = "Plains"),
		PowerPlant UMETA(DisplayName = "Power-Plant"),
		Swamp UMETA(DisplayName = "Swamp"),
		Tower UMETA(DisplayName = "Tower"),
		Urzas UMETA(DisplayName = "Urza’s")
	};
}
