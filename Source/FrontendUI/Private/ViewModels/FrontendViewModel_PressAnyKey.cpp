// Copyright (c) 2026 Leandro

#include "ViewModels/FrontendViewModel_PressAnyKey.h"

#include "CommonInputSubsystem.h"
#include "Engine/LocalPlayer.h"
#include "Settings/FrontendDeveloperSettings.h"

void
UFrontendViewModel_PressAnyKey::Initialize( ULocalPlayer * InLocalPlayer )
{
    LocalPlayer = InLocalPlayer;

    if( UCommonInputSubsystem * CommonInputSubsystem = UCommonInputSubsystem::Get( InLocalPlayer ) )
        {
            InputMethodChangedHandle = CommonInputSubsystem->OnInputMethodChangedNative.AddUObject(
                this, &UFrontendViewModel_PressAnyKey::HandleInputMethodChanged );
        }
}

void
UFrontendViewModel_PressAnyKey::Shutdown()
{
    if( UCommonInputSubsystem * CommonInputSubsystem = UCommonInputSubsystem::Get( LocalPlayer.Get() ) )
        {
            CommonInputSubsystem->OnInputMethodChangedNative.Remove( InputMethodChangedHandle );
        }

    InputMethodChangedHandle.Reset();
    LocalPlayer.Reset();
}

FText
UFrontendViewModel_PressAnyKey::GetPromptText() const
{
    const UFrontendDeveloperSettings * FrontendDeveloperSettings = GetDefault< UFrontendDeveloperSettings >();

    const UCommonInputSubsystem * CommonInputSubsystem           = UCommonInputSubsystem::Get( LocalPlayer.Get() );

    // Without the subsystem there is no device to report, so fall back to the keyboard prompt
    const bool bUsingGamepad
        = CommonInputSubsystem && CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad;

    return bUsingGamepad ? FrontendDeveloperSettings->PressAnyKeyPrompt_Gamepad
                         : FrontendDeveloperSettings->PressAnyKeyPrompt_KeyboardMouse;
}

void
UFrontendViewModel_PressAnyKey::RequestContinue() const
{
    OnContinueRequested.Broadcast();
}

void
UFrontendViewModel_PressAnyKey::HandleInputMethodChanged( ECommonInputType NewInputType )
{
    // GetPromptText reads the device itself, so the binding only needs to be told to re-run
    UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED( GetPromptText );
}
