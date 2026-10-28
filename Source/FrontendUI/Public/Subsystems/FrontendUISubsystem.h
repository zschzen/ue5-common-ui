// Copyright (c) 2026 Leandro

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "FrontendUISubsystem.generated.h"

class UWidget_ActivatableBase;
class UWidget_PrimaryLayout;
class UFrontendCommonButtonBase;

UENUM( BlueprintType )
enum class EAsyncPushWidgetState : uint8
{
    OnCreatedBeforePush,
    AfterPush
};

/**
 * Notifies a caller of PushSoftWidgetToStackAsync as the pushed widget's lifecycle progresses.
 * Bind with CreateUObject or CreateWeakLambda: a destroyed target unbinds silently instead of
 * firing into freed memory.
 */
DECLARE_DELEGATE_TwoParams( FOnAsyncPushWidgetState, EAsyncPushWidgetState, UWidget_ActivatableBase * );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnButtonDescriptionTextUpdatedDelegate,
                                              // Params
                                              UFrontendCommonButtonBase *, BroadcastingButton, FText, DescriptionText );

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendUISubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    //~ Begin USubsystem interface
    virtual bool ShouldCreateSubsystem( UObject * Outer ) const override;
    //~ End USubsystem interface

    static UFrontendUISubsystem * Get( const UObject * WorldContextObject );

    UFUNCTION( BlueprintCallable )
    void RegisterCreatedPrimaryLayoutWidget( UWidget_PrimaryLayout * InCreatedWidget );

    /**
     * Resolves InWidgetTag through the frontend widget map and pushes that widget onto the stack
     * tagged InWidgetStackTag, taking care of owning player and focus. Screens ask for navigation
     * through here instead of loading and pushing widget classes themselves
     */
    UFUNCTION( BlueprintCallable )
    void PushWidgetByTag( UPARAM( meta = ( Categories = "Frontend.Widget" ) ) FGameplayTag      InWidgetTag,
                          UPARAM( meta = ( Categories = "Frontend.WidgetStack" ) ) FGameplayTag InWidgetStackTag );

    /**
     * Asynchronously loads InSoftWidgetClass and pushes it onto the widget stack tagged
     * InWidgetStackTag. Requires a primary layout to already be registered via
     * RegisterCreatedPrimaryLayoutWidget
     *
     * @param InWidgetStackTag       Tag identifying the target stack on the primary layout.
     * @param InSoftWidgetClass      Soft class to load; must not be null.
     * @param AsyncPushStateCallback Fired twice: OnCreatedBeforePush (widget constructed, not yet
     *                               pushed) then AfterPush (widget live on the stack).
     */
    void PushSoftWidgetToStackAsync(
        const FGameplayTag & InWidgetStackTag, TSoftClassPtr< UWidget_ActivatableBase > InSoftWidgetClass,
        TFunction< void( EAsyncPushWidgetState, UWidget_ActivatableBase * ) > AysncPushStateCallback );

    UPROPERTY( BlueprintAssignable )
    FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

private:
    /**
     * Completion handler for the streamable load requested by PushSoftWidgetToStackAsync.
     * The parameters are the payload bound at the CreateUObject call site, not arguments the
     * streamable delegate itself carries -- FStreamableDelegate is a zero-argument delegate
     */
    void OnSoftWidgetClassLoaded( FGameplayTag WidgetStackTag, TSoftClassPtr< UWidget_ActivatableBase > SoftWidgetClass,
                                  FOnAsyncPushWidgetState AsyncPushStateCallback );

    UPROPERTY( Transient )
    TObjectPtr< UWidget_PrimaryLayout > CreatedPrimaryLayout;
};
