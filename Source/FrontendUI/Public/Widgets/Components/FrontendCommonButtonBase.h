// Copyright (c) 2026 Leandro

#pragma once

#include "CoreMinimal.h"

#include "CommonButtonBase.h"

#include "FrontendCommonButtonBase.generated.h"

class UCommonTextBlock;

/**
 * 
 */
UCLASS( Abstract, BlueprintType, meta = ( DisableNaiveTick ) )
class FRONTENDUI_API UFrontendCommonButtonBase : public UCommonButtonBase
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable )
    void SetButtonLabel( FText InText );

private:
    //~ Begin UUserWidget Interface
    virtual void NativePreConstruct() override;
    //~ End UUserWidget Interface

    //**** Bound Widgets ****//
    UPROPERTY( meta = ( BindWidgetOptional ) )
    UCommonTextBlock * CommonTextBlock_Label {};
    //**** Bound Widgets ****//

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = ( AllowPrivateAccess = "true" ) )
    FText ButtonDisplayText {};

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = ( AllowPrivateAccess = "true" ) )
    bool bUserUpperCaseForButtonText = false;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = ( AllowPrivateAccess = "true" ) )
    FText ButtonDescriptionText {};
};
