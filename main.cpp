// dear imgui - standalone example application for DirectX 11
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.

// imgui headers
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// directx headers
#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>

// RCC++ headers
#include "RuntimeObjectSystem.h"

// headers from our example
#include "StdioLogSystem.h"
#include "SystemTable.h"
#include "RCCppMainLoop.h"

// RCC++ Data
static StdioLogSystem           g_Logger;
static SystemTable              g_SystemTable;

// Forward declarations of helper functions
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Forward declarations of RCC++ helper functions
bool RCCppInit();
void RCCppCleanup();
void RCCppUpdate();

// Main code
int main(int, char**)
{
    // Create application window
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX11 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize RCC++
    RCCppInit();

    // Initialize Direct3D
    if (!g_SystemTable.pRCCppMainLoopI->CreateDeviceD3D(hwnd))
    {
        g_SystemTable.pRCCppMainLoopI->CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_SystemTable.pd3dDevice, g_SystemTable.pd3dDeviceContext);

    // set system table variables for ImGui and ImGui_Impl
    g_SystemTable.pImContext = ImGui::GetCurrentContext();
    g_SystemTable.ImGui_ImplDX11_RenderDrawData = ImGui_ImplDX11_RenderDrawData;



    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Update RCC++
        RCCppUpdate();

        // Call the function in our RCC++ class
        g_SystemTable.pRCCppMainLoopI->MainLoop();
    }

    // Cleanup
    RCCppCleanup();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    g_SystemTable.pRCCppMainLoopI->CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}


// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_SystemTable.pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_SystemTable.pRCCppMainLoopI->CleanupRenderTarget();
            g_SystemTable.pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            g_SystemTable.pRCCppMainLoopI->CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

bool RCCppInit()
{
    g_SystemTable.pRuntimeObjectSystem = new RuntimeObjectSystem;
    g_SystemTable.pLogger = &g_Logger;
	if( !g_SystemTable.pRuntimeObjectSystem->Initialise(&g_Logger, &g_SystemTable) )
    {
        return false;
    }

    g_SystemTable.pRuntimeObjectSystem->CleanObjectFiles();

    // ensure include directories are set - use location of this file as starting point
    FileSystemUtils::Path basePath = g_SystemTable.pRuntimeObjectSystem->FindFile( __FILE__ ).ParentPath();
    FileSystemUtils::Path imguiIncludeDir = basePath / "imgui";
    g_SystemTable.pRuntimeObjectSystem->AddIncludeDir( imguiIncludeDir.c_str() );

    return true;
}

void RCCppCleanup()
{
    delete g_SystemTable.pRuntimeObjectSystem;
}

void RCCppUpdate()
{
	//check status of any compile
	if( g_SystemTable.pRuntimeObjectSystem->GetIsCompiledComplete() )
	{
		// load module when compile complete
		g_SystemTable.pRuntimeObjectSystem->LoadCompiledModule();
	}

	if( !g_SystemTable.pRuntimeObjectSystem->GetIsCompiling() )
	{
		float deltaTime = 1.0f / ImGui::GetIO().Framerate;
		g_SystemTable.pRuntimeObjectSystem->GetFileChangeNotifier()->Update( deltaTime );
	}
}
