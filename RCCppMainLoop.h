#pragma once

// abstract interface to our RCCppMainLoop class, using I at end to denote Interface
struct RCCppMainLoopI
{
    virtual void MainLoop() = 0;
    virtual bool CreateDeviceD3D(void* hWnd) = 0;
    virtual void CleanupDeviceD3D() = 0;
    virtual void CreateRenderTarget() = 0;
    virtual void CleanupRenderTarget() = 0;

};