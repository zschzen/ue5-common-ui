// Copyright (c) 2026 Leandro

#include "Subsystems/FrontendUISubsystem.h"

#include "CoreTypes.h"
#include "Engine/AssetManager.h"
#include "FrontendDebugHelper.h"
#include "FrontendFunctionLibrary.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_PrimaryLayout.h"

UFrontendUISubsystem *
UFrontendUISubsystem::Get( const UObject * WorldContextObject )
{
    // ReturnNull, not Assert: Assert compiles out in Shipping, which would leave World null and crash the deref below
    const UWorld * World
        = GEngine ? GEngine->GetWorldFromContextObject( WorldContextObject, EGetWorldErrorMode::ReturnNull ) : nullptr;

    return World ? UGameInstance::GetSubsystem< UFrontendUISubsystem >( World->GetGameInstance() ) : nullptr;
}

void
UFrontendUISubsystem::RegisterCreatedPrimaryLayoutWidget( UWidget_PrimaryLayout * InCreatedWidget )
{
    check( InCreatedWidget );

    CreatedPrimaryLayout = InCreatedWidget;

    Debug::Print( TEXT( "Primary layout widget stored" ) );
}

void
UFrontendUISubsystem::PushWidgetByTag( FGameplayTag InWidgetTag, FGameplayTag InWidgetStackTag )
{
    // Captured by value: the callback runs after an async load, by which time a reference would
    // dangle
    APlayerController * OwningPlayerController = GetGameInstance()->GetFirstLocalPlayerController();

    PushSoftWidgetToStackAsync(
        InWidgetStackTag,
        UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag( InWidgetTag ),
        [OwningPlayerController]( EAsyncPushWidgetState InPushState, UWidget_ActivatableBase * PushedWidget )
            {
                switch( InPushState )
                    {
                    case EAsyncPushWidgetState::OnCreatedBeforePush:

                        // Before activation: CommonUI routes input and focus through the owning player
                        PushedWidget->SetOwningPlayer( OwningPlayerController );

                        break;

                    case EAsyncPushWidgetState::AfterPush:

                        if( UWidget * WidgetToFocus = PushedWidget->GetDesiredFocusTarget() )
                            {
                                WidgetToFocus->SetFocus();
                            }

                        break;
                    default: break;
                    }
            } );
}

void
UFrontendUISubsystem::PushSoftWidgetToStackAsync(
    const FGameplayTag & InWidgetStackTag, TSoftClassPtr< UWidget_ActivatableBase > InSoftWidgetClass,
    TFunction< void( EAsyncPushWidgetState, UWidget_ActivatableBase * ) > AysncPushStateCallback )
{
    check( !InSoftWidgetClass.IsNull() );

    UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
        InSoftWidgetClass.ToSoftObjectPath(),
        FStreamableDelegate::CreateLambda(
            [InSoftWidgetClass, this, InWidgetStackTag, AysncPushStateCallback]()
                {
                    UClass * LoadedWidgetClass = InSoftWidgetClass.Get();

                    check( LoadedWidgetClass && CreatedPrimaryLayout );

                    UCommonActivatableWidgetContainerBase * FoundWidgetStack
                        = CreatedPrimaryLayout->FindWidgetStackByTag( InWidgetStackTag );

                    UWidget_ActivatableBase * CreatedWidget = FoundWidgetStack->AddWidget< UWidget_ActivatableBase >(
                        LoadedWidgetClass,
                        [AysncPushStateCallback]( UWidget_ActivatableBase & CreatedWidgetInstance )
                            {
                                AysncPushStateCallback( EAsyncPushWidgetState::OnCreatedBeforePush,
                                                        &CreatedWidgetInstance );
                            } );

                    AysncPushStateCallback( EAsyncPushWidgetState::AfterPush, CreatedWidget );
                } ) );
}

void
UFrontendUISubsystem::OnSoftWidgetClassLoaded( FGameplayTag                             WidgetStackTag,
                                               TSoftClassPtr< UWidget_ActivatableBase > SoftWidgetClass,
                                               FOnAsyncPushWidgetState                  AsyncPushStateCallback )
{
    UClass * LoadedWidgetClass = SoftWidgetClass.Get();

    checkf( LoadedWidgetClass,
            TEXT( "Async load reported success but '%s' did not resolve" ),
            *SoftWidgetClass.ToString() );
    checkf( CreatedPrimaryLayout,
            TEXT( "No primary layout registered; call RegisterCreatedPrimaryLayoutWidget first" ) );

    UCommonActivatableWidgetContainerBase * FoundWidgetStack
        = CreatedPrimaryLayout->FindWidgetStackByTag( WidgetStackTag );

    // AddWidget's init functor is a TFunctionRef called synchronously, so capturing by reference here is safe
    UWidget_ActivatableBase * CreatedWidget = FoundWidgetStack->AddWidget< UWidget_ActivatableBase >(
        LoadedWidgetClass,
        [&AsyncPushStateCallback]( UWidget_ActivatableBase & WidgetInstance )
            { AsyncPushStateCallback.ExecuteIfBound( EAsyncPushWidgetState::OnCreatedBeforePush, &WidgetInstance ); } );

    // ExecuteIfBound, not Execute: caller may pass an unbound delegate to opt out of the callback
    AsyncPushStateCallback.ExecuteIfBound( EAsyncPushWidgetState::AfterPush, CreatedWidget );
}

bool
UFrontendUISubsystem::ShouldCreateSubsystem( UObject * Outer ) const
{
    // Dedicated servers have no UI, so skip them entirely
    if( false == ( CastChecked< UGameInstance >( Outer )->IsDedicatedServerInstance() ) )
        {
            // collect all subclasses of this subsystem class
            TArray< UClass * > FoundClasses {};
            GetDerivedClasses( GetClass(), FoundClasses );

            // no derived class overrides it
            return FoundClasses.IsEmpty();
        }

    return false;
}
