#pragma once

UENUM(BlueprintType, Category = "Srcyfall Meta")
namespace ECardComponentType
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		ComboPiece UMETA(DisplayName = "Combo Piece"),
		Token UMETA(DisplayName = "Token"),
	};
}
