#pragma once

UENUM(BlueprintType, Category = "Card Face")
namespace ECardFace
{
	enum Type
	{
		FaceUp UMETA(DisplayName = "Face Up"),
		FaceDown UMETA(DisplayName = "Face Down")
	};
}
