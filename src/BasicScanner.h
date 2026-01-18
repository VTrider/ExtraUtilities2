// Non-template properties and helpers for the scanner class

#pragma once

#include <cstdint>

#include <Windows.h>

#undef ABSOLUTE

namespace exu2
{
	class BasicScanner
	{
	protected:
		static inline uintptr_t m_bzccModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(L"battlezone2.exe"));
		static inline uintptr_t m_steamApiModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(L"steam_api.dll"));

		BasicScanner() = default;
		virtual ~BasicScanner() = default;

	public:
		// Should the scanner restore the original data when the dll exits?
		enum class Restore : uint8_t
		{
			ENABLED,
			DISABLED
		};

		// What base address to use when calculating memory addresses
		enum class BaseAddress : uint8_t
		{
			ABSOLUTE, // use absolute address, not really applicable in BZCC
			BZCC, // use BZCC module base, always necessary due to ASLR
			STEAMAPI // use steam_api as module base
		};

		// Calculates an address from module offset for use in a hook as opposed to accessing data
		static uintptr_t CalculateAddress(uintptr_t offset, BaseAddress baseAddress)
		{
			using enum BaseAddress;
			switch (baseAddress)
			{
			case ABSOLUTE:
				return offset;
			case BZCC:
				return m_bzccModuleBase + offset;
			case STEAMAPI:
				return m_steamApiModuleBase + offset;
			default:
				return 0;
			}
		}
	};
}
