// ©Vi-So Construction

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ViSoLogDevHelpers.generated.h"

/**
 * Helper functions that are specifically used in editor.
 */
UCLASS()
class VISOLOGGERDEV_API UViSoLogDevHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	* Navigates to a Asset in the editor.
	* This can be a DataAsset for example.
	*/
	UFUNCTION(BlueprintCallable, Category = "EditorHelpers")
	static void NavigateToAsset(UObject* ObjectToNavigate);

	/*
	* Navigates to the class in the editor.
	* This can be a blueprint of a NPC for example.
	*/
	UFUNCTION(BlueprintCallable, Category = "EditorHelpers")
	static void NavigateToClass(UClass* ClassToNavigateTo);

	/*
	* Check if the class is native
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EditorHelpers")
	static bool IsNativeClass(UClass* ClassToCheck);
};