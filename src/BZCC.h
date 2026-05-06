#pragma once

#include "Offsets.h"

#include <ScriptUtils.h>
#include <Windows.h>
#undef CONST

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

	class GameObjectClass;

	class GameObject
	{
	private:
		using GetObj_t = GameObject*(__fastcall*)(Handle h);

	public:
		uint8_t pad_1[0x11E];
		GameObjectClass* objClass; // UNTESTED

		static inline const GetObj_t GetObj = []() // UNTESTED
		{
			uintptr_t call_set_as_user = reinterpret_cast<uintptr_t>(SetAsUser) + 7;
			uintptr_t next_instruction = call_set_as_user + 5;
			uintptr_t relative_jmp_offset = *reinterpret_cast<uintptr_t*>(call_set_as_user + 1);
			return reinterpret_cast<GetObj_t>(next_instruction + relative_jmp_offset);
		}();
	};

	class GameObjectClass 
	{
	private:
		using Find_t = GameObjectClass*(__fastcall*)(const char* odf);

	public:
		static inline Find_t Find = reinterpret_cast<Find_t>(moduleBase + 0x166E2B); // TODO: pattern scan, currently 204.0
	};

	namespace Mission
	{
		inline MisnExport** p_misnExport =  *reinterpret_cast<MisnExport***>(moduleBase + Offsets::misnExport);
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

	class SchedPlan
	{
	private:
		// This is what AIPs use to find buildable terrain, but we can use it outside of an AIP context
		using GoodSpot_t = bool(__fastcall*)(int team, const GameObjectClass* buildClass, Vector& pos, const Vector& front);

		// WARNING: the base function uses a custom calling convention where the parameters are in fastcall order
		// but the caller cleans up the stack, you should not use this directly
		static inline const GoodSpot_t GoodSpotUnsafe = reinterpret_cast<GoodSpot_t>(moduleBase + 0x2A3CC0); // TODO: pattern scan, current offset is 204.0

	public:
		// Wrapper over the game function that accounts for the custom calling convention
		static bool GoodSpot(int team, const GameObjectClass* buildClass, Vector& pos, const Vector& front)
		{
			bool result;
			__asm
			{
				push front
				push pos
				mov edx, buildClass
				mov ecx, team
				call GoodSpotUnsafe
				mov result, al
				add esp, 0x08
			}
			return result;
		}
	};

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

		class VarScope
		{
		public:
			uint8_t pad_1[0x28];
			VarSysHandler handler;
		};

		inline VarScope** const p_gScope = *reinterpret_cast<VarScope***>(moduleBase + Offsets::globalHandler);

		class VarItem
		{
		public:
			enum class Flag : uint32_t
			{
				CONST = 0x4,
				NODELETE = 0x8000
			};

			uint8_t pad_1[0x18];
			uint32_t flags;
		};

		using FindVarItem_t = VarItem*(__fastcall*)(ConstName name);

		inline const FindVarItem_t FindVarItem = []()
		{
			uintptr_t call_find_var_item = reinterpret_cast<uintptr_t>(IFace_CreateCommand) + 19;
			uintptr_t next_instruction = call_find_var_item + 5;
			uintptr_t relative_jmp_offset = *reinterpret_cast<uintptr_t*>(call_find_var_item + 1);
			return reinterpret_cast<FindVarItem_t>(next_instruction + relative_jmp_offset);
		}();
	}
}
