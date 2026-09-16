// Copyright (c) 2026 Leandro

#pragma once

#include "NativeGameplayTags.h"

// Helper that holds the prefix and dot-version
#define WIDGETSTACK_TAG( X, Name ) X( Frontend_WidgetStack_##Name, "Frontend.WidgetStack." #Name )
#define WIDGET_TAG( X, Name )      X( Frontend_Widget_##Name, "Frontend.Widget." #Name )

// The tags list
#define FRONTEND_WIDGET_TAGS( X )                                                                                      \
    /** Stacks */                                                                                                      \
    WIDGETSTACK_TAG( X, Model )                                                                                        \
    WIDGETSTACK_TAG( X, GameMenu )                                                                                     \
    WIDGETSTACK_TAG( X, GameHUD )                                                                                      \
    WIDGETSTACK_TAG( X, Frontend )                                                                                     \
    /** Frontend Widgets */                                                                                            \
    WIDGET_TAG( X, PressAnyKeyScreen )                                                                                 \
    WIDGET_TAG( X, MainMenuScreen )

namespace FrontendGameplayTags
{
    // Declaration macro
#define DECL_TAG( VarName, TagStr ) FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN( VarName )

    FRONTEND_WIDGET_TAGS( DECL_TAG )

#undef DECL_TAG
}
