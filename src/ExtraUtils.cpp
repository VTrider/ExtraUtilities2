#include "ExtraUtils.h"

#include <Windows.h>

namespace exu2
{
	constexpr const char* version = "1.5.0";

	EXUAPI int DLLAPI GetGameMinorVersion()
	{
		auto filename = GetBZCCPath() / "battlezone2.exe";
		if (DWORD size = GetFileVersionInfoSizeW(filename.c_str(), 0))
		{
			auto versionData = std::make_unique<BYTE[]>(size);
			if (GetFileVersionInfoW(filename.c_str(), 0, size, versionData.get()))
			{
				UINT infoSize = 0;
				VS_FIXEDFILEINFO* fixedInfo = nullptr;
				VerQueryValueW(versionData.get(), L"\\", reinterpret_cast<LPVOID*>(&fixedInfo), &infoSize);
				return HIWORD(fixedInfo->dwFileVersionLS);
			}
		}
		std::terminate();
	}

	EXUAPI int DLLAPI GetGamePatchVersion()
	{
		auto filename = GetBZCCPath() / "battlezone2.exe";
		if (DWORD size = GetFileVersionInfoSizeW(filename.c_str(), 0))
		{
			auto versionData = std::make_unique<BYTE[]>(size);
			if (GetFileVersionInfoW(filename.c_str(), 0, size, versionData.get()))
			{
				UINT infoSize = 0;
				VS_FIXEDFILEINFO* fixedInfo = nullptr;
				VerQueryValueW(versionData.get(), L"\\", reinterpret_cast<LPVOID*>(&fixedInfo), &infoSize);
				return LOWORD(fixedInfo->dwFileVersionLS);
			}
		}
		std::terminate();
	}

	EXUAPI const char* DLLAPI GetDLLVersion()
	{
		return version;
	}
}