Support development of RCC++ through [GitHub Sponsors](https://github.com/sponsors/dougbinks) or [Patreon](https://www.patreon.com/enkisoftware)

[<img src="https://img.shields.io/static/v1?logo=github&label=Github&message=Sponsor&color=#ea4aaa" width="200"/>](https://github.com/sponsors/dougbinks)    [<img src="https://c5.patreon.com/external/logo/become_a_patron_button@2x.png" alt="Become a Patron" width="150"/>](https://www.patreon.com/enkisoftware)

# RuntimeCompiledCPlusPlus Dear ImGui and DirectX11 Tutorial
You can also find this tutorial in the devlog post [Runtime Compiled C++ Dear ImGui and DirectX11 Tutorial](https://www.enkisoftware.com/devlogpost-20200202-1-Runtime-Compiled-C++-Dear-ImGui-and-DirectX11-Tutorial).

This tutorial takes a small DirectX11 project, the Dear ImGui Example, and adds Runtime Compiled C++ to it. This enables us to edit the code at runtime and see the results live, without recompiling and restarting the project. 

This is a Windows only project but both Dear ImGui and Runtime Compiled C++ are cross platform. Thanks to Jonathan Bleeker and [Milviz](https://milviz.com/flight/index.php) for funding this tutorial.

Runtime-Compiled C++ (RCC++) is a way to reliably make major changes to C++ code at runtime and see the results immediately. It's aimed at games development but could be useful in any industry where turnaround times are a bottleneck.

https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus

RCC++ is primarily designed to shorten iteration times in development - developers can build their project, run it, make changes during runtime and see the results in a few seconds.

![Short teaser of Runtime Compiled C++ Dear ImGui and DirectX11 Example](https://github.com/dougbinks/images/blob/master/RCCpp_DX11_Example_ShortTeaser.gif)

## Getting the tutorial code
The complete finished code for this tutorial, including Dear ImGui and RuntimeCompiledCPlusPlus can be found on [GitHub as RCCpp_DX11_Example](https://github.com/dougbinks/RCCpp_DX11_Example). Each chapter of the tutorial has a branch with the changes up to that point, so the implementation can be followed step by step.

A similar cross platform example using [Dear ImGui](https://github.com/ocornut/imgui) with [GLFW](https://www.glfw.org/) and OpenGL is available on [GitHub as RCCpp-DearImGui-GLFW-example](https://github.com/juliettef/RCCpp-DearImGui-GLFW-example).

[RCC++ Dear ImGui and DirectX Tutorial Video Part 1: Introduction and Getting the Code](https://www.youtube.com/watch?v=U_petg2D718&list=PLRp7HE6uWI1m6tu_-vNUY-N_gnXT17WHQ&index=1)

The easiest way to get hold of the example code if you have git is to run the following command using a shell you can run git:

```
git clone --recursive https://github.com/dougbinks/RCCpp_DX11_Example
```

You can download git for windows from https://git-scm.com/download/win, and use the right click menu in Windows File Explorer to "Git Bash here" and then run git commands.

This will create the directory RCCpp_DX11_Example and get the latest source code, using the ```--recursive``` option to download the Dear ImGui and RuntimeCompiledCPlusPlus code, which have been included in the tutorial repository as submodules. If you want to run further git commands from the command line you'll need to cd into the directory:

```
cd RCCpp_DX11_Example
```

Alternatively you can use a git GUI program to get the code, most of these will automatically download the git submodules.

If you download the code via the "Download ZIP" approach, you'll also need to download RuntimeCompiledCPlusPlus and Dear ImGui into the RuntimeCompiledCPlusPlus and  imgui folders. The correct versions can be found by clicking on the RuntimeCompiledCPlusPlus and imgui folders you see on the front page of the [RCCpp_DX11_Example GitHub page](https://github.com/dougbinks/RCCpp_DX11_Example) as below.

The project is split into [several branches](https://github.com/dougbinks/RCCpp_DX11_Example/branches/all) to allow you to navigate to important points in its development, notably:

1. Project_Setup - [branch](https://github.com/dougbinks/RCCpp_DX11_Example/tree/Project_Setup) - [.zip](https://github.com/dougbinks/RCCpp_DX11_Example/archive/Project_Setup.zip)
1. Working_RCC++ - [branch](https://github.com/dougbinks/RCCpp_DX11_Example/tree/Working_RCC++) - [.zip](https://github.com/dougbinks/RCCpp_DX11_Example/archive/Working_RCC++.zip)
1. RCC++_With_ImGui - [branch](https://github.com/dougbinks/RCCpp_DX11_Example/tree/RCC++_With_ImGui) - [.zip](https://github.com/dougbinks/RCCpp_DX11_Example/archive/RCC++_With_ImGui.zip)
1. RCC++_With_D3D - [branch](https://github.com/dougbinks/RCCpp_DX11_Example/tree/RCC++_With_D3D) - [.zip](https://github.com/dougbinks/RCCpp_DX11_Example/archive/RCC++_With_D3D.zip)
1. RCC++_With_D3D_Library - [branch](https://github.com/dougbinks/RCCpp_DX11_Example/tree/RCC++_With_D3D_Library) - [.zip](https://github.com/dougbinks/RCCpp_DX11_Example/archive/RCC++_With_D3D_Library.zip)
1. master (latest code). - [branch](https://github.com/dougbinks/RCCpp_DX11_Example/tree/master) - [.zip](https://github.com/dougbinks/RCCpp_DX11_Example/archive/master.zip)

With git the following command can be used to change branches (using the RCC++_With_ImGui branch as an example):
```
git checkout RCC++_With_ImGui
```

## Initial Project Setup with Visual Studio
In this section I'm going to give an overview of the steps needed to setup a Visual Studio solution and projects with the files needed for RCC++, using the Dear ImGui example app as a basis.

Both Dear ImGui and RCC++ are on GitHub, and both provide Visual Studio project files. However, the project files need to be updated to match the version of VS in use. A simple approach to the project setup would be to fork each repo, but for this tutorial we copy the project files into another folder so we can keep the source repos clean of any changes.

This is somewhat tedious so I recommend you skip to the next chapter - if you're following along with the code you can grab the starting project on branch Project_Setup in your git clone using:
```
git checkout Project_Setup
```

[RCC++ Dear ImGui and DirectX Tutorial Video Part 2: Project Setup](https://www.youtube.com/watch?v=mTMVJb5wzZY&list=PLRp7HE6uWI1m6tu_-vNUY-N_gnXT17WHQ&index=2)

For detailed steps see the [repo commit history on branch  Project_Setup](https://github.com/dougbinks/RCCpp_DX11_Example/commits/Project_Setup).

The principal steps are to create a new Visual Studio solution with the ```example_win32_directx11``` Dear ImGui example and the RCC++ libraries. RCC++ consists of two libraries:
- the RuntimeCompiler which handles compiling; and 
- RuntimeObjectSystem which handles automatically compiling the appropriate files (this will be detailed later) whenever a file is changed.

A useful tip is that Visual Studio projects consist of two files - the .vcxproj and .vcxproj.filters file. The other VS files aren't required to setup a project. In the following instructions, and in the example repository, we copy the project files we need rather than create them from scratch and add the required code, though for RCC++ the later approach is fairly simple.

The setup consists of the following steps:
1. Set up a new repo and add RCC++ and Dear ImGui as submodules. If git isn't being used this step would be to create an empty directory for the project and download RCC++ and Dear ImGui into separate sub-directories
1. Test the example code for both works. This requires the projects to be updated to an installed version of Visual Studio which we're prompted for on opening the solution for the first time. Discard the project changes once tested
1. Create an empty Visual Studio Win32 Console project, and delete the project as we'll be making our own
1. Copy the example code from ```imgui\examples\example_win32_directx11``` root folder; ```main.cpp```, ```example_win32_directx11.vcxproj``` and ```example_win32_directx11.vcxproj.filters``` need to be copied.
1. Rename ```example_win32_directx11.vcxproj.*``` in the root folder to ```RCCpp_DX11_Example.*```, the same names as the project we deleted above.
1. Change the following paths in the project files ```RCCpp_DX11_Example.vcxproj.*``` we just renamed using a text editor with search and replace:
    1. Replace ```..\..``` with ```imgui```
    1. Replace ```..``` with ```imgui\examples```
1. Copy the RCC++ project files (```*.vcxproj``` and ```*.vcxproj.filters```) from folders ```RuntimeCompiledCPlusPlus\Aurora\RuntimeCompiler``` and ```RuntimeCompiledCPlusPlus\Aurora\RuntimeObjectSystem``` to our root folder. Change the following paths using a text editor with search and replace
    1. In ```RuntimeCompiler.vcxproj``` and ```RuntimeCompiler.vcxproj.filters``` ( renamed from RuntimeCompiler_VS2010.* ):
        1. Replace ```<ClCompile Include="``` with ```<ClCompile Include="RuntimeCompiledCPlusPlus\Aurora\RuntimeCompiler\```
        1. Replace ```<ClInclude Include="``` with ```<ClInclude Include="RuntimeCompiledCPlusPlus\Aurora\RuntimeCompiler\```
    1. In ```RuntimeObjectSystem.vcxproj``` and ```RuntimeObjectSystem.vcxproj.filters```:
        1. Replace ```<ClCompile Include="``` with ```<ClCompile Include="RuntimeCompiledCPlusPlus\Aurora\RuntimeObjectSystem\```
         1. Replace ```<ClInclude Include="``` with ```<ClInclude Include="RuntimeCompiledCPlusPlus\Aurora\RuntimeObjectSystem\```
1. For the following project changes, when opening the project properties (right clicking on a project in the Solution Explorer and selecting properties) pages make sure to set the configuration to ```All Configurations``` and Platform to ```All Platforms```.
1. Add the projects to our solution and switch the platform toolset to our version of Visual Studio: version 142 for Visual Studio 2019
1. Add the include directories to the RCC++ and imgui by changing the C/C++ General 'Additional Include Directories' to read: ```imgui;imgui\examples;RuntimeCompiledCPlusPlus\Aurora\RuntimeObjectSystem;RuntimeCompiledCPlusPlus\Aurora\RuntimeCompiler;%(AdditionalIncludeDirectories)```.
1. Setup project dependencies - right click on the Solution in the Solution Explorer and select Project Dependencies. For the project ```RCCpp_DX11_Example``` the ```RuntimeCompiler``` and ```RuntimeObjectSystem``` should be selected as 'depends on'.
1. Right click on all the projects ```RCCpp_DX11_Example```, ```RuntimeCompiler.lib``` and ```RuntimeObjectSystem.lib```, in General tab change the output directory to: ```$(SolutionDir)build\$(PlatformTarget)\$(Configuration)\``` and the Intermediate Directory to: ```$(SolutionDir)build\intermediates\$(ProjectName)\$(PlatformTarget)\$(Configuration)\```.
1. Right click on the ```RCCpp_DX11_Example``` project and select Properties. Under the Linker General settings add the output directory as an Additional Library Directory by entering ```$(OutDir)``` before the other directories.
1. In the Linker Input properties for the ```RCCpp_DX11_Example```  project add ```RuntimeCompiler.lib``` and ```RuntimeObjectSystem.lib``` as link Additional Dependencies.

The code up to this point is available in the example from the branch Project_Setup at https://github.com/dougbinks/RCCpp_DX11_Example/tree/Project_Setup. This runs the Dear ImGui example code and has the RuntimeCompiler and RuntimeObjectSystem libraries linked, but has no RCC++ code setup as yet.

## Working RCC++
The next step after the project setup is to get RCC++ working with the minimal code required.

[RCC++ Dear ImGui and DirectX Tutorial Video Part 3: Working RCC++](https://www.youtube.com/watch?v=qUHwtOUBSPA&list=PLRp7HE6uWI1m6tu_-vNUY-N_gnXT17WHQ&index=3)

For detailed steps take a look at the  [repo commit history on branch  Working_RCC++](https://github.com/dougbinks/RCCpp_DX11_Example/commits/Working_RCC++). 

The basic code to initialise and cleanup RCC++ is:

**main.cpp**
```cpp
#include "RuntimeObjectSystem.h"

// headers from our example 
#include "StdioLogSystem.h"

// RCC++ Data
static IRuntimeObjectSystem*    g_pRuntimeObjectSystem;
static StdioLogSystem           g_Logger;

// Forward declarations of RCC++ helper functions
bool RCCppInit();
void RCCppCleanup();

// Main code
int main(int, char**)
{
    // Create application window
    //...

    // Initialize RCC++
    RCCppInit();
    
    // Initialize Direct3D
    //...
    
    // Cleanup
    RCCppCleanup();
    //...
}

bool RCCppInit()
{
    g_pRuntimeObjectSystem = new RuntimeObjectSystem;
    if( !g_pRuntimeObjectSystem->Initialise(&g_Logger, NULL) )
    {
        delete g_pRuntimeObjectSystem;
        g_pRuntimeObjectSystem = NULL;
        return false;
    }
    return true;
}

void RCCppCleanup()
{
    delete g_pRuntimeObjectSystem;
}
```

One of the parameters which can be passed to the Initialise function for the RuntimeObjectSystem is an ```ICompilerLogger``` pointer. When non-null, RCC++ will log important information to this including all compiler output. StdioLogSystem is a simple implementation which takes the output of RCC++ compiles and passes them to the Visual Studio IDE debug stream via ```OutputDebugStream``` as well as to ```std::cout```. The log is formatted so that if there is an error in the compilation, double clicking on it goes to that line and file.

The RCC++ RuntimeObjectSystem file change notifier must have its update function called regularly so it can detect changed files. Additionally the code needs to load any compiled modules when a compile is complete. 

This code could go in a runtime compiled file but that requires care to ensure that when that file is compiled, any code which comes after loading a module does not reference memory which could have been deleted. In order to do this we place the code in main.cpp:

**main.cpp**
```cpp
// Forward declarations of RCC++ helper functions
//...
void RCCppUpdate();

// Main code
int main(int, char**)
{
    //...
    while (msg.message != WM_QUIT)
    {
        //...

        // Update RCC++
        RCCppUpdate();
    
    //...
    }
    //...
}
void RCCppUpdate()
{
    //check status of any compile
    if( g_pRuntimeObjectSystem->GetIsCompiledComplete() )
    {
        // load module when compile complete
        g_pRuntimeObjectSystem->LoadCompiledModule();
    }

    if( !g_pRuntimeObjectSystem->GetIsCompiling() )
    {
        float deltaTime = 1.0f / ImGui::GetIO().Framerate;
        g_pRuntimeObjectSystem->GetFileChangeNotifier()->Update( deltaTime );
    }
}
```

Note that a time delta is passed to RCC++. This is used to delay compilation of any files until 0.1 seconds have passed so that RCC++ captures all files saved if multiple files are saved at once. 

For RCC++ to work, at least one file must have a class derived from RCC++ IObject and registered with RCC++ using a register macro. For this example the file which will be registered for runtime compilation is called RCCppMainLoop.cpp as it is going to handle the inner main loop of the program. 

Initial code for the RCC++ file **RCCppMainLoop.cpp**:
```cpp
#include "ObjectInterfacePerModule.h"
#include "IObject.h"


// RCC++ uses interface Id's to distinguish between different classes
// here we have only one, so we don't need a header for this enum and put it in the same
// source code file as the rest of the code
enum InterfaceIDEnumConsoleExample
{
    IID_IRCCPP_MAIN_LOOP = IID_ENDInterfaceID, // IID_ENDInterfaceID from IObject.h InterfaceIDEnum

    IID_ENDInterfaceIDEnumConsoleExample
};

struct RCCppMainLoop : TInterface<IID_IRCCPP_MAIN_LOOP,IObject>
{

};

REGISTERSINGLETON(RCCppMainLoop,true);
```

Note I often use ```struct``` instead of ```class``` when we don't need private members.

The important elements here are:

```InterfaceIDEnumConsoleExample``` - this enum is used by the IObject factory system to identify objects. For RCC++ projects with more than one file it's normally in a separate header (the name is an accidental holdover from the console example in RCC++).

```struct RCCppMainLoop : TInterface<IID_IRCCPP_MAIN_LOOP,IObject>``` - this struct definition uses the ```TInterface``` template to help define a class (a struct is class which is default public) which can be automatically recompiled at runtime. We derive from the base runtime compiled class ```IObject``, and use the ```IID_IRCCPP_MAIN_LOOP``` enumeration as an id. RCC++ needs these enums, though in this example we'll only have one class so it's not going to be used except here.

```REGISTERSINGLETON(RCCppMainLoop,true)``` - this macro registers the class ```RCCppMainLoop``` with RCC++ as one which will only have one instance (i.e. a singleton), and the second parameter instructs RCC++ to construct one instance when RCC++ is initialized. This way we don't have to construct an instance of the class in our own code.

The ```REGISTERSINGLETON``` macro and an alternative ```REGISTERCLASS``` macro are the primary methods through which the RuntimeObjectSystem in RCC++ is informed about which files are needed for compilation. At least one file must have a class registered through one of these macros. We'll show how to register code dependencies later on in this tutorial. See the [wiki page on Runtime Modifiable Classes](https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus/wiki/Runtime-Modifiable-Classes) for more information.

The code up to this point is available in the example from the branch Working_RCC++ at https://github.com/dougbinks/RCCpp_DX11_Example/tree/Working_RCC++. At this point we can run the program. When we save out the file RCCppMainLoop.cpp we should see debug output in Visual Studio with the code compiling.

## Working Dear ImGui with RCC++
Now that we have a working runtime compiled file, we add code to use Dear ImGui and call that from main.cpp.

[RCC++ Dear ImGui and DirectX Tutorial Video Part 4: Dear ImGui with RCC++](https://www.youtube.com/watch?v=Nj_VImRCZgU&list=PLRp7HE6uWI1m6tu_-vNUY-N_gnXT17WHQ&index=4)

For detailed steps see the [repo commit history on branch  RCC++_With_ImGui](https://github.com/dougbinks/RCCpp_DX11_Example/commits/RCC++_With_ImGui). 


All functions needed in main.cpp from the RCCppMainLoop class need to be exposed. To do so, add an abstract interface which exposes each function as a pure virtual function in a header, and derive from that in the RCCppMainLoop class:

**RCCppMainLoop.h**
```cpp
#pragma once

// abstract interface to our RCCppMainLoop class, using I at end to denote Interface
struct RCCppMainLoopI
{
    virtual void MainLoop() = 0;
};
```

Next step is to include the header in RCCppMainLoop.cpp then derive from the interface with an implementation of the MainLoop() function we added:

**RCCppMainLoop.cpp**
```cpp
struct RCCppMainLoop : RCCppMainLoopI, TInterface<IID_IRCCPP_MAIN_LOOP,IObject>
{
    void MainLoop() override
    {
    }
};
```

Our Main.cpp code needs to be able to get hold of the instance of our RCCppMainLoop class. This can be done through the IObjectFactorySystem but we'll use a simpler approach through a struct we call the SystemTable.

The RuntimeObjectSystem can be initialized with SystemTable pointer which is then exposed via ```PerModuleInterface::g_pSystemTable```. This is linked into modules compiled at runtime. RCC++ only forward declares ```SystemTable```, and to use this we need to add a definition which includes the variables and functions we need as members. We'll be adding useful data to our SystemTable to communicate between main.cpp and our RCCppMainLoop class.

We create a header for our SystemTable:

**SystemTable.h**
```cpp
#pragma once

#include "RuntimeInclude.h"
RUNTIME_MODIFIABLE_INCLUDE; //recompile runtime files when this changes

struct RCCppMainLoopI;
struct ImGuiContext;

struct SystemTable
{
    RCCppMainLoopI* pRCCppMainLoopI = 0;
    ImGuiContext*   pImContext      = 0;
};
```

We now add a constructor to our RCCppMainLoop class:

**RCCppMainLoop.cpp**
```cpp
struct RCCppMainLoop : RCCppMainLoopI, TInterface<IID_IRCCPP_MAIN_LOOP,IObject>
{
    RCCppMainLoop()
    {
        PerModuleInterface::g_pSystemTable->pRCCppMainLoopI = this;
    }

    void MainLoop() override
    {
    }
};
```

The constructor uses the PerModuleInterface to access the system table and set pRCCppMainLoopI. So when RCCppMainLoop  is recompiled we'll automatically see this pointer switch to the new class.

In main.cpp we now create a SystemTable object and change our RCC++ initialization code to pass the SystemTable to the RuntimeObjectSystem and at the same time we add code to add an include directory to the RCC++ build system using ```AddIncludeDir()```.:

**main.cpp**
```cpp
#include "SystemTable.h"
#include "RCCppMainLoop.h"

//...

static SystemTable              g_SystemTable;

//...

bool RCCppInit()
{
    g_pRuntimeObjectSystem = new RuntimeObjectSystem;
    if( !g_pRuntimeObjectSystem->Initialise(&g_Logger, &g_SystemTable) )
    {
        delete g_pRuntimeObjectSystem;
        g_pRuntimeObjectSystem = NULL;
        return false;
    }

    // ensure include directories are set - use location of this file as starting point
    FileSystemUtils::Path basePath = g_pRuntimeObjectSystem->FindFile( __FILE__ ).ParentPath();
    FileSystemUtils::Path imguiIncludeDir = basePath / "imgui";
    g_pRuntimeObjectSystem->AddIncludeDir( imguiIncludeDir.c_str() );

    return true;
}
```

We also add a call to the MainLoop() function in our **main.cpp** loop:
```cpp
        // Call the function in our RCC++ class
        g_SystemTable.pRCCppMainLoopI->MainLoop();
```

We need to let the RCC++ system know how to link the RCCppMainLoop.cpp file when it is compiled to Dear ImGui. We could build Dear ImGui as a library and use [RUNTIME_COMPILER_LINKLIBRARY](https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus/wiki/Using-libraries-from-runtime-modifiable-classes) but instead we'll be using [RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE](https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus/wiki/Runtime-source-dependencies).

The ```RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE``` macro allows us to specify files which are required to be built and linked to our RCC++ compiled code. For Dear ImGui we need to compile and link to several files, so we add these to our RCCppMainLoop.cpp file and then we can add Dear ImGui code and change it at runtime.

Changes to **RCCppMainLoop.cpp**:
```cpp
#include "imgui.h"

// add imgui source dependencies
// an alternative is to put imgui into a library and use RuntimeLinkLibrary
#include "RuntimeSourceDependency.h"
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_widgets", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_draw", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_demo", ".cpp" );

//...

    void MainLoop() override
    {
        ImGui::SetCurrentContext( PerModuleInterface::g_pSystemTable->pImContext );

        ImGui::SetNextWindowPos(ImVec2(50,400), ImGuiCond_Appearing );
        ImGui::SetNextWindowSize(ImVec2(0,0), ImGuiCond_Always );
        ImGui::Begin("RCCppMainLoop Window" );
        ImGui::Text("You can change Window's code at runtime!");
        ImGui::End();
    }
```

The code up to this point is available in the example from the branch RCC++_With_ImGui at https://github.com/dougbinks/RCCpp_DX11_Example/tree/RCC++_With_ImGui. The Dear ImGui code in MainLoop() can now be modified at runtime.

## Using DirectX with RCC++: part 1
For detailed steps take a look at the [repo commit history up to branch RCC++_With_D3D](https://github.com/dougbinks/RCCpp_DX11_Example/commits/RCC++_With_D3D).

[RCC++ Dear ImGui and DirectX Tutorial Video Part 5: Using DirectX with RCC++](https://www.youtube.com/watch?v=x2gxWi0Firs&list=PLRp7HE6uWI1m6tu_-vNUY-N_gnXT17WHQ&index=5)

Most DirectX functionality uses interfaces (abstract base classes using pure virtual functions), which can be used without linking to a library. This means that passing a pointer and including a header is all that's needed to use them with RCC++, which can be done through the SystemTable.

Modified **SystemTable.h**:
```cpp
#pragma once

#include "RuntimeInclude.h"
RUNTIME_MODIFIABLE_INCLUDE; //recompile runtime files when this changes

struct RCCppMainLoopI;
struct ImGuiContext;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;

static SystemTable*& g_pSys  = PerModuleInterface::g_pSystemTable;

struct SystemTable
{
    RCCppMainLoopI* pRCCppMainLoopI = 0;
    ImGuiContext*   pImContext      = 0;
    ID3D11Device*            pd3dDevice            = NULL;
    ID3D11DeviceContext*     pd3dDeviceContext     = NULL;
    IDXGISwapChain*          pSwapChain            = NULL;
    ID3D11RenderTargetView*  pMainRenderTargetView = NULL;
};
```

A static reference to the SystemTable is added so it's easier to use, the following code:
```cpp
        PerModuleInterface::g_pSystemTable->pd3dDeviceContext;
```
can be simplified to:
```cpp
        g_pSys-->pd3dDeviceContext;
```

Initialize these pointers in main.cpp and in RCCppMainLoop.cpp add ```#include <d3d11.h>``` to use most D3D functionality through the pointers in the system table.

We can now use the device context in our **RCCppMainLoop.cpp** code:
```cpp
// ...

#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800

// ...

    void MainLoop() override
    {
        // rest of code...

        g_pSys->pd3dDeviceContext->OMSetRenderTargets(1, &g_pSys->pMainRenderTargetView, NULL);
        g_pSys->pd3dDeviceContext->ClearRenderTargetView( g_pSys->pMainRenderTargetView, (float*)&clear_color);
    }

//...
```

However we've not been able to move over the call to ```Present()``` at this point as this we need to call ```ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());``` which is a function in imgui_impl_dx11.h. We could move all the Dear ImGui code into a library and then [use the library from the runtime modifiable code](https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus/wiki/Using-libraries-from-runtime-modifiable-classes) as we do in the next chapter, but instead as this is only one function we add a function pointer to the System Table.

Updates to **SystemTable.h**:
```cpp
//...

typedef void (*ImGui_ImplDX11_RenderDrawDataFunc)( ImDrawData* draw_data );

// more code...
struct SystemTable
{
    //...

    ImGui_ImplDX11_RenderDrawDataFunc  ImGui_ImplDX11_RenderDrawData = NULL;

    //...
}
```

In **main.cpp** we initialize this after our Dear ImGui context:
```cpp
    // set system table variables for ImGui and ImGui_Impl
    g_SystemTable.pImContext = ImGui::GetCurrentContext();
    g_SystemTable.ImGui_ImplDX11_RenderDrawData = ImGui_ImplDX11_RenderDrawData;
```

and then in **RCCppMainLoop.cpp** the end we have:
```cpp
    void MainLoop() override
    {
        //...

        // Rendering
        ImGui::Render();
        g_pSys->pd3dDeviceContext->OMSetRenderTargets(1, &g_pSys->pMainRenderTargetView, NULL);
        g_pSys->pd3dDeviceContext->ClearRenderTargetView( g_pSys->pMainRenderTargetView, (float*)&clear_color);

        g_pSys->ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_pSys->pSwapChain->Present(1, 0); // Present with vsync

    }
```

The code up to this point is available in the example from the branch RCC++_With_D3D at https://github.com/dougbinks/RCCpp_DX11_Example/tree/RCC++_With_D3D. The D3D code can be modified at runtime, for example vsync can be turned off by changing ```g_pSys->pSwapChain->Present(1, 0);``` to ```g_pSys->pSwapChain->Present(0, 0);```.

## Using DirectX with RCC++: part 2
Whilst most D3D functionality can be accessed through interface pointers, there are some functions which require linking to the appropriate D3D library. See the RCC++ wiki on [using libraries from runtime modifiable classes](https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus/wiki/Using-libraries-from-runtime-modifiable-classes) for more information on linking to libraries.

For detailed steps take a look at the [repo commit history up to branch RCC++_With_D3D_Library](https://github.com/dougbinks/RCCpp_DX11_Example/commits/RCC++_With_D3D_Library).

To inform RCC++ that it needs to link with a library when performing runtime compilation, use the ```RUNTIME_COMPILER_LINKLIBRARY``` macro. For non system libraries the library directories to search can be added with the ```IRuntimeObjectSystem::AddLibraryDir``` function.

In **RCCppMainLoop.cpp** add the following lines:
```cpp
#include "RuntimeLinkLibrary.h"
RUNTIME_COMPILER_LINKLIBRARY( "d3d11.lib" ); 
```

The device creation can now be moved over to the RCCppMainLoop.cpp, extending the interface so main.cpp can call the creation functions:

We add the creation and cleanup interface functions to **RCCppMainLoop.h**:
```cpp
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
```

And move those functions over to **RCCppMainLoop.cpp**:
```cpp
struct RCCppMainLoop : RCCppMainLoopI, TInterface<IID_IRCCPP_MAIN_LOOP,IObject>
{

    // rest of code....

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
```

These functions are the same as we had in the ```main.cpp``` code, but with the struct access ```g_SystemTable.``` replaced with the system table pointer access ```g_pSys->```. In ```main.cpp``` we remove these functions and their forward declarations and add ```g_SystemTable.pRCCppMainLoopI->``` in front of calls to these functions as they are now accessed through the pointer to our RCCppMainLoop object pointer in the System Table. So for example:
```cpp
        CleanupDeviceD3D();
```
becomes:
```cpp
        g_SystemTable.pRCCppMainLoopI->CleanupDeviceD3D();
```

The code up to this point is available in the example from the branch RCC++_With_D3D at https://github.com/dougbinks/RCCpp_DX11_Example/tree/RCC++_With_D3D_Library.

## Conclusion
In addition to showing how to convert a small example to code which can use RCC++ for live code editing, the RCCpp_DX11_Example is a good starting point for prototyping Dear ImGui code.

This tutorial has covered:
1. Adding the required RCC++ projects to a Visual Studio project
1. Adding a file with a class which can be compiled using runtime compilation
1. Adding the code needed to detect file changes, compile and then load them
1. Passing information to & from the runtime compiled code with the system table
1. Using source code dependencies
1. Using code which has abstract interfaces such as the ```ID3D11DeviceContext```
1. Linking to libraries with runtime compiled code

These techniques are the main approaches for building applications which use RCC++. For more advanced usage, from adding runtime protection, setting compiler optimization and debug levels, disabling RCC++ in shipping, to undo and redo functionality etc. check out the [Runtime Compiled C++ Wiki](https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus/wiki).
