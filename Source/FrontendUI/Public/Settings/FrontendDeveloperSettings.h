// Copyright (c) 2026 Leandro

#pragma once

#include "CoreMinimal.h"

#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"

#include "FrontendDeveloperSettings.generated.h"

class UWidget_ActivatableBase;
/**
 * 
 */
UCLASS( Config = Game, DefaultConfig, meta = ( DisplayName = "Frontend UI Setting" ) )
class FRONTENDUI_API UFrontendDeveloperSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY( Config, EditAnywhere, Category = "Widget Reference",
               meta = ( ForceInlineRow, Categories = "Frontend.Widget" ) )
    TMap< FGameplayTag, TSoftClassPtr< UWidget_ActivatableBase > > FrontendWidgetMap {};

    UPROPERTY( Config, EditAnywhere, Category = "Press Any Key" )
    FText PressAnyKeyPrompt_KeyboardMouse {};

    UPROPERTY( Config, EditAnywhere, Category = "Press Any Key" )
    FText PressAnyKeyPrompt_Gamepad {};
    
    UPROPERTY( Config, EditAnywhere, Category = "Press Any Key" )
    FText PressAnyKeyPrompt_Touch {};
};
