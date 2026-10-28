// Copyright (c) 2026 Leandro

#include "Widgets/Widget_PressAnyKey.h"

UWidget_PressAnyKey::UWidget_PressAnyKey( const FObjectInitializer & ObjectInitializer )
    : Super( ObjectInitializer )
{
    // Focusability is read at construction only, so it cannot be set later
    SetIsFocusable( true );

    // Disables the NativeTick function entirely
    bHasScriptImplementedTick = false;
}

UWidget *
UWidget_PressAnyKey::NativeGetDesiredFocusTarget() const
{
    // Nothing inside this screen is focusable, so it takes focus itself. with no focus target
    // the push leaves focus elsewhere and no key event ever reaches this widget
    return const_cast< UWidget_PressAnyKey * >( this );
}
