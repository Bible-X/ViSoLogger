// ©Vi-So Construction

#pragma once
#include "GameplayTagContainer.h"
#include "ViSoLoggerTypes.generated.h"

class AActor;

UENUM(BlueprintType)
enum class EVSL_Verbosity : uint8 { Error, Warning, Note, Debug };

USTRUCT()
struct FViSoLogData
{
	GENERATED_BODY()

	EVSL_Verbosity Verbosity = EVSL_Verbosity::Error;
	TSoftObjectPtr<UObject> Instigator = nullptr;
	FString Message = FString();
	FString WhatToDo = FString();
	FString Tags = FString();
	
	FViSoLogData(EVSL_Verbosity InVerbosity, const UObject* InInstigator, FString InMessage, FString InWhatToDo , FName InTags)
	{
		Verbosity = InVerbosity;
		Instigator = InInstigator;
		Message = InMessage;
		WhatToDo = InWhatToDo;
		Tags = InTags.ToString();
	}

	FViSoLogData(EVSL_Verbosity InVerbosity, const UObject* InInstigator, FString InMessage, FString InWhatToDo)
	{
		Verbosity = InVerbosity;
		Instigator = InInstigator;
		Message = InMessage;
		WhatToDo = InWhatToDo;
	}

	FViSoLogData(EVSL_Verbosity InVerbosity, const UObject* InInstigator, FString InMessage, FName InTags)
	{
		Verbosity = InVerbosity;
		Instigator = InInstigator;
		Message = InMessage;
		Tags = InTags.ToString();
	}
	
	FViSoLogData(EVSL_Verbosity InVerbosity, const UObject* InInstigator, FString InMessage)
	{
		Verbosity = InVerbosity;
		Instigator = InInstigator;
		Message = InMessage;
	}

	FViSoLogData() {}
};

USTRUCT(BlueprintType)
struct FViSoLogNavTarget
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UObject> NavigationAsset;
	
	UPROPERTY(BlueprintReadOnly)
	TSoftClassPtr<UObject> NavigationTargetClass;

	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<AActor> NavigationActor;
	
	UPROPERTY(BlueprintReadOnly)
	FVector InstigatorWorldLocation = {0,0,0};

	FViSoLogNavTarget(const UClass* InNavigationTargetClass)
	{
		NavigationTargetClass = InNavigationTargetClass;
	}

	FViSoLogNavTarget(const UObject* InNavigationAsset)
	{
		NavigationAsset = InNavigationAsset;
	}

	FViSoLogNavTarget(const AActor* InNavigationActor)
	{
		if (!InNavigationActor) {return;}
		NavigationActor = InNavigationActor;
		InstigatorWorldLocation = InNavigationActor->GetActorLocation();
	}
	
	FViSoLogNavTarget() {}
};

USTRUCT(BlueprintType)
struct FViSoStoredLogData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	EVSL_Verbosity Verbosity = EVSL_Verbosity::Error;

	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<UObject> Instigator;
	
	UPROPERTY(BlueprintReadOnly)
	FString Message;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> WhatToDo;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> LogTimes;
	
	UPROPERTY(BlueprintReadOnly)
	FViSoLogNavTarget NavigationData;

	/** Must be setup with comma as tag separator FE: ("SomeTag,SomeOtherTag,Awesomeness") */
	UPROPERTY(BlueprintReadOnly, meta = (Categories = "ViSoLog.Tags"))
	FString Tags;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsNative = false;
	
	FViSoStoredLogData(FViSoLogData& LogData, FViSoLogNavTarget& NavData, bool InIsNative)
	{
		Verbosity = LogData.Verbosity;
		Message = LogData.Message;
		WhatToDo.Add(LogData.WhatToDo);
		Tags = LogData.Tags;
		
		NavigationData = NavData;
		
		IsNative = InIsNative;
	}

	FViSoStoredLogData()
	{
		
	}
};

USTRUCT(BlueprintType)
struct FViSoLogSessionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FViSoStoredLogData> SessionLogs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SessionDateAndTime;
};