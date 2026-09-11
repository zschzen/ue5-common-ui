// Copyright (c) 2026 Leandro

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "FrontendUISubsystem.generated.h"

class UWidget_PrimaryLayout;

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendUISubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    //~ Begin USubsystem interface
    virtual bool ShouldCreateSubsystem( UObject * Outer ) const override;
    //~ End USubsystem interface

    static UFrontendUISubsystem * Get( const UObject * WorldContextObject );

    UFUNCTION( BlueprintCallable )
    void RegisterCreatedPrimaryLayoutWidget( UWidget_PrimaryLayout * InCreatedWidget );

private:
    UPROPERTY( Transient )
    UWidget_PrimaryLayout * CreatePrimaryLayout;
};
