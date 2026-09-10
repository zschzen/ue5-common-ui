// Copyright (c) 2026 Leandro

#pragma once

#include "NativeGameplayTags.h"

// Helper that holds the prefix and dot-version
#define WIDGET_TAG( X, Name ) X( Frontend_WidgetStack_##Name, "Frontend.WidgetStack." #Name )

// The tags list
#define FRONTEND_WIDGET_TAGS( X )                                                                                      \
    WIDGET_TAG( X, Model )                                                                                             \
    WIDGET_TAG( X, GameMenu )                                                                                          \
    WIDGET_TAG( X, GameHUD )                                                                                           \
    WIDGET_TAG( X, Frontend )

namespace FrontendGameplayTags
{
    // Declaration macro
#define DECL_TAG( VarName, TagStr ) FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( VarName )

    FRONTEND_WIDGET_TAGS( DECL_TAG )

#undef DECL_TAG
}
