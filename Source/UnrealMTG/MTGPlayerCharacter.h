// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealMTG.h"
#include "GameFramework/Character.h"
#include "MTGPlayerCharacter.generated.h"

UCLASS()
class UNREALMTG_API AMTGPlayerCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// Library Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Library")
	class UMTGLibraryActorComponent* Library;

	/// Stack Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Stack")
	class UMTGStackActorComponent* Stack;

	/// Hand Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Hand")
	class UMTGHandActorComponent* Hand;

	/// Graveyard Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Graveyard")
	class UMTGGraveyardActorComponent* Graveyard;

	/// Exile Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Exile")
	class UMTGExileActorComponent* Exile;

	/// Command Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Command")
	class UMTGCommadActorComponent* Command;

	/// Battlefield Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Battlefield")
	class UMTGBattlefieldActorComponent* Battlefield;
};
