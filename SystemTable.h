#pragma once

#include "RuntimeInclude.h"
RUNTIME_MODIFIABLE_INCLUDE; //recompile runtime files when this changes

struct RCCppMainLoopI;

struct SystemTable
{
    RCCppMainLoopI* pRCCppMainLoopI = 0;
};