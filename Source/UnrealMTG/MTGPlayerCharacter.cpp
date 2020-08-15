// Fill out your copyright notice in the Description page of Project Settings.


#include "MTGPlayerCharacter.h"

#include "Types/Playground/MTGLibraryActorComponent.h"
#include "Types/Playground/MTGStackActorComponent.h"
#include "Types/Playground/MTGHandActorComponent.h"
#include "Types/Playground/MTGGraveyardActorComponent.h"
#include "Types/Playground/MTGExileActorComponent.h"
#include "Types/Playground/MTGCommadActorComponent.h"
#include "Types/Playground/MTGBattlefieldActorComponent.h"

#include "UnrealMTG/Playground.h"

// Sets default values
AMTGPlayerCharacter::AMTGPlayerCharacter(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Library = PCIP.CreateDefaultSubobject<class UMTGLibraryActorComponent>(this, TEXT("Library"));
	Stack = PCIP.CreateDefaultSubobject<class UMTGStackActorComponent>(this, TEXT("Stack"));
	Hand = PCIP.CreateDefaultSubobject<class UMTGHandActorComponent>(this, TEXT("Hand"));
	Graveyard = PCIP.CreateDefaultSubobject<class UMTGGraveyardActorComponent>(this, TEXT("Graveyard"));
	Exile = PCIP.CreateDefaultSubobject<class UMTGExileActorComponent>(this, TEXT("Exile"));
	Command = PCIP.CreateDefaultSubobject<class UMTGCommadActorComponent>(this, TEXT("Command"));
	Battlefield = PCIP.CreateDefaultSubobject<class UMTGBattlefieldActorComponent>(this, TEXT("Battlefield"));
}

// Called when the game starts or when spawned
void AMTGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Library->OwningCharacter = this;
	Stack->OwningCharacter = this;
	Hand->OwningCharacter = this;
	Graveyard->OwningCharacter = this;
	Exile->OwningCharacter = this;
	Command->OwningCharacter = this;
	Battlefield->OwningCharacter = this;
}

// Called every frame
void AMTGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMTGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AMTGPlayerCharacter::Init(class APlayground* PlayerPlayground)
{
	Playground = PlayerPlayground;
	Playground->OwningCharacter = this;
	return true;
}

