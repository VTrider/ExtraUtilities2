#pragma once

#include "Offsets.h"

#include <ScriptUtils.h>
#include <Windows.h>

#include <cstdint>

namespace BZCC
{
	inline const HMODULE moduleHandle = GetModuleHandleW(L"battlezone2.exe");
	inline const uintptr_t steamAPIBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(L"steam_api.dll"));
	inline const uintptr_t moduleBase = reinterpret_cast<uintptr_t>(moduleHandle);

	class Camera
	{
	public:
		// TODO: Reverse struct
		uint8_t pad1[0x160];
		Matrix perspective;
		Matrix view;
		uint8_t pad2[0x114];

		// IMPORTANT: this is not actually specifically satellite mode,
		// it's a flag that disables all fog if set to 1, which happens to
		// coincide with satellite mode. There is a related value that unlocks the
		// cursor from the center of the screen you can find easily with memory scanning
		// which also follows the satellite state, but it may have other uses for war thunder
		// style aiming or something? The value is currently set to const since changing it
		// will affect the fog and not the satellite state, this api will change if 
		// the actual satellite state flag/function is found.
		static inline const volatile bool* const inSatellite = *reinterpret_cast<bool**>(moduleBase + Offsets::inSatellite);

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

#pragma pack(push, 1)
	class NetPlayerInfo
	{
	public:
		char nickname[32]; // includes null terminator
		uint8_t pad_1[92];
		uint64_t steam64;

		// TODO: this is actually something different not the g_pNetPlayerInfo see 1.3 pdb
		// Array of 16 values one per team slot presumably, can be filled with garbage or ai players,
		// so validate there's actually a player there before using the value.
		// ONLY ACTIVE IN MP
		static inline NetPlayerInfo** netPlayerInfoArray = *reinterpret_cast<NetPlayerInfo***>(moduleBase + Offsets::netPlayerInfoArray);
	};
#pragma pack(pop)

	namespace Steam
	{
		inline const char* const activeConfigMod = *reinterpret_cast<char**>(moduleBase + Offsets::activeConfigMod);
		inline const uint64_t* const steam64 = reinterpret_cast<uint64_t*>(steamAPIBase + 0x34690);
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
