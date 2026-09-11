// Copyright (c) 2026 Leandro

#pragma once

namespace Debug
{
    static void
    Print( const FString & Msg, const int32 InKey = -1, const FColor & InColor = FColor::MakeRandomColor() )
    {
        if( GEngine )
            {
                GEngine->AddOnScreenDebugMessage( InKey, 7.0F, InColor, Msg );
                UE_LOG( LogTemp, Warning, TEXT( "%s" ), *Msg );
            }
    }
}
