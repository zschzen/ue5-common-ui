// Copyright (c) 2026 Leandro

#include "FrontendGameplayTags.h"

namespace FrontendGameplayTags
{
    // Definition macro
#define DEF_TAG( VarName, TagStr ) UE_DEFINE_GAMEPLAY_TAG( VarName, TagStr )

    // Execute
    FRONTEND_WIDGET_TAGS( DEF_TAG )

    // Clean up
#undef DEF_TAG
}
