// ©Vi-So Construction

#pragma once
#include "GameplayTagContainer.h"
#include "ViSoLoggerTypes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FViSoLogNavigationData
{
	GENERATED_BODY()

	TSoftObjectPtr<UObject> Instigator;

#if !UE_BUILD_SHIPPING
	TSoftObjectPtr<UObject> NavigationTarget;
	TSoftClassPtr<UObject> NavigationTargetClass;
#endif

	FViSoLogNavigationData(const UObject* InInstigator, const UObject* InNavigationTarget = nullptr)
	{
		if (!InInstigator) {return;}
		Instigator = InInstigator;

		#if !UE_BUILD_SHIPPING
			if (InNavigationTarget)
			{
				NavigationTarget = InNavigationTarget;
				NavigationTargetClass = InNavigationTarget->GetClass();
			}
			else
			{
				NavigationTarget = Instigator;
				NavigationTargetClass = Instigator->GetClass();
			}
		#endif
	}

	FViSoLogNavigationData()
	{
		
	}
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FViSoLogData
{
	GENERATED_BODY()
	
	FString Message;
	FString WhatToDo;
	
	FViSoLogData(FString InMessage, FString InWhatToDo)
	{
		Message = InMessage;
		WhatToDo = InWhatToDo;
	}
	
	FViSoLogData(FString InMessage)
	{
		Message = InMessage;
	}
	
	FViSoLogData()
	{
	
	}
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FViSoStoredLogData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Message;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> WhatToDo;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> LogTimes;
	
	UPROPERTY(BlueprintReadOnly)
	FViSoLogNavigationData NavigationData;
	
	UPROPERTY(BlueprintReadOnly, meta = (Categories = "ViSoLog.Tags"))
	FGameplayTagContainer Tags;

	UPROPERTY(BlueprintReadOnly)
	FVector InstigatorWorldLocation = {0,0,0};

	UPROPERTY(BlueprintReadOnly)
	bool IsNative = false;
	
	FViSoStoredLogData(FViSoLogData& LogData, FViSoLogNavigationData& NavData, bool InIsNative)
	{
		Message = LogData.Message;
		WhatToDo.Add(LogData.WhatToDo);
		NavigationData = NavData;
		IsNative = InIsNative;
	}

	FViSoStoredLogData()
	{
		
	}
};

/**
 * Struct that holds all log info of a session
 */
USTRUCT(BlueprintType)
struct FViSoLogSessionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FViSoStoredLogData> SessionLogs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SessionDateAndTime;
};