#include "ExtraUtils.h"
#include "LuaHelpers.h"

#include <lua.hpp>

#include <string>

#define EXPORT(symbol) { #symbol, symbol },

namespace exu2::lua
{
	int GetPerspectiveMatrix(lua_State* L)
	{
		PushMatrix(L, exu2::GetPerspectiveMatrix());
		return 1;
	}

	int GetViewMatrix(lua_State* L)
	{
		PushMatrix(L, exu2::GetViewMatrix());
		return 1;
	}

	int InSatellite(lua_State* L)
	{
		lua_pushboolean(L, exu2::InSatellite());
		return 1;
	}

	int IsVisible(lua_State* L)
	{
		if (auto h = CheckHandle(L, 1))
		{
			lua_pushboolean(L, exu2::IsVisible(*h));
		}
		else if (auto m = CheckMatrix(L, 1))
		{
			lua_pushboolean(L, exu2::IsVisible(**m));
		}
		else if (auto v = CheckVector(L, 1))
		{
			lua_pushboolean(L, exu2::IsVisible(**v));
		}
		else
		{
			return luaL_argerror(L, 1, "Extra Utilities 2 Error: Invalid argument to IsVisible");
		}
		return 1;
	}

	int WorldToScreen(lua_State* L)
	{
		auto Overload = [L](auto&& pos)
		{
			Vector outScreen{};
			if (exu2::WorldToScreen(pos, &outScreen))
			{
				PushVector(L, outScreen);
			}
			else
			{
				lua_pushnil(L);
			}
		};

		if (auto h = CheckHandle(L, 1))
		{
			Overload(*h);
		}
		else if (auto m = CheckMatrix(L, 1))
		{
			Overload(**m);
		}
		else if (auto v = CheckVectorOrSingles(L, 1))
		{
			Overload(*v);
		}
		else
		{
			return luaL_argerror(L, 1, "Extra Utilities 2 Error: Invalid argument to WorldToScreen");
		}
		return 1;
	}

	int IFace_GetArgCount(lua_State* L)
	{
		int count = exu2::IFace_GetArgCount();
		lua_pushinteger(L, count);
		return 1;
	}

	int IFace_GetArgFloat(lua_State* L)
	{
		int arg = luaL_checkinteger(L, 1);
		float value{};
		bool success = exu2::IFace_GetArgFloat(arg, &value);

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

	int IFace_GetArgInteger(lua_State* L)
	{
		int arg = luaL_checkinteger(L, 1);
		int value{};
		bool success = exu2::IFace_GetArgInteger(arg, &value);

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

	int IFace_GetArgString(lua_State* L)
	{
		int arg = luaL_checkinteger(L, 1);
		char* value = nullptr;
		bool success = exu2::IFace_GetArgString(arg, &value);

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

	int GetBZCCPath(lua_State* L)
	{
		lua_pushstring(L, exu2::GetBZCCPath().string().c_str());
		return 1;
	}

	int GetWorkshopPath(lua_State* L)
	{
		lua_pushstring(L, exu2::GetWorkshopPath().string().c_str());
		return 1;
	}

	int GetViewportSize(lua_State* L)
	{
		iVector2 viewport = exu2::GetViewportSize();

		lua_pushinteger(L, viewport.x);
		lua_pushinteger(L, viewport.y);

		return 2;
	}

	int GetSteam64(lua_State* L)
	{
		lua_pushstring(L, std::to_string(exu2::GetSteam64()).c_str());
		return 1;
	}

	int IFace_DeleteItem(lua_State* L)
	{
		ConstName name = luaL_checkstring(L, 1);
		bool result = exu2::IFace_DeleteItem(name);
		lua_pushboolean(L, result);
		return 1;
	}


	void RegisterConstants(lua_State* L)
	{
		lua_pushstring(L, versionString);
		lua_setfield(L, -2, "VERSION");
	}

	extern "C" __declspec(dllexport) int luaopen_ExtraUtilities2(lua_State* L)
	{
		constexpr luaL_Reg EXPORT_TABLE[] = {
			EXPORT(GetPerspectiveMatrix)
			EXPORT(GetViewMatrix)
			EXPORT(InSatellite)
			EXPORT(IsVisible)
			EXPORT(WorldToScreen)
			EXPORT(IFace_GetArgCount)
			EXPORT(IFace_GetArgFloat)
			EXPORT(IFace_GetArgInteger)
			EXPORT(IFace_GetArgString)
			EXPORT(GetBZCCPath)
			EXPORT(GetWorkshopPath)
			EXPORT(GetViewportSize)
			EXPORT(GetSteam64)
			EXPORT(IFace_DeleteItem)
			{ 0, 0 }
		};
		luaL_newlib(L, EXPORT_TABLE);
		RegisterConstants(L);
		return 1;
	}
}