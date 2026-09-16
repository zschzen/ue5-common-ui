// Copyright (c) 2026 Leandro

#include "FrontendFunctionLibrary.h"

#include "CoreTypes.h"
#include "Settings/FrontendDeveloperSettings.h"

TSoftClassPtr< UWidget_ActivatableBase >
UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag( UPARAM( meta = ( Categories = "Frontend.Widget" ) )
                                                               FGameplayTag InWidgetTag )
{
    const UFrontendDeveloperSettings * FrontendDeveloperSettings = GetDefault< UFrontendDeveloperSettings >();
    checkf( FrontendDeveloperSettings->FrontendWidgetMap.Contains( InWidgetTag ),
            TEXT( "Could not find the corresponding widget under the tag %s" ),
            *InWidgetTag.ToString() );

    return FrontendDeveloperSettings->FrontendWidgetMap.FindRef( InWidgetTag );
}
