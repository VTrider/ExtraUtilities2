#include "ExtraUtils.h"

#include <Windows.h>

#include <tuple>

namespace exu2
{
	EXUAPI std::pair<size_t, size_t> GetViewportSize()
	{
		HWND hwnd = FindWindow("BZCC Main Window", nullptr); // That's the name of the window class
		RECT rc;
		GetClientRect(hwnd, &rc);
		return std::make_pair(rc.right - rc.left, rc.bottom - rc.top);
	}
}