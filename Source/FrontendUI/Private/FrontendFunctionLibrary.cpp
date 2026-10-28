// Copyright (c) 2026 Leandro

#include "FrontendFunctionLibrary.h"

#include "CoreTypes.h"
#include "Engine/LocalPlayer.h"
#include "Settings/FrontendDeveloperSettings.h"
#include "Subsystems/FrontendUISubsystem.h"

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

void
UFrontendFunctionLibrary::PushWidgetByTag_ForPlayer( const ULocalPlayer * LocalPlayer,
                                                     UPARAM( meta = ( Categories = "Frontend.Widget" ) )
                                                         FGameplayTag InWidgetTag,
                                                     UPARAM( meta = ( Categories = "Frontend.WidgetStack" ) )
                                                         FGameplayTag InWidgetStackTag )
{
    if( UFrontendUISubsystem * FrontendUISubsystem = UFrontendUISubsystem::Get( LocalPlayer ) )
        {
            FrontendUISubsystem->PushWidgetByTag( InWidgetTag, InWidgetStackTag );
        }
}
