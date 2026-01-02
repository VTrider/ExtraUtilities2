#pragma once

#ifdef EXU_EXPORTS
#define EXUAPI __declspec(dllexport)
#else
#define EXUAPI __declspec(dllimport)
#endif

#include <ScriptUtils.h>

#include <Windows.h>

#include <cstdint>
#include <tuple>

namespace exu2
{
	constexpr const char* versionString = "1.0.0";
	constexpr const char* gameVersion = "2.0.204.1";

	using VarSysHandler = void(__cdecl*)(unsigned long crc);

	struct iVector2
	{
		int x, y;
	};

	// Camera

	// Perspective functions warning: don't use the built in matrix functions,
	// they only work on the 3x3 portion of the matrix, perspective transformations
	// require 4x4, and you need vec4's with a W component 

	// Returns the current perspective projection matrix
	EXUAPI Matrix DLLAPI GetPerspectiveMatrix();

	// Returns the current view matrix 
	EXUAPI Matrix DLLAPI GetViewMatrix();

	// Fills outScreen with normalized screen coordinates [0,1] that correspond to a position in the world.
	// The z component is the depth, larger values are closer to the camera.
	// Returns true if the position is visible, otherwise false.
	EXUAPI bool DLLAPI WorldToScreen(const Vector& worldPosition, Vector* outScreen);

	// Console

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

	// Graphics

	// Gets the current viewport size in pixels (X, Y)
	EXUAPI iVector2 GetViewportSize();

	// Steam

	// Gets the Steam 64 ID of the local user
	EXUAPI uint64_t DLLAPI GetSteam64();

	// VarSys

	// Low level create command. Creates an "unregistered" VarSys command, it will show up in the `ls` command but
	// it will not seen by the current mission's ProcessCommand function. You can use VarSys_RegisterHandler to set
	// a custom handler that can even work outside of a game. WARNING: these commands are NODELETE by default
	// and I don't know why, so this function probably isn't too useful. UNABLE TO BE BOUND IN LUA
	EXUAPI void DLLAPI VarSys_CreateCmd(ConstName name);

	// Deletes an IFace item and all its subdirectories, returns true if
	// successful, or false if the item does not exist
	EXUAPI bool DLLAPI IFace_DeleteItem(ConstName name);

	// Registers a handler for a VarSys scope, ie. in a command "exu.stuff.function", "exu" and "stuff" are both
	// considered a scope. The handler is a function that follows the same API as ProcessCommand in ScriptUtils.
	// The magic number is usually 0 in the game's code so I recommend passing that in, anything else is untested.
	// UNABLE TO BE BOUND IN LUA
	EXUAPI void DLLAPI VarSys_RegisterHandler(ConstName name, VarSysHandler handler, unsigned long magic);

	// Same as the lua function
	inline int GetTPS()
	{
		return SecondsToTurns(1.0f);
	}
}