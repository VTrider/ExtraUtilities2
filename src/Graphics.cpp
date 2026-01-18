#include "ExtraUtils.h"

#include <Windows.h>

namespace exu2
{
	EXUAPI iVector2 GetViewportSize()
	{
		HWND hwnd = FindWindowW(L"BZCC Main Window", nullptr); // That's the name of the window class
		RECT rc;
		GetClientRect(hwnd, &rc);
		return iVector2(rc.right - rc.left, rc.bottom - rc.top);
	}
}