#include "ExtraUtils.h"

namespace exu2
{
	constexpr const char* version = "1.2.0";

	EXUAPI const char* DLLAPI GetDLLVersion()
	{
		return version;
	}
}