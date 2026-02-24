#include "ExtraUtils.h"

#include <Windows.h>

namespace exu2
{
	constexpr const char* version = "1.2.0";

	EXUAPI int DLLAPI GetGameMinorVersion()
	{
		DWORD handle;
		auto filename = GetBZCCPath().append("battlezone2.exe");
		if (DWORD size = GetFileVersionInfoSizeW(filename.c_str(), &handle))
		{
			auto versionData = std::make_unique<BYTE[]>(size);
			if (GetFileVersionInfoW(filename.c_str(), handle, size, versionData.get()))
			{
				UINT infoSize = 0;
				VS_FIXEDFILEINFO* fixedInfo = nullptr;
				VerQueryValueW(versionData.get(), L"\\", reinterpret_cast<LPVOID*>(&fixedInfo), &infoSize);
				return HIWORD(fixedInfo->dwFileVersionLS);
			}
		}
		else
		{
			std::terminate();
		}
		return {};
	}

	EXUAPI const char* DLLAPI GetDLLVersion()
	{
		return version;
	}
}