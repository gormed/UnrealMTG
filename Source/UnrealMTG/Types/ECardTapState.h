#pragma once

UENUM(BlueprintType, Category = "Card Tap State")
namespace ECardTapState
{
	enum Type
	{
		Untapped UMETA(DisplayName = "Untapped"),
		Tapped UMETA(DisplayName = "Tapped")
	};
}
