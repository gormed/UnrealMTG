
#pragma once

UENUM(BlueprintType, Category = "Card Layout Type")
namespace ECardLayoutType
{
	enum Type
	{
		Normal UMETA(DisplayName = "Normal"),
		Split UMETA(DisplayName = "Split"),
		Transform UMETA(DisplayName = "Transform"),
		Token UMETA(DisplayName = "Token")
	};
}
