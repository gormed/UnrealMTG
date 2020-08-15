// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Types/FMTGDeck.h"

#include "Playground.generated.h"

UCLASS()
class UNREALMTG_API APlayground : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayground();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Init Library"))
	bool Init(class AMTGPlayerCharacter* owningCharacter, FMTGDeck deck);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG")
	class AMTGPlayerCharacter* OwningCharacter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG")
	FMTGDeck Deck;
};
