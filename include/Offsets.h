#pragma once

#include "Offsets205.3.h"
#include "Offsets206.9.h"

#include "ExtraUtils.h"

namespace BZCC
{
	inline const HMODULE moduleHandle = GetModuleHandleW(L"battlezone2.exe");
	inline const uintptr_t steamAPIBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(L"steam_api.dll"));
	inline const uintptr_t moduleBase = reinterpret_cast<uintptr_t>(moduleHandle);
}

#define RESOLVE_VERSIONED_OFFSET(name) \
	[]() -> uintptr_t \
	{ \
		int minorVersion = exu2::GetGameMinorVersion(); \
		if (minorVersion == 205 && exu2::GetGamePatchVersion() == 3) \
		{ \
			return Offsets::V205_3::##name; \
		} \
		else if (minorVersion == 206 && exu2::GetGamePatchVersion() == 9) \
		{ \
			return Offsets::V206_9::##name; \
		} \
		else \
			std::terminate(); \
	}()

namespace Offsets
{
	inline const uintptr_t ArgCount               = RESOLVE_VERSIONED_OFFSET(ArgCount);
    inline const uintptr_t GetArgFloat            = RESOLVE_VERSIONED_OFFSET(GetArgFloat);
    inline const uintptr_t GetArgInteger          = RESOLVE_VERSIONED_OFFSET(GetArgInteger);
    inline const uintptr_t GetArgString           = RESOLVE_VERSIONED_OFFSET(GetArgString);
    inline const uintptr_t DeleteItem             = RESOLVE_VERSIONED_OFFSET(DeleteItem);
    inline const uintptr_t CreateCmd              = RESOLVE_VERSIONED_OFFSET(CreateCmd);
    inline const uintptr_t RegisterHandler        = RESOLVE_VERSIONED_OFFSET(RegisterHandler);
    inline const uintptr_t inSatellite            = RESOLVE_VERSIONED_OFFSET(inSatellite);
    inline const uintptr_t netPlayerInfoArray     = RESOLVE_VERSIONED_OFFSET(netPlayerInfoArray);
    inline const uintptr_t activeConfigMod        = RESOLVE_VERSIONED_OFFSET(activeConfigMod);
    inline const uintptr_t misnExport             = RESOLVE_VERSIONED_OFFSET(misnExport);
	inline const uintptr_t globalHandler          = RESOLVE_VERSIONED_OFFSET(globalHandler);
	inline const uintptr_t GameObjectClass_Find   = RESOLVE_VERSIONED_OFFSET(GameObjectClass_Find);
	inline const uintptr_t SchedPlan_GoodSpot     = RESOLVE_VERSIONED_OFFSET(SchedPlan_GoodSpot);
	inline const uintptr_t Armory_QueueBuild      = RESOLVE_VERSIONED_OFFSET(Armory_QueueBuild);
	inline const uintptr_t Constructor_QueueBuild = []()
	{
		// Notes from ghidra: rel32-call: target = match + 0xC + signed read_i32(match + 0x8)
		uintptr_t match = BZCC::moduleBase + RESOLVE_VERSIONED_OFFSET(Constructor_QueueBuild);
		intptr_t offset = *reinterpret_cast<intptr_t*>(match + 0x8);
		// Subtract moduleBase from it to make it consistent with the other offsets that require you to add moduleBase before using them
		return match + 0xC + offset - BZCC::moduleBase;
	}();
	inline const uintptr_t Factory_QueueBuild     = RESOLVE_VERSIONED_OFFSET(Factory_QueueBuild);
}
