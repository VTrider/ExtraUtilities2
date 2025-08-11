#include "BZCC.h"
#include "ExtraUtils.h"
#include "Scanner.h"

namespace exu2
{
	const Scanner<uint64_t> s64(BZCC::Steam::steam64, BasicScanner::Restore::DISABLED, BasicScanner::BaseAddress::STEAMAPI);

	uint64_t DLLAPI GetSteam64()
	{
		return s64.Read();
	}
}