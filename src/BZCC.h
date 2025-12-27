#pragma once

#include "Offsets.h"

#include <ScriptUtils.h>
#include <Windows.h>

#include <cstdint>

namespace BZCC
{
	inline const HMODULE moduleHandle = GetModuleHandle("battlezone2.exe");
	inline const uintptr_t moduleBase = reinterpret_cast<uintptr_t>(moduleHandle);

	class Camera
	{
	public:
		// TODO: Reverse struct
		uint8_t pad1[0x160];
		Matrix perspective;
		Matrix view;

		static inline const Camera* const mainCamera = []()
		{
			// This is based off of the GetCameraPosition export, it is unlikely to change
			uintptr_t offset = reinterpret_cast<uintptr_t>(GetCameraPosition) + 5;
			auto val= *reinterpret_cast<Camera***>(offset);
			return *val;
		}();
	};

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

		using VarSysHandler = void(__cdecl*)(unsigned long crc);
		using RegisterHandler_t = void(__cdecl*)(ConstName name, VarSysHandler handler, unsigned long magic);
		inline const RegisterHandler_t RegisterHandler = (RegisterHandler_t)(moduleBase + Offsets::RegisterHandler);

		using CreateCmd_t = void(__cdecl*)(ConstName name);
		inline const CreateCmd_t CreateCmd = (CreateCmd_t)(moduleBase + Offsets::CreateCmd);
	}
}
