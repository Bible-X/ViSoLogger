// ©bcc.media foundation

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "ViSoLogEditorSubSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPIEPostStarted, bool, bIsSimulating);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPIEPreEnded, bool, bIsSimulating);

/**
 * BibleX Editor subsystem to assist with editor widgets
 */
UCLASS()
class VISOLOGEDITOR_API UViSoLogEditorSubSystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	/** Sent when a PIE session has fully started and after BeginPlay() has been called */
	UPROPERTY(BlueprintAssignable, Category = "Editor Scripting | Event Listener")
	FOnPIEPostStarted OnPIEPostStarted;

	/** Sent when a PIE session is ending, before anything else happens */
	UPROPERTY(BlueprintAssignable, Category = "Editor Scripting | Event Listener")
	FOnPIEPostStarted OnPIEPreEnded;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void HandlePostPIEStarted(bool bIsSimulating) const;
	void HandlePrePIEEnded(bool bIsSimulating) const;
};
