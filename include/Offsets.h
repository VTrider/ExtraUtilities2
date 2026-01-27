#pragma once

#include "Offsets185.h"
#include "Offsets200.h"
#include "Offsets204.h"

#include "ExtraUtils.h"

#define RESOLVE_VERSIONED_OFFSET(name) \
	[]() -> uintptr_t \
	{ \
		int minorVersion = exu2::GetGameMinorVersion(); \
		if (minorVersion == 185) \
		{ \
			return Offsets::V185::##name; \
		} \
		else if (minorVersion == 200) \
		{ \
			return Offsets::V200::##name; \
		} \
		else if (minorVersion == 204) \
		{ \
			return Offsets::V204::##name; \
		} \
		else \
			std::terminate(); \
	}()

namespace Offsets
{
	inline const uintptr_t ArgCount           = RESOLVE_VERSIONED_OFFSET(ArgCount);
    inline const uintptr_t GetArgFloat        = RESOLVE_VERSIONED_OFFSET(GetArgFloat);
    inline const uintptr_t GetArgInteger      = RESOLVE_VERSIONED_OFFSET(GetArgInteger);
    inline const uintptr_t GetArgString       = RESOLVE_VERSIONED_OFFSET(GetArgString);
    inline const uintptr_t DeleteItem         = RESOLVE_VERSIONED_OFFSET(DeleteItem);
    inline const uintptr_t CreateCmd          = RESOLVE_VERSIONED_OFFSET(CreateCmd);
    inline const uintptr_t RegisterHandler    = RESOLVE_VERSIONED_OFFSET(RegisterHandler);
    inline const uintptr_t inSatellite        = RESOLVE_VERSIONED_OFFSET(inSatellite);
    inline const uintptr_t netPlayerInfoArray = RESOLVE_VERSIONED_OFFSET(netPlayerInfoArray);
    inline const uintptr_t activeConfigMod    = RESOLVE_VERSIONED_OFFSET(activeConfigMod);
    inline const uintptr_t misnExport         = RESOLVE_VERSIONED_OFFSET(misnExport);
}
