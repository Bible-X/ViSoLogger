// ©Vi-So Construction

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FViSoLoggerDevModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
};
