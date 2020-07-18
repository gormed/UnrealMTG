// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealMTG/UnrealMTG.h"

#include "MTGSearchObject.h"

void UMTGSearchObject::SearchCard(const FString& Query, bool& bSuccessful, const int32 Page, const FString& Unique, const FString& Order, const FString& Direction)
{
	FHttpModule* Http = &FHttpModule::Get();
	bSuccessful = false;

	if (!Http)
	{
		return;
	}

	if (!Http->IsHttpEnabled())
	{
		return;
	}

	if (Query == "") {
		return;
	}

	FString URL = "https://api.scryfall.com/cards/search?q='" + FGenericPlatformHttp::UrlEncode(Query) + "'";

	if (Page > 0) {
		URL += "&page=" + FString::Printf(TEXT("%d"), Page);
	}
	if (Unique != "") {
		URL += "&unique=" + Unique;
	}
	if (Order != "") {
		URL += "&order=" + Order;
	}
	if (Direction != "") {
		URL += "&dir=" + Direction;
	}

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb("GET");
	Request->SetURL(URL);
	Request->SetHeader("User-Agent", "UnrealMTG/1.0");
	//Request->SetHeader("Upgrade-Insecure-Requests", "1");
	UE_LOG(LogMTGScryfall, Display, TEXT("Scryfall API Call: GET %s"), *URL);

	Request->OnProcessRequestComplete().BindUObject(this, &UMTGSearchObject::HTTPOnResponse_SearchCard);
	if (!Request->ProcessRequest())
	{
		return;
	}

	bSuccessful = true;
}

void UMTGSearchObject::HTTPOnResponse_SearchCard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		const FString requestUrl = Request->GetURL();
		const int32 responseCode = Response->GetResponseCode();
		const FString JSON = Response->GetContentAsString();
		UE_LOG(LogMTGScryfall, Display, TEXT("Scryfall API Response %d to %s\nJSON:\n%s"), responseCode , *requestUrl, *JSON);

		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(*JSON);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
			if (JsonObject->HasField("total_cards") && JsonObject->HasField("data")) {
				TArray<FCardSearchData> cardSearchResults;
				const TArray< TSharedPtr<FJsonValue> > cards = JsonObject->GetArrayField("data");
				if (JsonObject->GetNumberField("total_cards") > 0) {
					for (auto card : cards) {
						const TSharedPtr<FJsonObject> cardObject = card->AsObject();
						if (cardObject->HasField("id") &&
							cardObject->HasField("name")) {
							FCardSearchData cardData;
							cardData.CardId = cardObject->GetStringField("id");
							cardData.CardName = cardObject->GetStringField("name");
							cardSearchResults.Add(cardData);
						}
					}
					OnSearchCardCompleted.Broadcast(cardSearchResults);
				}
			}
		}
		else {
			UE_LOG(LogMTGScryfall, Display, TEXT("UMTGSearchObject::HTTPOnResponse_SearchCard: Failed to parse JSON"));
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("UMTGSearchObject::HTTPOnResponse_SearchCard: Failed to parse JSON"));
			}
		}
	}
	else {
		UE_LOG(LogMTGScryfall, Display, TEXT("UMTGSearchObject::HTTPOnResponse_SearchCard: Request Failed"));
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("UMTGSearchObject::HTTPOnResponse_SearchCard: Request Failed"));
		}
	}
}

void UMTGSearchObject::AutocompleteSearchCard(const FString& Query, bool& bSuccessful)
{
	FHttpModule* Http = &FHttpModule::Get();
	bSuccessful = false;

	if (!Http)
	{
		return;
	}

	if (!Http->IsHttpEnabled())
	{
		return;
	}

	if (Query == "") {
		return;
	}

	FString URL = "https://api.scryfall.com/cards/autocomplete?q='" + FGenericPlatformHttp::UrlEncode(Query) + "'";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb("GET");
	Request->SetURL(URL);
	Request->SetHeader("User-Agent", "UnrealMTG/1.0");
	UE_LOG(LogMTGScryfall, Display, TEXT("Scryfall API Call: GET %s"), *URL);

	Request->OnProcessRequestComplete().BindUObject(this, &UMTGSearchObject::HTTPOnResponse_AutocompleteSearchCard);
	if (!Request->ProcessRequest())
	{
		return;
	}

	bSuccessful = true;
}

void UMTGSearchObject::RandomCard(const FString& Query, bool& bSuccessful, const FString& Face, const FString& Version)
{
	FHttpModule* Http = &FHttpModule::Get();
	bSuccessful = false;

	if (!Http)
	{
		return;
	}

	if (!Http->IsHttpEnabled())
	{
		return;
	}

	if (Query == "") {
		return;
	}

	FString URL = "https://api.scryfall.com/cards/random?q=\"" + Query + "\"";

	if (Face != "") {
		URL += "&face=" + Face;
	}
	if (Version != "") {
		URL += "&version=" + Version;
	}

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb("GET");
	Request->SetURL(URL);
	Request->SetHeader("User-Agent", "UnrealMTG/1.0");
	UE_LOG(LogMTGScryfall, Display, TEXT("Scryfall API Call: GET %s"), *URL);

	Request->OnProcessRequestComplete().BindUObject(this, &UMTGSearchObject::HTTPOnResponse_RandomCard);
	if (!Request->ProcessRequest())
	{
		return;
	}

	bSuccessful = true;
}

void UMTGSearchObject::GetCardCollection(const TArray<FCardIdentifier> Identifiers, bool& bSuccessful)
{
	FHttpModule* Http = &FHttpModule::Get();
	bSuccessful = false;

	if (!Http)
	{
		return;
	}

	if (!Http->IsHttpEnabled())
	{
		return;
	}

	if (Identifiers.Num() == 0) {
		return;
	}

	TSharedPtr<FJsonObject> payloadJson = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> identifiersJson = TArray<TSharedPtr<FJsonValue>>();
	for (FCardIdentifier identifier : Identifiers) {
		TSharedPtr<FJsonObject> identifierJson = MakeShared<FJsonObject>();
		if (identifier.Name != "") {
			identifierJson->SetStringField("name", identifier.Name);
		}
		identifiersJson.Add(MakeShared<FJsonValueObject>(identifierJson));
	}
	payloadJson->SetArrayField("identifiers", identifiersJson);

	FString payloadString = "";
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&payloadString);
	FJsonSerializer::Serialize(payloadJson.ToSharedRef(), Writer);

	FString URL = "https://api.scryfall.com/cards/collection";

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb("POST");
	Request->SetURL(URL);
	Request->SetHeader("User-Agent", "UnrealMTG/1.0");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(payloadString);
	UE_LOG(LogMTGScryfall, Display, TEXT("Scryfall API Call: POST %s %s"), *URL, *payloadString);

	Request->OnProcessRequestComplete().BindUObject(this, &UMTGSearchObject::HTTPOnResponse_GetCardCollection);
	if (!Request->ProcessRequest())
	{
		return;
	}

	bSuccessful = true;
}

void UMTGSearchObject::HTTPOnResponse_AutocompleteSearchCard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString JSON = "{\"error\": \"UMTGSearchObject::HTTPOnResponse_SearchCard\"}";
	if (bWasSuccessful)
	{
		JSON = Response->GetContentAsString();
	}

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JSON);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
		// OnAutocompleteSearchCardCompleted.Broadcast(JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("UMTGSearchObject::HTTPOnResponse_SearchCard: Failed to parse JSON"));
		}
	}
}

void UMTGSearchObject::HTTPOnResponse_RandomCard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString JSON = "{\"error\": \"UMTGSearchObject::HTTPOnResponse_SearchCard\"}";
	if (bWasSuccessful)
	{
		JSON = Response->GetContentAsString();
	}

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JSON);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
		// OnRandomCardCompleted.Broadcast(JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("UMTGSearchObject::HTTPOnResponse_SearchCard: Failed to parse JSON"));
		}
	}
}

void UMTGSearchObject::HTTPOnResponse_GetCardCollection(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString JSON = "{\"error\": \"UMTGSearchObject::HTTPOnResponse_SearchCard\"}";
	if (bWasSuccessful)
	{
		JSON = Response->GetContentAsString();
	}

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JSON);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
		// OnGetCardCollectionCompleted.Broadcast(JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("UMTGSearchObject::HTTPOnResponse_SearchCard: Failed to parse JSON"));
		}
	}
}
