// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../UnrealMTG.h"
#include "EStackSide.h"
#include "AbstractPlaygroundActorComponent.h"
#include "Components/ActorComponent.h"
#include "AbstractStackActorComponent.generated.h"

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
	TArray<class ACard*> ViewCards(class AMTGPlayerCharacter* character, int32 count, TEnumAsByte<EStackSide::Type> side);

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Draw Cards"))
	TArray<class ACard*> DrawCards(class AMTGPlayerCharacter* character, int32 count, TEnumAsByte<EStackSide::Type> side);

	UFUNCTION(BlueprintCallable, Category = "MTG|Action", meta = (DisplayName = "Put Cards Into Library"))
	bool PutCards(
		class UAbstractPlaygroundActorComponent* source,
		const TArray<class ACard*>& putCards,
		TEnumAsByte<EStackSide::Type> side
	);
};
