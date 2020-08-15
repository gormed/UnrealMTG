#pragma once

#include "CoreMinimal.h"

#include "FCardIdentifier.generated.h"

USTRUCT(BlueprintType)
struct FCardIdentifier
{
	GENERATED_BODY();

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Identifier")
	FString Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Identifier")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Identifier")
	FString MtgoId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Identifier")
	FString MultiverseId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Identifier")
	FString OracleId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Identifier")
	FString IllustrationId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Identifier")
	FString Set;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Identifier")
	FString CollectorNumber;

	FCardIdentifier() {
		Id = "";
		Name = "";
		MtgoId = "";
		OracleId = "";
		IllustrationId = "";
		Set = "";
		CollectorNumber = "";
	}
};
