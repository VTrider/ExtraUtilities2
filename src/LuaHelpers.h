#pragma once

#include <lua.hpp>
#include <ScriptUtils.h>

#include <optional>

namespace exu2
{
	inline void PushMatrix(lua_State* L, const Matrix& m)
	{
		lua_getglobal(L, "SetMatrix");

		lua_pushnumber(L, m.right.x);
		lua_pushnumber(L, m.right.y);
		lua_pushnumber(L, m.right.z);
		lua_pushnumber(L, m.up.x);
		lua_pushnumber(L, m.up.y);
		lua_pushnumber(L, m.up.z);
		lua_pushnumber(L, m.front.x);
		lua_pushnumber(L, m.front.y);
		lua_pushnumber(L, m.front.z);
		lua_pushnumber(L, m.posit.x);
		lua_pushnumber(L, m.posit.y);
		lua_pushnumber(L, m.posit.z);

		lua_call(L, 12, 1);

		// The lua function doesn't set W so we do it manually
		lua_pushnumber(L, m.rightw);
		lua_setfield(L, -2, "right_w");

		lua_pushnumber(L, m.upw);
		lua_setfield(L, -2, "up_w");

		lua_pushnumber(L, m.frontw);
		lua_setfield(L, -2, "right_w");

		lua_pushnumber(L, m.positw);
		lua_setfield(L, -2, "posit_w");
	}


	inline void PushVector(lua_State* L, const Vector& v)
	{
		lua_getglobal(L, "SetVector");

		lua_pushnumber(L, v.x);
		lua_pushnumber(L, v.y);
		lua_pushnumber(L, v.z);

		lua_call(L, 3, 1);
	}

	// Notes on "require" and "check" functions, string for
	// all userdata types is identical to their C type ie
	// Handle -> "Handle", Quaternion -> "Quaternion"

	inline Handle RequireHandle(lua_State* L, int idx)
	{
		return reinterpret_cast<Handle>(luaL_checkudata(L, idx, "Handle"));
	}

	inline std::optional<Handle> CheckHandle(lua_State* L, int idx)
	{
		if (Handle h = reinterpret_cast<Handle>(luaL_testudata(L, idx, "Handle")))
		{
			return h;
		}
		else
		{
			return std::nullopt;
		}
	}

	inline Vector* RequireVector(lua_State* L, int idx)
	{
		return reinterpret_cast<Vector*>(luaL_checkudata(L, idx, "Vector"));
	}

	inline std::optional<Vector*> CheckVector(lua_State* L, int idx)
	{
		if (Vector* h = reinterpret_cast<Vector*>(luaL_testudata(L, idx, "Vector")))
		{
			return h;
		}
		else
		{
			return std::nullopt;
		}
	}

	// Get either a vector or three numbers from lua
	inline std::optional<Vector> CheckVectorOrSingles(lua_State* L, int idx)
	{
		Vector v{};
		if (auto optv = CheckVector(L, idx))
		{
			v = **optv;
		}
		else if (lua_gettop(L) == 3)
		{
			v.x = static_cast<float>(luaL_checknumber(L, idx));
			v.y = static_cast<float>(luaL_checknumber(L, idx + 1));
			v.z = static_cast<float>(luaL_checknumber(L, idx + 2));
		}
		else
		{
			return std::nullopt;
		}

		return v;
	}

	inline Matrix* RequireMatrix(lua_State* L, int idx)
	{
		return reinterpret_cast<Matrix*>(luaL_checkudata(L, idx, "Matrix"));
	}

	inline std::optional<Matrix*> CheckMatrix(lua_State* L, int idx)
	{
		if (Matrix* h = reinterpret_cast<Matrix*>(luaL_testudata(L, idx, "Matrix")))
		{
			return h;
		}
		else
		{
			return std::nullopt;
		}
	}

}
