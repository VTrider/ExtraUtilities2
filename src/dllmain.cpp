// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>
#include <delayimp.h>

#include <BZCC.h>
#include <ExtraUtils.h>

#include <iostream>
#include <iomanip>

inline std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    os << std::fixed << std::setprecision(3);

    os << "[ " << std::setw(7) << m.right.x
       << " " << std::setw(7) << m.right.y
       << " " << std::setw(7) << m.right.z
       << " " << std::setw(7) << m.rightw << " ]\n";

    os << "[ " << std::setw(7) << m.up.x
       << " " << std::setw(7) << m.up.y
       << " " << std::setw(7) << m.up.z
       << " " << std::setw(7) << m.upw << " ]\n";

    os << "[ " << std::setw(7) << m.front.x
       << " " << std::setw(7) << m.front.y
       << " " << std::setw(7) << m.front.z
       << " " << std::setw(7) << m.frontw << " ]\n";

    os << "[ " << std::setw(7) << m.posit.x
       << " " << std::setw(7) << m.posit.y
       << " " << std::setw(7) << m.posit.z
       << " " << std::setw(7) << m.positw << " ]";

    return os;
}

#include <fstream>
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
        {
            std::ofstream test("feuker.txt");
            // test << BZCC::Camera::mainCamera << '\n';
            test << exu2::GetPerspectiveMatrix() << '\n';
            test << exu2::GetViewMatrix() << '\n';
        }
		break;
	case DLL_PROCESS_DETACH:
		if (GetModuleHandle("LuaMission.dll"))
		{
			__FUnloadDelayLoadedDLL2("LuaMission.dll");
		}
		break;
	}
    return TRUE;
}
