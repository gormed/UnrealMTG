// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MTGBlueprintFunctionLibrary.generated.h"
/**
 * 
 */
UCLASS()
class UNREALMTG_API UMTGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//////////////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "MTG|Card Search", meta = (DisplayName = "Create Search"))
	static class UMTGSearchObject* CreateSearch(const FString& SearchName, UObject* Outer, bool& bSuccessful);
};
