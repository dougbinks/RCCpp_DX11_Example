#include "RCCppMainLoop.h"

#include "imgui.h"

// D3D11 has a virtual interace, so we only need to include the header and
// have a system pointer
// However functions, such as D3D11CreateDeviceAndSwapChain require the
// library to be included
#include "RuntimeLinkLibrary.h"
RUNTIME_COMPILER_LINKLIBRARY( "d3d11.lib" ); // we don't need to IRuntimeObjectSystem::AddLibraryDir as system lib
#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800

#include "IObject.h"
#include "SystemTable.h"
#include "ISimpleSerializer.h"
#include "IRuntimeObjectSystem.h"


// add imgui source dependencies
// an alternative is to put imgui into a library and use RuntimeLinkLibrary
#include "RuntimeSourceDependency.h"
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_widgets", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_draw", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_demo", ".cpp" );


// RCC++ uses interface id's to distinguish between different classes
// here we have only one, so we don't need a header for this enum and put it in the sam
// source code file as the rest of the code
enum InterfaceIDEnumConsoleExample
{
	IID_IRCCPP_MAIN_LOOP = IID_ENDInterfaceID, // IID_ENDInterfaceID from IObject.h InterfaceIDEnum

	IID_ENDInterfaceIDEnumConsoleExample
};

struct RCCppMainLoop : RCCppMainLoopI, TInterface<IID_IRCCPP_MAIN_LOOP,IObject>
{
    // Our state - now members of RCCppMainLoop
    bool   show_demo_window    = true;
    bool   show_another_window = false;
    ImVec4 clear_color         = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    float  f                   = 0.0f;
    int    counter             = 0;

    // data for compiling window
    static constexpr double SHOW_AFTER_COMPILE_TIME = 3.0f;
    double compileStartTime    = -SHOW_AFTER_COMPILE_TIME;
    double compileEndTime      = -SHOW_AFTER_COMPILE_TIME;
    unsigned int compiledModules = 0;

	RCCppMainLoop()
	{
		g_pSys->pRCCppMainLoopI = this;
	}

	void Init( bool isFirstInit ) override
	{
        // If you want to do any initialization which is expensive and done after state
        // has been serialized you can do this here.

		if( isFirstInit )
        {
            // do any init needed to be done only once here, isFirstInit only set
            // when object is first constructed at program start.
        }
        // can do any initialization you might want to change here.
	}

    void Serialize( ISimpleSerializer *pSerializer ) override
    {
		SERIALIZE( show_demo_window );
        SERIALIZE( show_another_window );
        SERIALIZE( clear_color );
        SERIALIZE( f );
        SERIALIZE( counter );
        SERIALIZE( compileStartTime );
        SERIALIZE( compileEndTime );
    }

	void MainLoop() override
	{
		ImGui::SetCurrentContext( g_pSys->pImContext );

		ImGui::SetNextWindowPos(ImVec2(50,400), ImGuiCond_Appearing );
		ImGui::SetNextWindowSize(ImVec2(0,0), ImGuiCond_Always );
        ImGui::Begin("RCCppMainLoop Window" );
        ImGui::Text("You can change Window's code at runtime!");
        ImGui::End();

		
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Show a compiling info
        double time = ImGui::GetTime();
        bool bCompiling = g_pSys->pRuntimeObjectSystem->GetIsCompiling();
        double timeSinceLastCompile = time - compileEndTime;
        if( bCompiling  || timeSinceLastCompile < SHOW_AFTER_COMPILE_TIME )
        {
            if( bCompiling )
            {
                if( timeSinceLastCompile > SHOW_AFTER_COMPILE_TIME )
                {
                    compileStartTime = time;
                }
                compileEndTime = time; // ensure always updated
            }
            bool bCompileOk = g_pSys->pRuntimeObjectSystem->GetLastLoadModuleSuccess();

            ImVec4 windowBgCol = ImVec4(0.1f,0.4f,0.1f,1.0f);
            if( !bCompiling )
            {
                if( bCompileOk )
                {
                    windowBgCol = ImVec4(0.1f,0.7f,0.1f,1.0f);
                }
                else
                {
                    windowBgCol = ImVec4(0.7f,0.1f,0.1f,1.0f);
                }
            }
            ImGui::PushStyleColor(ImGuiCol_WindowBg,windowBgCol);

            ImVec2 sizeAppWindow = ImGui::GetIO().DisplaySize;
            ImGui::SetNextWindowPos(ImVec2( sizeAppWindow.x - 300, sizeAppWindow.y - 50), ImGuiCond_Always );
		    ImGui::SetNextWindowSize(ImVec2(280,0), ImGuiCond_Always );
            ImGui::Begin("Compiling", NULL, ImGuiWindowFlags_NoTitleBar );
            if( bCompiling )
            {
                ImGui::Text("Compiling... time %.2fs", (float)(time - compileStartTime) );
            }
            else
            {
                if( bCompileOk )
                {
                    ImGui::Text("Compiling... time %.2fs. SUCCEED", (float)(compileEndTime - compileStartTime) );
                }
                else
                {
                    ImGui::Text("Compiling... time %.2fs. FAILED", (float)(compileEndTime - compileStartTime) );
                }
            }
            ImGui::End();
            ImGui::PopStyleColor();

        }


        // Rendering
        ImGui::Render();
        g_pSys->pd3dDeviceContext->OMSetRenderTargets(1, &g_pSys->pMainRenderTargetView, NULL);
        g_pSys->pd3dDeviceContext->ClearRenderTargetView( g_pSys->pMainRenderTargetView, (float*)&clear_color);

        g_pSys->ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_pSys->pSwapChain->Present(1, 0); // Present with vsync
        //g_pSys->pSwapChain->Present(0, 0); // Present without vsync
	}

    bool CreateDeviceD3D(void* hWnd) override
    {
        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = (HWND)hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSys->pSwapChain, &g_pSys->pd3dDevice, &featureLevel, &g_pSys->pd3dDeviceContext) != S_OK)
            return false;

        CreateRenderTarget();
        return true;
    }

    void CleanupDeviceD3D() override
    {
        CleanupRenderTarget();
        if (g_pSys->pSwapChain) { g_pSys->pSwapChain->Release(); g_pSys->pSwapChain = NULL; }
        if (g_pSys->pd3dDeviceContext) { g_pSys->pd3dDeviceContext->Release(); g_pSys->pd3dDeviceContext = NULL; }
        if (g_pSys->pd3dDevice) { g_pSys->pd3dDevice->Release(); g_pSys->pd3dDevice = NULL; }
    }

    void CreateRenderTarget() override
    {
        ID3D11Texture2D* pBackBuffer;
        g_pSys->pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        g_pSys->pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pSys->pMainRenderTargetView);
        pBackBuffer->Release();
    }

    void CleanupRenderTarget() override
    {
        if (g_pSys->pMainRenderTargetView) { g_pSys->pMainRenderTargetView->Release(); g_pSys->pMainRenderTargetView = NULL; }
    }

};

REGISTERSINGLETON(RCCppMainLoop,true);