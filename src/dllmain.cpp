// dllmain.cpp : Defines the entry point for the DLL application.

#include "ExtraUtils.h"
#include <ScriptUtils.h>

#include <Windows.h>
#include <delayimp.h>

#include <cstring>
#include <exception>
#include <format>

namespace exu2
{
	void Startup()
	{
		PrintConsoleMessage(std::format("Running Extra Utilities 2 v{} by VTrider", GetDLLVersion()).c_str());
	}

	void Shutdown()
	{
		if (GetModuleHandleW(L"LuaMission.dll"))
		{
			__FUnloadDelayLoadedDLL2("LuaMission.dll");
		}
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       [[maybe_unused]] LPVOID opReserved
                     )
{
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		exu2::Startup();
		break;
	case DLL_PROCESS_DETACH:
		exu2::Shutdown();
		break;
	}
    return TRUE;
}

FARPROC WINAPI DelayLoadHandler(unsigned int dliNotify, [[maybe_unused]] PDelayLoadInfo pdli)
{
	if (_stricmp(pdli->szDll, "LuaMission.dll") == 0)
	{
		if (dliNotify == dliFailGetProc)
		{
			const wchar_t* msg = L"This mod is using a custom LuaMission.dll that does not provide "
								  "exports for the Lua C API. This is highly discouraged. Please contact "
								  "the mod author to update it to conform to stock standards.";
			MessageBoxW(NULL, msg, L"Extra Utilities 2", MB_ICONERROR | MB_APPLMODAL);
			std::terminate();
		}
	}

	return NULL;
}

extern "C" const PfnDliHook  __pfnDliNotifyHook2 = DelayLoadHandler;
extern "C" const PfnDliHook  __pfnDliFailureHook2 = DelayLoadHandler;
