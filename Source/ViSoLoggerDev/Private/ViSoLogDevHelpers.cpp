// ©Vi-So Construction

#include "ViSoLogDevHelpers.h"
#include "SourceCodeNavigation.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Subsystems/AssetEditorSubsystem.h"

void UViSoLogDevHelpers::NavigateToAsset(TSoftObjectPtr<UObject> ObjectToNavigate)
{
	if (ObjectToNavigate.IsNull()) {return;}
	if (!GEditor) {return;}
	if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
	{
		if (const UObject* TargetObject = ObjectToNavigate.LoadSynchronous())
		{
			AssetEditorSubsystem->OpenEditorForAsset(TargetObject);
		}
	}
}

void UViSoLogDevHelpers::NavigateToClass(TSoftClassPtr<UClass> ClassToNavigateTo)
{
	if (ClassToNavigateTo.IsNull()) {return;}
	
	const UClass* TargetClass = ClassToNavigateTo.LoadSynchronous();
	if (!TargetClass) {return;}
	
	if (TargetClass->IsNative())
	{
		if (FSourceCodeNavigation::CanNavigateToClass(TargetClass))
		{
			if (FSourceCodeNavigation::NavigateToClass(TargetClass))
			{
				return;
			}
		}

		// Failing that, fall back to the older method which will still get the file open assuming it exists
		FString NativeParentClassHeaderPath;
		if (FSourceCodeNavigation::FindClassHeaderPath(TargetClass, NativeParentClassHeaderPath) &&
			(IFileManager::Get().FileSize(*NativeParentClassHeaderPath) != INDEX_NONE))
		{
			FSourceCodeNavigation::OpenSourceFile(FPaths::ConvertRelativePathToFull(NativeParentClassHeaderPath));
		}
	}
	else
	{
		// If not a native class it will open up a blueprint.
		FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(TargetClass);
	}
}

bool UViSoLogDevHelpers::IsNativeClass(UClass* ClassToCheck)
{
	return ClassToCheck->IsNative();
}