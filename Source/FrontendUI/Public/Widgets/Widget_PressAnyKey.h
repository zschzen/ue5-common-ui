// Copyright (c) 2026 Leandro

#pragma once

#include "CoreMinimal.h"

#include "Widgets/Widget_ActivatableBase.h"

#include "Widget_PressAnyKey.generated.h"

/**
 * View for the title screen. Binds to a view model created by its widget blueprint and leaves
 * input handling to blueprint overrides -- what the prompt says, where the player goes next, and
 * how input is interpreted all live outside this class.
 */
UCLASS( Abstract, meta = ( DisableNativeTick ) )
class FRONTENDUI_API UWidget_PressAnyKey : public UWidget_ActivatableBase
{
    GENERATED_BODY()

public:
    UWidget_PressAnyKey( const FObjectInitializer & ObjectInitializer );

protected:
    //~ Begin UCommonActivatableWidget interface
    virtual UWidget * NativeGetDesiredFocusTarget() const override;
    //~ End UCommonActivatableWidget interface

    /** Analog values below this magnitude are ignored, so stick drift does not trigger the screen */
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Input" )
    float AnalogActivationThreshold { 0.5f };
};
