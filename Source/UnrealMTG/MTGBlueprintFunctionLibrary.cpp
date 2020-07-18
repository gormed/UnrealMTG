// Fill out your copyright notice in the Description page of Project Settings.

#include "MTGBlueprintFunctionLibrary.h"

#include "MTGSearchObject.h"

UMTGSearchObject* UMTGBlueprintFunctionLibrary::CreateSearch(const FString& SearchName, UObject* Outer, bool& bSuccessful)
{
	UMTGSearchObject* Search = NewObject<UMTGSearchObject>(Outer, FName(*SearchName));
	bSuccessful = true;
	return Search;
}
