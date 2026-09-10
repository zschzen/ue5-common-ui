// Copyright (c) 2026 Leandro

#include "Controllers/FrontendPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void
AFrontendPlayerController::OnPossess( APawn * aPawn )
{
    Super::OnPossess( aPawn );

    // Set ViewTarget for Default tag Camera
    TArray< AActor * > FoundCameras {};
    UGameplayStatics::GetAllActorsOfClassWithTag( this, ACameraActor::StaticClass(), FName( "Default" ), FoundCameras );

    if( false == FoundCameras.IsEmpty() )
        {
            SetViewTarget( FoundCameras[0] );
        }
}
