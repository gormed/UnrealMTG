// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractPlaygroundActorComponent.h"
#include "Components/ActorComponent.h"
#include "MTGHandActorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCastCardsSignature, UAbstractPlaygroundActorComponent*, Target, TSet<ACard*>, CardsCast);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDrawCardsSignature, UAbstractPlaygroundActorComponent*, Source, TSet<ACard*>, CardsDrawn);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMTG_API UMTGHandActorComponent : public UAbstractPlaygroundActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMTGHandActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Show Hand To Player(s)"))
	void ShowHand(TArray<AMTGPlayerCharacter*> ToCharacters);

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Hide Hand From All Players"))
	void HideHand();

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Cast Cards"))
	bool CastCards(
		UAbstractPlaygroundActorComponent* Target,
		const TSet<ACard*> CastCards,
		const FMoveAction Action
	);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Action")
	FCastCardsSignature OnCastCards;

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Draw Cards"))
	bool DrawCards(
		UAbstractPlaygroundActorComponent* Source,
		const TSet<ACard*> CardsToDraw,
		const FMoveAction Action
	);

	UPROPERTY(BlueprintAssignable, Category = "MTG|Action")
	FDrawCardsSignature OnDrawCards;
};
