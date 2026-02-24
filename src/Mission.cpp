#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{
	EXUAPI const MisnExport* const DLLAPI GetMissionExport()
	{
		return BZCC::Mission::misnExport;
	}

	EXUAPI const MisnExport2* const DLLAPI GetMissionExport2()
	{
		return BZCC::Mission::misnExport2;
	}
}