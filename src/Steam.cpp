#include "BZCC.h"
#include "ExtraUtils.h"
#include "Scanner.h"

#include <ScriptUtils.h>

namespace exu2
{
	EXUAPI const char* const DLLAPI GetActiveConfigMod()
	{
		return BZCC::Steam::activeConfigMod;
	}

	uint64_t DLLAPI GetSteam64()
	{
		return *BZCC::Steam::steam64;
	}

	EXUAPI uint64_t DLLAPI GetSteam64(int team)
	{
		if (IsNetworkOn())
		{
			BZCC::NetPlayerInfo* info = BZCC::NetPlayerInfo::netPlayerInfoArray[team];
			return (info) ? info->steam64 : 0ULL;
		}
		else if (team == GetLocalPlayerTeamNumber())
		{
			return GetSteam64();
		}
		else
		{
			return 0ULL;
		}
	}
}