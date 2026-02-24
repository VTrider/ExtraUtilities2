// dllmain.cpp : Defines the entry point for the DLL application.

#include "ExtraUtils.h"
#include <ScriptUtils.h>

#include <Windows.h>
#include <delayimp.h>

#include <cstring>

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
			exu2::GetMissionExport()->misnImport->FailMission(0.0f, "custom_lm.txt");
		}
	}

	return NULL;
}

extern "C" const PfnDliHook  __pfnDliNotifyHook2 = DelayLoadHandler;
extern "C" const PfnDliHook  __pfnDliFailureHook2 = DelayLoadHandler;
