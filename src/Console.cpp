#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{
	int DLLAPI IFace_GetArgCount()
	{
		return BZCC::Console::ArgCount();
	}

	bool DLLAPI IFace_GetArgFloat(int arg, float& value)
	{
		return BZCC::Console::GetArgFloat(arg, &value);
	}

	bool DLLAPI IFace_GetArgInteger(int arg, int& value)
	{
		return BZCC::Console::GetArgInteger(arg, &value);
	}

	bool DLLAPI IFace_GetArgString(int arg, char*& value)
	{
		return BZCC::Console::GetArgString(arg, &value);
	}

	bool DLLAPI IFace_GetArgBool(int arg, bool& value)
	{
		const auto toLower = [](std::string& s) { std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {return std::tolower(c); }); };
		char* stringArg;
		int intArg;
		if (IFace_GetArgString(arg, stringArg))
		{
			std::string str = stringArg;
			toLower(str);
			if (str == "true")
			{
				value = true;
				return true;
			}
			else if (str == "false")
			{
				value = false;
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (IFace_GetArgInteger(arg, intArg))
		{
			if (intArg == 0 || intArg == 1)
			{
				value = intArg;
				return true;
			}
			return false;
		}

		return false;
	}
}