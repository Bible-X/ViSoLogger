// ©Vi-So Construction

#include "ViSoLogDevHelpers.h"

#if WITH_EDITOR
#include "SourceCodeNavigation.h"
#include "Kismet2/KismetEditorUtilities.h"
#include <Subsystems/AssetEditorSubsystem.h>
#endif

void UViSoLogDevHelpers::NavigateToAsset(UObject* ObjectToNavigate)
{
#if WITH_EDITOR
	if (ObjectToNavigate && GEditor)
	{
		if (UAssetEditorSubsystem* AESS = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
		{
			AESS->OpenEditorForAsset(ObjectToNavigate);
		}
	}
#endif
}

void UViSoLogDevHelpers::NavigateToClass(UClass* ClassToNavigateTo)
{
#if WITH_EDITOR
	if (ClassToNavigateTo)
	{
		if (ClassToNavigateTo->IsNative())
		{
			if (FSourceCodeNavigation::CanNavigateToClass(ClassToNavigateTo))
			{
				if (FSourceCodeNavigation::NavigateToClass(ClassToNavigateTo))
				{
					return;
				}
			}

			// Failing that, fall back to the older method which will still get the file open assuming it exists
			FString NativeParentClassHeaderPath;
			if (FSourceCodeNavigation::FindClassHeaderPath(ClassToNavigateTo, NativeParentClassHeaderPath) &&
				(IFileManager::Get().FileSize(*NativeParentClassHeaderPath) != INDEX_NONE))
			{
				FSourceCodeNavigation::OpenSourceFile(FPaths::ConvertRelativePathToFull(NativeParentClassHeaderPath));
			}
		}
		else
		{
			// If not a native class it will open up a blueprint.
			FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(ClassToNavigateTo);
		}
	}
#endif
}

bool UViSoLogDevHelpers::IsNativeClass(UClass* ClassToCheck)
{
	return ClassToCheck->IsNative();
}