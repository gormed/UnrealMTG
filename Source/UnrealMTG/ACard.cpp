// Fill out your copyright notice in the Description page of Project Settings.

#include "ACard.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFilemanager.h"
#include "HighResScreenshot.h"
#include "ImageUtils.h"
#include "IImageWrapper.h"
#include "GameFramework/Character.h"

// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ObjectType = ECardObjectType::Type::Card;
}

void ACard::InitCard(const FString& CardId)
{
	Id = CardId;
	if (CardDataNotCached(this->Id)) {
		FetchCard(this->Id);
	}
	else
	{
		LoadCardFromCache(this->Id);
	}
}

bool ACard::LoadCardFromJson(TSharedPtr<FJsonObject> JsonObject, FString& OutId)
{
	OutId = JsonObject->GetStringField(TEXT("id"));

	// object
	const FString Scryfall_Object = JsonObject->GetStringField(TEXT("object"));
	if (Scryfall_Object == "card") {
		ObjectType = ECardObjectType::Card;
	}
	else if (Scryfall_Object == "related_card") {
		ObjectType = ECardObjectType::RelatedCard;
	}
	else if (Scryfall_Object == "card_face") {
		ObjectType = ECardObjectType::CardFace;
	}
	else if (Scryfall_Object == "card_part") {
		ObjectType = ECardObjectType::CardPart;
	}
	else {
		ObjectType = ECardObjectType::None;
	}

	// lang
	const FString Scryfall_Lang = JsonObject->GetStringField(TEXT("lang"));
	Language = Scryfall_Lang;

	// oracle_id
	const FString Scryfall_OracleId = JsonObject->GetStringField(TEXT("oracle_id"));

	// name
	const FString Scryfall_Name = JsonObject->GetStringField(TEXT("name"));
	Name = Scryfall_Name;

	// layout
	const FString Scryfall_Layout = JsonObject->GetStringField(TEXT("layout"));
	if (Scryfall_Layout == "split") {
		Layout = ECardLayoutType::Split;
	}
	else if (Scryfall_Layout == "transform") {
		Layout = ECardLayoutType::Transform;
	}
	else if (Scryfall_Layout == "token") {
		Layout = ECardLayoutType::Token;
	}
	else if (Scryfall_Layout == "normal") {
		Layout = ECardLayoutType::Normal;
	}

	// type_line
	const FString Scryfall_TypeLine = JsonObject->GetStringField(TEXT("type_line"));
	Type.TypeLine = Scryfall_TypeLine;
	// TODO: Parse TypeLine into single types
	// Type.Supertype = ECardSupertype::None;

	// mana_cost
	const FString Scryfall_ManaCost = JsonObject->GetStringField(TEXT("mana_cost"));
	ManaCost.ManaCostLine = Scryfall_ManaCost;
	// TODO: Parse ManaCostLine into single mana types
	// ManaCost.Black = 1

	// cmc
	const uint32 Scryfall_CMC = JsonObject->GetIntegerField(TEXT("cmc"));
	CMC = Scryfall_CMC;

	// colors
	const TArray<TSharedPtr<FJsonValue>> Scryfall_Colors = JsonObject->GetArrayField(TEXT("colors"));
	CardColors = ParseColorFragments(Scryfall_Colors);

	// color_identity
	const TArray<TSharedPtr<FJsonValue>> Scryfall_ColorIdentity = JsonObject->GetArrayField(TEXT("color_identity"));
	ColorIdentity = ParseColorFragments(Scryfall_ColorIdentity);

	// rarity
	const FString Scryfall_Rarity = JsonObject->GetStringField(TEXT("rarity"));

	// border_color
	const FString Scryfall_BorderColor = JsonObject->GetStringField(TEXT("border_color"));

	// keywords
	const TArray<TSharedPtr<FJsonValue>> Scryfall_Keywords = JsonObject->GetArrayField(TEXT("keywords"));

	// card_faces
	if (JsonObject->HasField("card_faces")) {
		const TArray<TSharedPtr<FJsonValue>> Scryfall_CardFaces = JsonObject->GetArrayField(TEXT("card_faces"));
	}

	// We fetch the large JPEG image or load it from cache
	const TSharedPtr<FJsonObject> Scryfall_ImageUris = JsonObject->GetObjectField(TEXT("image_uris"));
	const FString ImageUri = Scryfall_ImageUris->GetStringField("large");
	const TEnumAsByte<ECardSide::Type> CardSide = ECardSide::Front;
	if (CachedCardImageFileExists(OutId, CardSide)) {
		LoadCardImageFromCache(OutId, CardSide);
	}
	else {
		FetchCardTexture(ImageUri, CardSide);
	}

	// Broadcast Init Event
	OnCardIntialized.Broadcast();

	return true;
}

bool ACard::SaveCardToCache(const FString& id, const FString& jsonString)
{
	FString cachedFile = this->CachedFilePath(id);
	CardCache.Add(id);
	return FFileHelper::SaveStringToFile(jsonString, *cachedFile);
}

void ACard::LoadCardFromCache(const FString& id)
{
	if (!CachedCardDataFileExists(id)) {
		return;
	}
	FString json = this->LoadJsonFile(id);
	FString outId;
	if (GenerateFromJsonString(json, outId)) {
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

void ACard::LoadCardImageFromCache(const FString& id, TEnumAsByte<ECardSide::Type> CardSide)
{
	UTexture2D* Texture = LoadTextureFromFile(CachedImagePath(id, CardSide), EImageFormat::JPEG);
	if (Texture && CardSide == ECardSide::Front) {
		FrontSideTexture = Texture;
	}
	else if (Texture && CardSide == ECardSide::Back) {
		BackSideTexture = Texture;
	}
	else {
		return;
	}
	// Broadcast Fetched Event
	OnCardTextureFetched.Broadcast(CardSide, Texture);
}

UTexture2D* ACard::LoadTextureFromFile(const FString& FullFilePath, EImageFormat ImageFormat)
{
	UTexture2D* LoadedT2D = NULL;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

	// Load From File
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *FullFilePath)) return NULL;

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
	{
		TArray<uint8> UncompressedRGBA;
		if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
		{
			LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_R8G8B8A8);

			if (!LoadedT2D) return NULL;

			const TArray<uint8>& ByteArray = UncompressedRGBA;

			// Copy
			void* TextureData = LoadedT2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
			LoadedT2D->PlatformData->Mips[0].BulkData.Unlock();

			// Update
			LoadedT2D->UpdateResource();
		}
	}

	// Success
	// IsValid = true;
	return LoadedT2D;
}

bool ACard::GenerateFromJsonString(FString& json, FString& OutId)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(json);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}

		return LoadCardFromJson(JsonObject, OutId);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}

	return false;
}

TArray<TEnumAsByte<ECardColorFragment::Type>> ACard::ParseColorFragments(const TArray<TSharedPtr<FJsonValue>> colors)
{
	TArray<TEnumAsByte<ECardColorFragment::Type>> ColorFragments;
	for (TSharedPtr<FJsonValue> jsonColor : colors)
	{
		FString color;
		TEnumAsByte<ECardColorFragment::Type> colorFragment;
		if (jsonColor->TryGetString(color)) {
			if (color == "black" || color == "B") {
				colorFragment = ECardColorFragment::Black;
			}
			else if (color == "white" || color == "W") {
				colorFragment = ECardColorFragment::White;
			}
			else if (color == "red" || color == "R") {
				colorFragment = ECardColorFragment::Red;
			}
			else if (color == "blue" || color == "U") {
				colorFragment = ECardColorFragment::Blue;
			}
			else if (color == "green" || color == "G") {
				colorFragment = ECardColorFragment::Green;
			}
			else if (color == "colorless" || color == "C") {
				colorFragment = ECardColorFragment::Colorless;
			}
			ColorFragments.Add(colorFragment);
		}
	}
	return ColorFragments;
}

FString ACard::LoadJsonFile(const FString& id)
{
	// Games/Content/****.json
	FString cachedFile = this->CachedFilePath(id);
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *cachedFile);

	return JsonStr;
}

bool ACard::CardDataNotCached(const FString& id)
{
	int32 contains = this->CardCache.Find(id);
	return contains == -1;
}

FString ACard::CachedFilePath(const FString& id)
{
	return FPaths::GameDevelopersDir() + "card_cache/" + id + ".json";
}

FString ACard::CachedImagePath(const FString& id, TEnumAsByte<ECardSide::Type> CardSide)
{
	if (CardSide == ECardSide::Front) {
		return FPaths::GameDevelopersDir() + "card_cache/front_img/" + id + ".jpg";
	}
	else if (CardSide == ECardSide::Back) {
		return FPaths::GameDevelopersDir() + "card_cache/back_img/" + id + ".jpg";
	}
	else {
		return "";
	}
}

bool ACard::CachedCardDataFileExists(const FString& id)
{
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*this->CachedFilePath(id));
}

bool ACard::CachedCardImageFileExists(const FString& id, TEnumAsByte<ECardSide::Type> CardSide)
{
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*this->CachedImagePath(id, CardSide));
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

	Request->OnProcessRequestComplete().BindUObject(this, &ACard::HTTPOnResponse_FetchCard);
	if (!Request->ProcessRequest())
	{
		return false;
	}

	return true;
}

void ACard::HTTPOnResponse_FetchCard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString ResponseStr = "ACard::HTTPOnResponse_FetchCard>>> Connection Error";
	if (bWasSuccessful)
	{
		ResponseStr = Response->GetContentAsString();
	}

	FString OutId;
	if (GenerateFromJsonString(ResponseStr, OutId) && OutId != "") {
		SaveCardToCache(OutId, ResponseStr);
		if (GEngine) {
			const FString url = Request->GetURL();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Card fetched from %s"), *url));
		}
	}
	else {

	}
}

void ACard::SetTapped(const bool NewTapped)
{
	if (bTapped != NewTapped) {
		bTapped = NewTapped;
		OnCardTappedChanged.Broadcast(this, NewTapped);
	}
}

bool ACard::FetchCardTexture(const FString& URL, const TEnumAsByte<ECardSide::Type> CardSide)
{
	if (FetchCardImageUri != "") {
		return false;
	}

	FetchCardImageUri = URL;
	FetchCardSide = CardSide;

	FHttpModule* Http = &FHttpModule::Get();

	if (!Http)
	{
		return false;
	}

	if (!Http->IsHttpEnabled())
	{
		return false;
	}

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb("GET");
	Request->SetURL(FetchCardImageUri);
	Request->SetHeader("User-Agent", "UnrealMTG/1.0");

	Request->OnProcessRequestComplete().BindUObject(this, &ACard::HTTPOnResponse_FetchCardImage);
	if (!Request->ProcessRequest())
	{
		return false;
	}

	return true;
}

void ACard::HTTPOnResponse_FetchCardImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TArray<uint8> imageDataArray = Response->GetContent();

		// Save Card Image to Cache
		bool bSaved = FFileHelper::SaveArrayToFile(imageDataArray, *CachedImagePath(this->Id, FetchCardSide));

		if (!bSaved) {

		}

		// Convert Image into Texture
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(imageDataArray.GetData(), imageDataArray.Num()))
		{
			TArray<uint8> UncompressedBGRA;
			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
			{
				int32 Width = ImageWrapper->GetWidth();
				int32 Height = ImageWrapper->GetHeight();
				UTexture2D* CardTexture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);

				if (!CardTexture) return;

				void* TextureData = CardTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
				CardTexture->PlatformData->Mips[0].BulkData.Unlock();

				// Update the rendering resource from data.
				CardTexture->UpdateResource();

				if (FetchCardSide == ECardSide::Front) {
					FrontSideTexture = CardTexture;
				}
				else if (FetchCardSide == ECardSide::Back) {
					BackSideTexture = CardTexture;
				}
				else {

				}
				// Reset URI to indicate we are done
				FetchCardImageUri = "";
				// Broadcast Fetched Event
				OnCardTextureFetched.Broadcast(FetchCardSide, CardTexture);
			}
		}
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
