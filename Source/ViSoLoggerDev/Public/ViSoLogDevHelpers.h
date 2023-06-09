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
	UFUNCTION(BlueprintCallable, Category = "EditorHelpers")
	static void NavigateToAsset(TSoftObjectPtr<UObject> ObjectToNavigate);
	
	UFUNCTION(BlueprintCallable, Category = "EditorHelpers")
	static void NavigateToClass(TSoftClassPtr<UClass> ClassToNavigateTo);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EditorHelpers")
	static bool IsNativeClass(UClass* ClassToCheck);
};