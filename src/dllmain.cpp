// dllmain.cpp : Defines the entry point for the DLL application.

#include "ExtraUtils.h"
#include <ScriptUtils.h>

#include <Windows.h>
#include <delayimp.h>

#include <cstring>
#include <format>
#include <string>

namespace exu2
{
	void Startup()
	{
		if (int ver = GetGameMinorVersion(); ver  < MINIMUM_REQUIRED_VERSION)
		{
			std::wstring message = std::format(L"Game version {} is incompatible. Minimum required version is {}", ver, MINIMUM_REQUIRED_VERSION);
			MessageBoxW(NULL, message.c_str(), L"Extra Utilities 2", MB_APPLMODAL | MB_ICONERROR);
			std::terminate();
		}
		PrintConsoleMessage("Running Extra Utilities 2 v{} by VTrider", GetDLLVersion());
	}

	void Shutdown()
	{
		VarSys_UninstallGlobalHandler();
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
			const wchar_t* message = L"This mod is using a custom LuaMission.dll that does not provide exports for the Lua C API."
									  "This is highly discouraged. Please contact the mod author to update it to conform to stock standards.";
			MessageBoxW(NULL, message, L"Extra Utilities 2", MB_ICONERROR);
			// this isn't working idk why
			// exu2::GetMissionExport()->misnImport->FailMission(0.0f, "custom_lm.txt");
		}
	}

	return NULL;
}

extern "C" const PfnDliHook  __pfnDliNotifyHook2 = DelayLoadHandler;
extern "C" const PfnDliHook  __pfnDliFailureHook2 = DelayLoadHandler;
