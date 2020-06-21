// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractPlayActorComponent.h"
#include "Components/ActorComponent.h"
#include "MTGBattlefieldActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMTG_API UMTGBattlefieldActorComponent : public UAbstractPlayActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMTGBattlefieldActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
