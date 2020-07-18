// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Http.h"
#include "Types/FCardSearchData.h"
#include "Types/FCardIdentifier.h"

#include "MTGSearchObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearchCardCompletedSignature, const TArray<FCardSearchData>&, CardSearchResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAutocompleteSearchCardCompletedSignature, const TArray<FCardSearchData>&, CardSearchResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRandomCardCompletedSignature, const TArray<FCardSearchData>&, CardSearchResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetCardCollectionCompletedSignature, const TArray<FCardSearchData>&, CardSearchResults);

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALMTG_API UMTGSearchObject : public UObject
{
	GENERATED_BODY()

	//////////////////////////////////////////////////////////////////////////

	/// https://scryfall.com/docs/api/cards/search
	UFUNCTION(BlueprintCallable, Category = "MTG|Card Search", meta = (DisplayName = "Search Card"))
	void SearchCard(const FString& Query, bool& bSuccessful, const int32 Page = 1, const FString& Unique = "cards", const FString& Order = "name", const FString& Direction = "auto");

	/// https://scryfall.com/docs/api/cards/autocomplete
	UFUNCTION(BlueprintCallable, Category = "MTG|Card Search", meta = (DisplayName = "Auto-complete Search Card"))
	void AutocompleteSearchCard(const FString& Query, bool& bSuccessful);

	/// https://scryfall.com/docs/api/cards/random
	UFUNCTION(BlueprintCallable, Category = "MTG|Card Search", meta = (DisplayName = "Random Card"))
	void RandomCard(const FString& Query, bool& bSuccessful, const FString& Face = "", const FString& Version = "large");

	/// https://scryfall.com/docs/api/cards/collection
	UFUNCTION(BlueprintCallable, Category = "MTG|Card Search", meta = (DisplayName = "Get Card Collection"))
	void GetCardCollection(const TArray<FCardIdentifier> Identifiers, bool& bSuccessful);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Card Search")
	FSearchCardCompletedSignature OnSearchCardCompleted;

	UPROPERTY(BlueprintAssignable, Category = "MTG|Card Search")
	FAutocompleteSearchCardCompletedSignature OnAutocompleteSearchCardCompleted;

	UPROPERTY(BlueprintAssignable, Category = "MTG|Card Search")
	FRandomCardCompletedSignature OnRandomCardCompleted;

	UPROPERTY(BlueprintAssignable, Category = "MTG|Card Search")
	FGetCardCollectionCompletedSignature OnGetCardCollectionCompleted;

private:

	void HTTPOnResponse_SearchCard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void HTTPOnResponse_AutocompleteSearchCard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void HTTPOnResponse_RandomCard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void HTTPOnResponse_GetCardCollection(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
