#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{
	using namespace BZCC::Mission;

	const MisnExport* const DLLAPI GetMissionExport()
	{
		const MisnExport* const misnExport = *p_misnExport;
		return misnExport;
	}

	const MisnExport2* const DLLAPI GetMissionExport2()
	{
		const MisnExport2* const misnExport2 = *reinterpret_cast<MisnExport2**>(reinterpret_cast<uintptr_t>(p_misnExport) - 4);
		return misnExport2;
	}
}