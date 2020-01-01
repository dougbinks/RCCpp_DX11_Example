#include "IObject.h"
#include "RCCppMainLoop.h"
#include "SystemTable.h"
#include "ISimpleSerializer.h"

#include "imgui.h"

// add imgui source dependencies
// an alternative is to put imgui into a library and use RuntimeLinkLibrary
#include "RuntimeSourceDependency.h"
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_widgets", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_draw", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_demo", ".cpp" );

// D3D11 has a virtual interace, so we only need to include the header and
// have a system pointer.
#include <d3d11.h>



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
    float  f = 0.0f;
    int    counter = 0;

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


        // Rendering
        ImGui::Render();
        PerModuleInterface::g_pSystemTable->pd3dDeviceContext->OMSetRenderTargets(1, &g_pSys->pMainRenderTargetView, NULL);
        PerModuleInterface::g_pSystemTable->pd3dDeviceContext->ClearRenderTargetView( g_pSys->pMainRenderTargetView, (float*)&clear_color);

        g_pSys->ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_pSys->pSwapChain->Present(1, 0); // Present with vsync
        //g_pSys->pSwapChain->Present(0, 0); // Present without vsync


	}
};

REGISTERSINGLETON(RCCppMainLoop,true);