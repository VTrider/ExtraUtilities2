#include "ExtraUtils.h"
#include "LuaHelpers.h"

#include <lua.hpp>

#include <string>

#define EXPORT(symbol) { #symbol, symbol },

namespace exu2
{
	static int GetPerspectiveMatrix(lua_State* L)
	{
		PushMatrix(L, GetPerspectiveMatrix());
		return 1;
	}

	static int WorldToScreen(lua_State* L)
	{
		Vector worldPos = CheckVectorOrSingles(L, 1);
		Vector screenPos;
		if (WorldToScreen(worldPos, &screenPos))
		{
			PushVector(L, screenPos);
		}
		else
		{
			lua_pushnil(L);
		}

		return 1;
	}

	static int GetViewMatrix(lua_State* L)
	{
		PushMatrix(L, GetViewMatrix());
		return 1;
	}

	static int IFace_GetArgCount(lua_State* L)
	{
		int count = IFace_GetArgCount();
		lua_pushinteger(L, count);
		return 1;
	}

	static int IFace_GetArgFloat(lua_State* L)
	{
		int arg = luaL_checkinteger(L, 1);
		float value{};
		bool success = IFace_GetArgFloat(arg, &value);

		if (success)
		{
			lua_pushnumber(L, value);
		}
		else
		{
			lua_pushnil(L);
		}

		lua_pushboolean(L, success);

		return 2;
	}

	static int IFace_GetArgInteger(lua_State* L)
	{
		int arg = luaL_checkinteger(L, 1);
		int value{};
		bool success = IFace_GetArgInteger(arg, &value);

		if (success)
		{
			lua_pushinteger(L, value);
		}
		else
		{
			lua_pushnil(L);
		}
		
		lua_pushboolean(L, success);

		return 2;
	}

	static int IFace_GetArgString(lua_State* L)
	{
		int arg = luaL_checkinteger(L, 1);
		char* value = nullptr;
		bool success = IFace_GetArgString(arg, &value);

		if (success && value != nullptr)
		{
			lua_pushstring(L, value);
		}
		else
		{
			lua_pushnil(L);
		}

		lua_pushboolean(L, success);

		return 2;
	}

	static int IFace_DeleteItem(lua_State* L)
	{
		ConstName name = luaL_checkstring(L, 1);
		bool result = IFace_DeleteItem(name);
		lua_pushboolean(L, result);
		return 1;
	}
/*
	static int VarSys_RegisterHandler(lua_State* L)
	{
		// Probably not able to be bound in lua due to function differences
		ConstName name = luaL_checkstring(L, 1);
		unsigned long magic = luaL_checklong(L, 3);
		VarSys_RegisterHandler(name, nullptr, magic);
		return 0;
	}

	static int VarSys_CreateCmd([[maybe_unused]] lua_State* L)
	{

	}
*/

	static int GetViewportSize(lua_State* L)
	{
		auto viewport = GetViewportSize();

		lua_pushinteger(L, viewport.first);
		lua_pushinteger(L, viewport.second);

		return 2;
	}

	static int GetSteam64(lua_State* L)
	{
		lua_pushstring(L, std::to_string(GetSteam64()).c_str());
		return 1;
	}

	static void RegisterConstants(lua_State* L)
	{
		lua_pushstring(L, versionString);
		lua_setfield(L, -2, "VERSION");
	}

	extern "C" __declspec(dllexport) int luaopen_ExtraUtilities2(lua_State* L)
	{
		constexpr luaL_Reg EXPORT_TABLE[] = {
			EXPORT(GetPerspectiveMatrix)
			EXPORT(WorldToScreen)
			EXPORT(GetViewMatrix)
			EXPORT(IFace_GetArgCount)
			EXPORT(IFace_GetArgFloat)
			EXPORT(IFace_GetArgInteger)
			EXPORT(IFace_GetArgString)
			EXPORT(IFace_DeleteItem)
			EXPORT(GetViewportSize)
			EXPORT(GetSteam64)
			{ 0, 0 }
		};
		luaL_newlib(L, EXPORT_TABLE);
		RegisterConstants(L);
		return 1;
	}
}