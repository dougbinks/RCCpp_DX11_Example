#pragma once

#include "RuntimeInclude.h"
RUNTIME_MODIFIABLE_INCLUDE; //recompile runtime files when this changes

struct RCCppMainLoopI;
struct ImGuiContext;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;

struct SystemTable
{
    RCCppMainLoopI* pRCCppMainLoopI = 0;
    ImGuiContext*   pImContext      = 0;
    ID3D11Device*            pd3dDevice            = NULL;
    ID3D11DeviceContext*     pd3dDeviceContext     = NULL;
    IDXGISwapChain*          pSwapChain            = NULL;
    ID3D11RenderTargetView*  pMainRenderTargetView = NULL;
};