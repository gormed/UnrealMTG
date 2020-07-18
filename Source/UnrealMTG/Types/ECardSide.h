#pragma once

UENUM(BlueprintType, Category = "Card Side")
namespace ECardSide
{
	enum Type
	{
		Front UMETA(DisplayName = "Frontside"),
		Back UMETA(DisplayName = "Backside")
	};
}
