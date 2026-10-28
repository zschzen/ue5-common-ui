// Copyright (c) 2026 Leandro

#include "Widgets/Components/FrontendCommonButtonBase.h"

#include "CommonTextBlock.h"

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
    if ( CommonTextBlock_Label && GetCurrentTextStyleClass() )
        {
            CommonTextBlock_Label->SetStyle( GetCurrentTextStyleClass() );
        }
}
