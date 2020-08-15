// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../UnrealMTG.h"
#include "../FMoveAction.h"
#include "Components/ActorComponent.h"
#include "AbstractPlaygroundActorComponent.generated.h"

class ACard;
class AMTGPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMTG_API UAbstractPlaygroundActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbstractPlaygroundActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	template<class T>
	bool CheckPlaygroundComponent(
		T*& outType
	);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MTG")
	AMTGPlayerCharacter* OwningCharacter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MTG")
	TSet<ACard*> Cards;
};
