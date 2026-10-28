// Copyright (c) 2026 Leandro

#include "Widgets/Components/FrontendCommonButtonBase.h"

#include "CommonTextBlock.h"
#include "Subsystems/FrontendUISubsystem.h"

void
UFrontendCommonButtonBase::SetButtonLabel( FText InText )
{
    if( CommonTextBlock_Label && !InText.IsEmpty() )
        {
            CommonTextBlock_Label->SetText( ( bUserUpperCaseForButtonText ? InText.ToUpper() : InText ) );
        }
}

void
UFrontendCommonButtonBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetButtonLabel( ButtonDisplayText );
}

void
UFrontendCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
    Super::NativeOnCurrentTextStyleChanged();

    // Apply a valid style
    if( CommonTextBlock_Label && GetCurrentTextStyleClass() )
        {
            CommonTextBlock_Label->SetStyle( GetCurrentTextStyleClass() );
        }
}

void
UFrontendCommonButtonBase::NativeOnHovered()
{
    Super::NativeOnHovered();

    // Set description text
    if( false == ButtonDescriptionText.IsEmpty() )
        {
            UFrontendUISubsystem::Get( this )->OnButtonDescriptionTextUpdated.Broadcast( this, ButtonDescriptionText );
        }
}

void
UFrontendCommonButtonBase::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();

    // Clear
    UFrontendUISubsystem::Get( this )->OnButtonDescriptionTextUpdated.Broadcast( this, FText::GetEmpty() );
}
