#pragma once

#include <lua.hpp>
#include <ScriptUtils.h>

namespace exu2
{
	inline void PushMatrix(lua_State* L, const Matrix& m)
	{
		lua_getglobal(L, "SetMatrix");

		m.frontC
	}
}
