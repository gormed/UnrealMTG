// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "IImageWrapperModule.h"

#include "Types/EAbilityKeyword.h"
#include "Types/EActionKeyword.h"
#include "Types/ECardObjectType.h"
#include "Types/ECardColorFragment.h"
#include "Types/ECardObjectType.h"
#include "Types/ECardLayoutType.h"
#include "Types/ECardTapState.h"
#include "Types/ECardSide.h"

#include "Types/FCardTypeDef.h"
#include "Types/FCardManaCost.h"
#include "Types/FCardPart.h"
#include "Types/FCardFace.h"
#include "Types/FCardCounter.h"

#include "ACard.generated.h"

class UAbstractPlaygroundActorComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCardIntitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCardTextureFetched, TEnumAsByte<ECardSide::Type>, CardSide, UTexture2D*, Texture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCardTappedChanged, ACard*, Card, bool, Tapped);

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
	UFUNCTION(BlueprintCallable, Category = "MTG|Card", meta = (DisplayName = "Init Card"))
	void InitCard(const FString& CardId);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Card")
	FCardIntitialized OnCardIntialized;

	/// Implement this event in Blueprints
	// UFUNCTION(BlueprintImplementableEvent, Category = "Victory PC", meta = (DisplayName = "Card Data Received"))
	// void CardDataReceived(const FString& JSON);

	/// Scryfall object: 'card'
	UPROPERTY(BlueprintReadOnly, Category = "MTG|Card")
	TEnumAsByte<ECardObjectType::Type> ObjectType;

	/// Printed Language
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	FString Language;

	/// Scryfall id
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	FString Id;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	FString Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	TEnumAsByte<ECardLayoutType::Type> Layout;

	/// Mana costs struct
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	FCardManaCost ManaCost;

	/// Converted Mana Costs
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	int32 CMC;

	/// The cards colors
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	TArray<TEnumAsByte<ECardColorFragment::Type>> CardColors;

	/// The cards color identity
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	TArray<TEnumAsByte<ECardColorFragment::Type>> ColorIdentity;

	/// The card type as a struct
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	FCardTypeDef Type;
	
	/// The cards tap state
	UPROPERTY(BlueprintReadOnly, Category = "MTG|Card")
	TEnumAsByte<ECardTapState::Type> TapState;

	/// The cards ability keywords
	UPROPERTY(BlueprintReadOnly, Category = "MTG|Card")
	TArray<TEnumAsByte<EAbilityKeyword::Type>> AbilityKeywords;

	/// The cards action keywords
	UPROPERTY(BlueprintReadOnly, Category = "MTG|Card")
	TArray<TEnumAsByte<EActionKeyword::Type>> ActionKeywords;

	/// The cards parts if any
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	TArray<FCardPart> Parts;

	/// The cards faces if any
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	TArray<FCardFace> Faces;

	/// The card text if any
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	FString OracleText;

	/// The cards power if it is a creature
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	int32 Power;

	/// The cards toughness if it is a creature
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	int32 Toughness;

	/// The cards counters if any
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	TArray<FCardCounter> Counter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	class AMTGPlayerCharacter* OwningCharacter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG|Card")
	UAbstractPlaygroundActorComponent* CurrentZone;

	/// Indicate the tapped state
	UPROPERTY(BlueprintReadOnly, Category = "MTG|Card")
	bool bTapped;

	UFUNCTION(BlueprintCallable, Category = "MTG|Card", meta = (DisplayName = "Tap / Untap"))
	void SetTapped(const bool NewTapped);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Card")
	FCardTappedChanged OnCardTappedChanged;

	UFUNCTION(BlueprintCallable, Category = "MTG|Card", meta = (DisplayName = "Fetch Card Image"))
	bool FetchCardTexture(const FString& URL, const TEnumAsByte<ECardSide::Type> CardSide);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Card")
	FCardTextureFetched OnCardTextureFetched;

	UPROPERTY(BlueprintReadWrite, Category = "MTG|Card")
	UTexture2D* FrontSideTexture;

	UPROPERTY(BlueprintReadWrite, Category = "MTG|Card")
	UTexture2D* BackSideTexture;

private:

	TArray<FString> CardCache;

	bool FetchCard(const FString& id);
	void HTTPOnResponse_FetchCard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void HTTPOnResponse_FetchCardImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	FString FetchCardImageUri;
	TEnumAsByte<ECardSide::Type> FetchCardSide;

	bool CardDataNotCached(const FString& id);
	
	bool CachedCardDataFileExists(const FString& id);
	bool CachedCardImageFileExists(const FString& id, TEnumAsByte<ECardSide::Type> CardSide);

	FString CachedFilePath(const FString& id);
	FString CachedImagePath(const FString& id, TEnumAsByte<ECardSide::Type> CardSide);

	void LoadCardFromCache(const FString& id);
	void LoadCardImageFromCache(const FString& id, TEnumAsByte<ECardSide::Type> CardSide);
	UTexture2D* LoadTextureFromFile(const FString& FullFilePath, EImageFormat ImageFormat);

	bool SaveCardToCache(const FString& id, const FString& jsonString);

	bool GenerateFromJsonString(FString& json, FString& OutId);

	bool LoadCardFromJson(TSharedPtr<FJsonObject> JsonObject, FString& OutId);

	FString LoadJsonFile(const FString& id);

	TArray<TEnumAsByte<ECardColorFragment::Type>> ParseColorFragments(const TArray<TSharedPtr<FJsonValue>> colors);
};
