#pragma once

#ifdef EXU_EXPORTS
#define EXUAPI __declspec(dllexport)
#else
#define EXUAPI __declspec(dllimport)
#endif

#include <ScriptUtils.h>

#include <Windows.h>

#include <cstdint>

namespace exu2
{
	constexpr const char* versionString = "1.0.0";
	// The following functions are used in ProcessCommand(long crc):

	// Gets the count of arguments supplied to the current command
	// note that it also includes the name of the command, so it will always
	// be a minimum of 1, subtract 1 for the real count of arguments supplied
	EXUAPI int DLLAPI IFace_GetArgCount();

	// The out parameter in these three functions should not be a nullptr,
	// return value is true if it could parse the correct data type, false if not.
	// In C++ you should initialize the value to 0 or nullptr in the case of GetArgString,
	// in Lua it will always return nil if the function fails

	// Gets a float value at the given position if it exists
	EXUAPI bool DLLAPI IFace_GetArgFloat(int arg, float* value);

	// Gets an integer value at the given position if it exists
	EXUAPI bool DLLAPI IFace_GetArgInteger(int arg, int* value);

	// Gets a string value at the given position if it exists
	EXUAPI bool DLLAPI IFace_GetArgString(int arg, char** value);

	// Deletes an IFace item and all its subdirectories, returns true if
	// successful, or false if the item does not exist
	EXUAPI bool DLLAPI IFace_DeleteItem(ConstName name);

	// Gets the Steam 64 ID of the local user
	EXUAPI uint64_t DLLAPI GetSteam64();

	// Same as the lua function
	inline int GetTPS()
	{
		return SecondsToTurns(1.0f);
	}
}