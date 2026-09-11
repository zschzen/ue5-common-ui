// Copyright (c) 2026 Leandro

#include "Subsystems/FrontendUISubsystem.h"

#include "CoreTypes.h"
#include "FrontendDebugHelper.h"

UFrontendUISubsystem *
UFrontendUISubsystem::Get( const UObject * WorldContextObject )
{
    if( GEngine )
        {
            const UWorld * World = GEngine->GetWorldFromContextObject( WorldContextObject, EGetWorldErrorMode::Assert );

            return UGameInstance::GetSubsystem< UFrontendUISubsystem >( World->GetGameInstance() );
        }

    return nullptr;
}

void
UFrontendUISubsystem::RegisterCreatedPrimaryLayoutWidget( UWidget_PrimaryLayout * InCreatedWidget )
{
    check( InCreatedWidget );

    CreatePrimaryLayout = InCreatedWidget;

    Debug::Print( TEXT( "Primary layout widget stored" ) );
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
