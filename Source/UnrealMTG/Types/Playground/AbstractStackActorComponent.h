// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../UnrealMTG.h"
#include "../EStackSide.h"
#include "AbstractPlaygroundActorComponent.h"
#include "Components/ActorComponent.h"
#include "AbstractStackActorComponent.generated.h"

class ACard;
class AMTGPlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FViewCardsSignature, AMTGPlayerCharacter*, Character, int32, Count, TEnumAsByte<EStackSide::Type>, Side, TSet<ACard*>, Cards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPutCardsSignature, UAbstractPlaygroundActorComponent*, Source, const TSet<ACard*>&, PutCards, TEnumAsByte<EStackSide::Type>, Side);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FRemoveCardsSignature, AMTGPlayerCharacter*, Character, int32, Count, TEnumAsByte<EStackSide::Type>, Side, TSet<ACard*>, RemovedCards);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMTG_API UAbstractStackActorComponent : public UAbstractPlaygroundActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbstractStackActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "View Cards"))
	TSet<ACard*> ViewCards(
		AMTGPlayerCharacter* Character,
		bool& bSuccessful,
		const int32 Count = 1,
		const TEnumAsByte<EStackSide::Type> Side = EStackSide::Top
	);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Action")
	FViewCardsSignature OnCardsViewed;

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Put Cards"))
		void PutCards(
			UAbstractPlaygroundActorComponent* Source,
			const TSet<ACard*>& PutCards,
			bool& bSuccessful,
			const TEnumAsByte<EStackSide::Type> Side = EStackSide::Top
		);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Action")
	FPutCardsSignature OnCardsPut;

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Draw Cards"))
	TSet<ACard*> RemoveCards(
		AMTGPlayerCharacter* Character,
		bool& bSuccessful,
		const int32 Count = 1,
		const TEnumAsByte<EStackSide::Type> Side = EStackSide::Top
	);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Action")
	FRemoveCardsSignature OnCardsRemoved;
};
