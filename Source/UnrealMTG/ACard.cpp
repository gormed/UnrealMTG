// Fill out your copyright notice in the Description page of Project Settings.


#include "ACard.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFilemanager.h"

// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ObjectType = ECardObjectType::Type::Card;
	this->CardCache = TArray<FString>();
}

void ACard::InitCard(const FString& CardId)
{
	this->Id = CardId;
	if (this->NotCached(this->Id)) {
		this->FetchCard(this->Id);
	}
	else
	{
		this->LoadCardFromCache(this->Id);
	}
}

bool ACard::SaveCardToCache(const FString& id, const FString& jsonString)
{
	FString cachedFile = this->CachedFilePath(id);
	this->CardCache.Add(id);
	return FFileHelper::SaveStringToFile(jsonString, *cachedFile);
}

void ACard::LoadCardFromCache(const FString& id)
{
	if (!this->CachedFileExists(id)) {
		return;
	}
	FString json = this->LoadJsonFile(id);
	FString outId;
	if (this->GenerateFromJsonString(outId, json)) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Loaded card from cache"));
		}
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Failed to load card from cache"));
		}
	}
}

bool ACard::GenerateFromJsonString(FString& id, FString& json)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(json);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}

		return this->LoadCardFromJson(id, JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}

	return false;
}

bool ACard::LoadCardFromJson(FString& id, TSharedPtr<FJsonObject> JsonObject)
{
	int32 totalCards = JsonObject->GetIntegerField(TEXT("total_cards"));
	bool hasMore = JsonObject->GetBoolField(TEXT("has_more"));
	TArray<TSharedPtr<FJsonValue>> cards = JsonObject->GetArrayField(TEXT("data"));
	if (totalCards == 1) {
		TSharedPtr<FJsonValue> card = cards[0];
		TSharedPtr<FJsonObject> json = card->AsObject();
		id = json->GetStringField(TEXT("id"));
		// TODO: Parse card json into props

		return true;
	}

	return false;
}

FString ACard::LoadJsonFile(const FString& id)
{
	// Games/Content/****.json
	FString cachedFile = this->CachedFilePath(id);
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *cachedFile);

	return JsonStr;
}

bool ACard::NotCached(const FString& id)
{
	int32 contains = this->CardCache.Find(id);
	return contains > -1;
}

FString ACard::CachedFilePath(const FString& id)
{
	return FPaths::GameDevelopersDir() + "/card_cache/" + id + ".json";
}

bool ACard::CachedFileExists(const FString& id)
{
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*this->CachedFilePath(id));
}

bool ACard::FetchCard(const FString& id)
{
	FHttpModule* Http = &FHttpModule::Get();

	if (!Http)
	{
		return false;
	}

	if (!Http->IsHttpEnabled())
	{
		return false;
	}

	FString URL = "https://api.scryfall.com/cards/" + id;
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb("GET");
	Request->SetURL(URL);
	Request->SetHeader("User-Agent", "UnrealMTG/1.0");
	// Request->SetHeader("Content-Type", "text/html");

	Request->OnProcessRequestComplete().BindUObject(this, &ACard::HTTPOnResponseReceived);
	if (!Request->ProcessRequest())
	{
		return false;
	}

	return true;
}

void ACard::HTTPOnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString ResponseStr = "ACard::HTTPOnResponseReceived>>> Connection Error";
	if (bWasSuccessful)
	{
		ResponseStr = Response->GetContentAsString();
	}

	FString id;
	this->GenerateFromJsonString(id, ResponseStr);
	if (id != "") {
		this->SaveCardToCache(id, ResponseStr);
	}
}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
