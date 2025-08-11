#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{
	EXUAPI int DLLAPI IFace_GetArgCount()
	{
		return BZCC::Console::ArgCount();
	}

	EXUAPI bool DLLAPI IFace_GetArgFloat(int arg, float* value)
	{
		return BZCC::Console::GetArgFloat(arg, value);
	}

	EXUAPI bool DLLAPI IFace_GetArgInteger(int arg, int* value)
	{
		return BZCC::Console::GetArgInteger(arg, value);
	}

	EXUAPI bool DLLAPI IFace_GetArgString(int arg, char** value)
	{
		return BZCC::Console::GetArgString(arg, value);
	}
}