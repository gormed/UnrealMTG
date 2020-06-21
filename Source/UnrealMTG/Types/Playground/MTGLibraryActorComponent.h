// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractStackActorComponent.h"
#include "Components/ActorComponent.h"
#include "MTGLibraryActorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMTG_API UMTGLibraryActorComponent : public UAbstractStackActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMTGLibraryActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
