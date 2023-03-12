#include "ViSoLogEditorSubSystem.h"

void UViSoLogEditorSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FEditorDelegates::PostPIEStarted.AddUObject(this, &UViSoLogEditorSubSystem::HandlePostPIEStarted);
	FEditorDelegates::PrePIEEnded.AddUObject(this, &UViSoLogEditorSubSystem::HandlePrePIEEnded);
}

void UViSoLogEditorSubSystem::Deinitialize()
{
	Super::Deinitialize();

	FEditorDelegates::PostPIEStarted.RemoveAll(this);
	FEditorDelegates::PrePIEEnded.RemoveAll(this);
}


void UViSoLogEditorSubSystem::HandlePostPIEStarted(bool bIsSimulating) const
{
	OnPIEPostStarted.Broadcast(bIsSimulating);
}

void UViSoLogEditorSubSystem::HandlePrePIEEnded(bool bIsSimulating) const
{
	OnPIEPreEnded.Broadcast(bIsSimulating);
}