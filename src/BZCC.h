#pragma once

#include "Offsets.h"

#include <ScriptUtils.h>
#include <Windows.h>

#include <cstdint>

namespace BZCC
{
	inline const uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("battlezone2.exe"));

	namespace Console
	{
		using ArgCount_t = int(__cdecl*)(void);
		inline const ArgCount_t ArgCount = (ArgCount_t)(moduleBase + Offsets::ArgCount);

		using GetArgFloat_t = bool(__cdecl*)(int arg, float* value);
		inline const GetArgFloat_t GetArgFloat = (GetArgFloat_t)(moduleBase + Offsets::GetArgFloat);

		using GetArgInteger_t = bool(__cdecl*)(int arg, int* value);
		inline const GetArgInteger_t GetArgInteger = (GetArgInteger_t)(moduleBase + Offsets::GetArgInteger);

		using GetArgString_t = bool(__cdecl*)(int arg, char** value);
		inline const GetArgString_t GetArgString = (GetArgString_t)(moduleBase + Offsets::GetArgString);
	}

	namespace Steam
	{
		inline auto* steam64 = (uint64_t*)0x34690; // offset from steam_api.dll
	}

	namespace VarSys
	{
		using DeleteItem_t = bool(__cdecl*)(ConstName name);
		inline const DeleteItem_t DeleteItem = (DeleteItem_t)(moduleBase + Offsets::DeleteItem);
	};
}
