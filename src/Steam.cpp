#include "BZCC.h"
#include "ExtraUtils.h"
#include "Scanner.h"

#include <ScriptUtils.h>

namespace exu2
{
	uint64_t DLLAPI GetSteam64()
	{
		if (IsNetworkOn())
		{
			int myTeam = GetLocalPlayerTeamNumber();
			return GetSteam64(myTeam);
		}
		else
		{
			return *BZCC::Steam::steam64;
		}
	}

	EXUAPI uint64_t DLLAPI GetSteam64(int team)
	{
		BZCC::NetPlayerInfo* info = BZCC::NetPlayerInfo::netPlayerInfoArray[team];
		return (info) ? info->steam64 : 0LL;
	}
}