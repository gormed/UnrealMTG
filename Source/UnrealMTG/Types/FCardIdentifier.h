#pragma once

#include "CoreMinimal.h"

#include "FCardIdentifier.generated.h"

USTRUCT(BlueprintType)
struct FCardIdentifier
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Identifier")
	FString Id;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Identifier")
	FString Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Identifier")
	FString MtgoId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Identifier")
	FString MultiverseId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Identifier")
	FString OracleId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Identifier")
	FString IllustrationId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Identifier")
	FString Set;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card Identifier")
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
