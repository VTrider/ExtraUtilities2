/*
* Memory Scanner class with automatic
* protection and restoration of the original
* data
*/

#pragma once

#include "BasicScanner.h"

#include <Windows.h>

#include <vector>

#undef ABSOLUTE // win32 name collision

namespace exu2
{
	template <class T>
	class Scanner : public BasicScanner
	{
	private:
		// This needs to be initialized first so that the address of the
		// desired value can be resolved properly
		BaseAddress m_baseAddress; // what base address to use when accessing memory

		T* m_address;
		Restore m_restoreData; // should you restore the data after leaving game? usually yes but sometimes no for things like game settings
		T m_originalData;

		DWORD m_oldProtect{}; // Original memory protection value
		static inline DWORD m_dummyProtect; // dummy variable for VirtualProtect

		// Finds the true address from addresses that require an offset from a module
		T* ResolveBase(T* offset)
		{
			uintptr_t rawOffset = reinterpret_cast<uintptr_t>(offset);
			using enum BaseAddress;
			switch (m_baseAddress)
			{
			case ABSOLUTE:
				return offset;
			case BZCC:
				return reinterpret_cast<T*>(m_bzccModuleBase + rawOffset);
			case STEAMAPI:
				return reinterpret_cast<T*>(m_steamApiModuleBase + rawOffset);
			default:
				return nullptr;
			}
		}

	public:
		Scanner(T* address, Restore restoreData = Restore::ENABLED, 
			BaseAddress baseAddress = BaseAddress::ABSOLUTE)
			: m_address(ResolveBase(address)), m_restoreData(restoreData), m_baseAddress(baseAddress)
		{
			VirtualProtect(m_address, sizeof(T), PAGE_EXECUTE_READWRITE, &m_oldProtect);
			m_originalData = Read();
		}

		// Traverse multi-level pointer
		Scanner(T* address, const std::initializer_list<uint8_t>& offsetsList, Restore restoreData = Restore::ENABLED, 
			BaseAddress baseAddress = BaseAddress::ABSOLUTE)
			: m_address(ResolveBase(address)), m_restoreData(restoreData), m_baseAddress(baseAddress)
		{
			VirtualProtect(m_address, sizeof(T), PAGE_EXECUTE_READWRITE, &m_oldProtect);
			uintptr_t resolvedAddress = reinterpret_cast<uintptr_t>(m_address);
			std::vector offsets = offsetsList;
			for (size_t i = 0; i < offsets.size(); i++)
			{
				resolvedAddress = *reinterpret_cast<uintptr_t*>(resolvedAddress);
				resolvedAddress += offsets[i];
			}
			m_address = reinterpret_cast<T*>(resolvedAddress);
			m_originalData = Read();
		}

		Scanner(Scanner& o) = delete;
		Scanner(Scanner&& o) noexcept
			: BasicScanner(std::move(o))
		{
			this->m_baseAddress = o.m_baseAddress;
			this->m_address = o.m_address;
			this->m_restoreData = o.m_restoreData;
			this->m_originalData = o.m_originalData;
			this->m_oldProtect = o.m_oldProtect;
		}

		~Scanner()
		{
			if (m_restoreData == Restore::ENABLED)
			{
				Write(m_originalData);
			}
			VirtualProtect(m_address, sizeof(T), m_oldProtect, &m_dummyProtect);
		}

		T Read() const noexcept
		{
			if (m_address == nullptr)
			{
				return{};
			}

			return *m_address;
		}

		void Write(T value) noexcept
		{
			if (m_address == nullptr)
			{
				return;
			}

			*m_address = value;
		}

		// Get the underlying pointer of the data for direct access
		T* Get() const noexcept
		{
			if (m_address == nullptr)
			{
				return nullptr;
			}

			return m_address;
		}
	};
}