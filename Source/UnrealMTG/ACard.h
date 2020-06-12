// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//HTTP
#include "Http.h"

#include "Types/ECardObjectType.h"
#include "Types/ECardColorFragment.h"
#include "Types/ECardObjectType.h"
#include "Types/ECardLayoutType.h"

#include "Types/FCardTypeDef.h"
#include "Types/FCardManaCost.h"
#include "Types/FCardPart.h"
#include "Types/FCardFace.h"
#include "Types/FCardCounter.h"

#include "ACard.generated.h"

UCLASS()
class UNREALMTG_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// Initializes a card from URI (Can be overridden by Blueprint!)
	UFUNCTION(BlueprintCallable, Category = "Card", meta = (DisplayName = "Init Card"))
	void InitCard(const FString& CardId);

	/// Implement this event in Blueprints
	// UFUNCTION(BlueprintImplementableEvent, Category = "Victory PC", meta = (DisplayName = "Card Data Received"))
	// void CardDataReceived(const FString& JSON);

	void HTTPOnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/// Scryfall object: 'card'
	UPROPERTY(BlueprintReadOnly, Category = "Card")
	TEnumAsByte<ECardObjectType::Type> ObjectType;

	/// Printed Language
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	FString Language;

	/// Scryfall id
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	FString Id;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	FString Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	TEnumAsByte<ECardLayoutType::Type> Layout;

	/// Mana costs struct
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	FCardManaCost ManaCost;

	/// Converted Mana Costs
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	int32 CMC;

	/// The cards colors
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	TArray<TEnumAsByte<ECardColorFragment::Type>> CardColors;

	/// The cards color identity
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	TArray<TEnumAsByte<ECardColorFragment::Type>> ColorIdentity;

	/// The card type as a struct
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	FCardTypeDef Type;

	/// The cards parts if any
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	TArray<FCardPart> Parts;

	/// The cards faces if any
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	TArray<FCardFace> Faces;

	/// The card text if any
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	FString OracleText;

	// The cards power if it is a creature
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	int32 Power;

	// The cards toughness if it is a creature
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	int32 Toughness;

	/// The cards counters if any
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	TArray<FCardCounter> Counter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Card")
	ACharacter* OwningPlayer;

private:

	TArray<FString> CardCache;

	bool FetchCard(const FString& id);

	bool NotCached(const FString& id);
	
	bool CachedFileExists(const FString& id);

	FString CachedFilePath(const FString& id);

	void LoadCardFromCache(const FString& id);

	bool SaveCardToCache(const FString& id, const FString& jsonString);

	bool GenerateFromJsonString(FString& id, FString& json);

	bool LoadCardFromJson(FString& id, TSharedPtr<FJsonObject> JsonObject);

	FString LoadJsonFile(const FString& id);
};
