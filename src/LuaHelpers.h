#pragma once

#include <lua.hpp>
#include <ScriptUtils.h>

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

	// Get either a vector or three numbers from lua
	inline Vector CheckVectorOrSingles(lua_State* L, int idx)
	{
		Vector v;
		if (lua_isuserdata(L, idx))
		{
			lua_getfield(L, idx, "x");
			v.x = static_cast<float>(luaL_checknumber(L, -1));

			lua_getfield(L, idx, "y");
			v.y = static_cast<float>(luaL_checknumber(L, -1));

			lua_getfield(L, idx, "z");
			v.z = static_cast<float>(luaL_checknumber(L, -1));
		}
		else
		{
			v.x = static_cast<float>(luaL_checknumber(L, idx));
			v.y = static_cast<float>(luaL_checknumber(L, idx + 1));
			v.z = static_cast<float>(luaL_checknumber(L, idx + 2));
		}

		return v;
	}

	inline void PushVector(lua_State* L, const Vector& v)
	{
		lua_getglobal(L, "SetVector");

		lua_pushnumber(L, v.x);
		lua_pushnumber(L, v.y);
		lua_pushnumber(L, v.z);

		lua_call(L, 3, 1);
	}
}
