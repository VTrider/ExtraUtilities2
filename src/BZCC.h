/*
* Offsets for BZCC
* Calculate the address at runtime with
* moduleBase + offset = address
*/

#pragma once

#include <ScriptUtils.h>
#include <Windows.h>

#include <cstdint>

namespace BZCC
{
	// Game updates are API breaking and the offsets should not be used until they have been
	// updated to the new version
	inline const char* currentBZCCVersion = "2.0.200";

	inline const uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("battlezone2.exe"));

	namespace Console
	{
		using ArgCount_t = int(__cdecl*)(void);
		inline const ArgCount_t ArgCount = (ArgCount_t)(moduleBase + 0x0034DE71);

		using GetArgFloat_t = bool(__cdecl*)(int arg, float* value);
		inline const GetArgFloat_t GetArgFloat = (GetArgFloat_t)(moduleBase + 0x0034DEC9);

		using GetArgInteger_t = bool(__cdecl*)(int arg, int* value);
		inline const GetArgInteger_t GetArgInteger = (GetArgInteger_t)(moduleBase + 0x0034E13A);

		using GetArgString_t = bool(__cdecl*)(int arg, char** value);
		inline const GetArgString_t GetArgString = (GetArgString_t)(moduleBase + 0x0034E109);
	}

	namespace Steam
	{
		inline auto* steam64 = (uint64_t*)0x34690; // offset from steam_api.dll
	}

	namespace VarSys
	{
		using DeleteItem_t = bool(__cdecl*)(ConstName name);
		inline const DeleteItem_t DeleteItem = (DeleteItem_t)(moduleBase + 0x003494BE);
	};
}
