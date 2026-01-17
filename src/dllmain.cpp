// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>
#include <delayimp.h>

#include <cstring>
#include <exception>
 
FARPROC WINAPI DelayLoadHandler(unsigned int dliNotify, [[maybe_unused]] PDelayLoadInfo pdli)
{
	if (_stricmp(pdli->szDll, "LuaMission.dll") == 0)
	{
		if (dliNotify == dliFailGetProc)
		{
			const char* msg = "This mod is using a custom LuaMission.dll that does not provide "
							  "exports for the Lua C API. This is highly discouraged. Please contact "
							  "the mod author to update it to conform to stock standards.";
			MessageBox(NULL, msg, "Extra Utilities 2", MB_ICONERROR | MB_APPLMODAL);
			std::terminate();
		}
	}

	return NULL;
}

extern "C" const PfnDliHook  __pfnDliNotifyHook2 = DelayLoadHandler;
extern "C" const PfnDliHook  __pfnDliFailureHook2 = DelayLoadHandler;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       [[maybe_unused]] LPVOID opReserved
                     )
{
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		break;
	case DLL_PROCESS_DETACH:
		if (GetModuleHandle("LuaMission.dll"))
		{
			__FUnloadDelayLoadedDLL2("LuaMission.dll");
		}
		break;
	}
    return TRUE;
}
