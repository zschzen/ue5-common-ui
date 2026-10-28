// Copyright (c) 2026 Leandro

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "FrontendFunctionLibrary.generated.h"

class ULocalPlayer;
class UWidget_ActivatableBase;

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintPure, Category = "Frontend Function Library" )
    static TSoftClassPtr< UWidget_ActivatableBase >
    GetFrontendSoftWidgetClassByTag( UPARAM( meta = ( Categories = "Frontend.Widget" ) ) FGameplayTag InWidgetTag );

    /**
     * Blueprint-facing navigation entry point: resolves InWidgetTag through the frontend widget map
     * and pushes that widget onto the stack tagged InWidgetStackTag for LocalPlayer. Screens ask
     * for navigation through here instead of holding a reference to the UI subsystem
     */
    UFUNCTION( BlueprintCallable, Category = "Frontend Function Library" )
    static void PushWidgetByTag_ForPlayer( const ULocalPlayer * LocalPlayer,
                                           UPARAM( meta = ( Categories = "Frontend.Widget" ) ) FGameplayTag InWidgetTag,
                                           UPARAM( meta = ( Categories = "Frontend.WidgetStack" ) ) FGameplayTag InWidgetStackTag );
};
