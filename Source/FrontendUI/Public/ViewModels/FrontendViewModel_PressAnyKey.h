// Copyright (c) 2026 Leandro

#pragma once

#include "CoreMinimal.h"

#include "CommonInputTypeEnum.h"
#include "MVVMViewModelBase.h"

#include "FrontendViewModel_PressAnyKey.generated.h"

class ULocalPlayer;

/**
 * The View asks the title-screen flow to continue. Carries no destination -- navigation is the
 * View's decision, the ViewModel only states the intent
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnContinueRequested );

/**
 * Screen state for the press-any-key title screen: the prompt the player reads, and the one
 * command that screen can issue. Holds no widget references -- the view binds to it, never the
 * other way around
 */
UCLASS()
class FRONTENDUI_API UFrontendViewModel_PressAnyKey : public UMVVMViewModelBase
{
    GENERATED_BODY()

public:
    /** Subscribes to input device changes so the prompt can follow the device in use */
    UFUNCTION( BlueprintCallable )
    void Initialize( ULocalPlayer * InLocalPlayer );

    /** Drops the subscription. Safe to call when Initialize never ran or its local player died */
    UFUNCTION( BlueprintCallable )
    void Shutdown();

    /**
     * Derived from the developer settings and the device currently in use, so there is no stored
     * value to set -- the field is re-broadcast when the device changes instead
     */
    UFUNCTION( BlueprintPure, FieldNotify )
    FText GetPromptText() const;

    /**
     * The player asked to leave the title screen. Broadcasts OnContinueRequested and nothing else
     * -- where to go next is the View's decision
     */
    UFUNCTION( BlueprintCallable )
    void RequestContinue() const;

    /** Bind in the owning widget to perform the actual navigation */
    UPROPERTY( BlueprintAssignable )
    FOnContinueRequested OnContinueRequested;

private:
    void HandleInputMethodChanged( ECommonInputType NewInputType );

    TWeakObjectPtr< ULocalPlayer > LocalPlayer {};

    FDelegateHandle InputMethodChangedHandle {};
};
