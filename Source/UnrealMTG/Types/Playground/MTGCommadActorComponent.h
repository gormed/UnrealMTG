// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractPlayActorComponent.h"
#include "Components/ActorComponent.h"
#include "MTGCommadActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMTG_API UMTGCommadActorComponent : public UAbstractPlayActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMTGCommadActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
