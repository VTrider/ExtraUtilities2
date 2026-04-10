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
		if (value == nullptr)
			return false;
		return BZCC::Console::GetArgFloat(arg, value);
	}

	EXUAPI bool DLLAPI IFace_GetArgInteger(int arg, int* value)
	{
		if (value == nullptr)
			return false;
		return BZCC::Console::GetArgInteger(arg, value);
	}

	EXUAPI bool DLLAPI IFace_GetArgString(int arg, char** value)
	{
		if (value == nullptr)
			return false;
		return BZCC::Console::GetArgString(arg, value);
	}
}