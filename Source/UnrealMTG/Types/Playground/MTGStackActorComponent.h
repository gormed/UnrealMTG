// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../UnrealMTG.h"
#include "AbstractPlaygroundActorComponent.h"
#include "Components/ActorComponent.h"
#include "MTGStackActorComponent.generated.h"

class ACard;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMTG_API UMTGStackActorComponent : public UAbstractPlaygroundActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMTGStackActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Cast Cards"))
	bool CastCards(
		UAbstractPlaygroundActorComponent* source,
		TSet<ACard*> castCards,
		TEnumAsByte<ECardFace::Type> face
	);
};
