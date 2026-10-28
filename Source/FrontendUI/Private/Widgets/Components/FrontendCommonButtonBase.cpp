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
