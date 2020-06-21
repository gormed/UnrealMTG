#pragma once

UENUM(BlueprintType, Category = "Card Keyword")
namespace EActionKeyword
{
	enum Type
	{
		None UMETA(DisplayName = "None"),
		Meld UMETA(DisplayName = "Meld"),
		Bolster UMETA(DisplayName = "Bolster"),
		Clash UMETA(DisplayName = "Clash"),
		Fateseal UMETA(DisplayName = "Fateseal"),
		Investigate UMETA(DisplayName = "Investigate"),
		Manifest UMETA(DisplayName = "Manifest"),
		Monstrosity UMETA(DisplayName = "Monstrosity"),
		Populate UMETA(DisplayName = "Populate"),
		Proliferate UMETA(DisplayName = "Proliferate"),
		Scry UMETA(DisplayName = "Scry"),
		Support UMETA(DisplayName = "Support"),
		Detain UMETA(DisplayName = "Detain"),
		Explore UMETA(DisplayName = "Explore"),
		Fight UMETA(DisplayName = "Fight"),
		Amass UMETA(DisplayName = "Amass"),
		Adapt UMETA(DisplayName = "Adapt"),
		Assemble UMETA(DisplayName = "Assemble"),
		Abandon UMETA(DisplayName = "Abandon"),
		Activate UMETA(DisplayName = "Activate"),
		Attach UMETA(DisplayName = "Attach"),
		Exert UMETA(DisplayName = "Exert"),
		Cast UMETA(DisplayName = "Cast"),
		Counter UMETA(DisplayName = "Counter"),
		Create UMETA(DisplayName = "Create"),
		Destroy UMETA(DisplayName = "Destroy"),
		Discard UMETA(DisplayName = "Discard"),
		Double UMETA(DisplayName = "Double"),
		Exchange UMETA(DisplayName = "Exchange"),
		Exile UMETA(DisplayName = "Exile"),
		Play UMETA(DisplayName = "Play"),
		Regenerate UMETA(DisplayName = "Regenerate"),
		Reveal UMETA(DisplayName = "Reveal"),
		Sacrifice UMETA(DisplayName = "Sacrifice"),
		SetInMotion UMETA(DisplayName = "Set in motion"),
		Shuffle UMETA(DisplayName = "Shuffle"),
		Tap UMETA(DisplayName = "Tap"),
		Untap UMETA(DisplayName = "Untap"),
		Vote UMETA(DisplayName = "Vote"),
		Transform UMETA(DisplayName = "Transform"),
		Surveil UMETA(DisplayName = "Surveil"),
		Goad UMETA(DisplayName = "Goad"),
		Planeswalk UMETA(DisplayName = "Planeswalk"),
		Mill UMETA(DisplayName = "Mill")
	};
}
