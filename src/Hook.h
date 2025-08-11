#pragma once

#include "BasicPatch.h"

#include <Windows.h>
#include <array>

namespace exu2
{
	class Hook : public BasicPatch
	{
	private:
		const void* m_function;
		const void** p_function = &m_function; // pointer to the function for memcpy

		// x86 shellcode
		static constexpr uint8_t CALL[] = { 0xFF, 0x15 }; // call near absolute indirect

		bool ValidateHook() const
		{
			if (m_length < 6)
			{
				std::terminate();
			}
			return true;
		}

		void DoPatch() override
		{
			uint8_t* p_address = reinterpret_cast<uint8_t*>(m_address);

			VirtualProtect(p_address, m_length, PAGE_EXECUTE_READWRITE, &m_oldProtect);

			std::memset(p_address, NOP, m_length);
			std::memcpy(p_address, CALL, 2);

			// +2 bytes because the first two are the jmp instruction, next 4 is the address.
			// importantly the call instruction needs a static pointer to the function, 
			// not one in stack memory, that's why the pointer is a class member
			std::memcpy(p_address + 2, &p_function, sizeof(uintptr_t)); 

			VirtualProtect(p_address, m_length, m_oldProtect, &dummyProtect);

			m_status = Status::ACTIVE;
		}

	public:
		Hook(uintptr_t address, const void* function, size_t length, Status status)
			: BasicPatch(address, length, status), m_function(function)
		{
			if (!ValidateHook())
			{
				return;
			}

			if (m_status == Status::ACTIVE)
			{
				DoPatch();
			}
		}

		Hook(Hook& h) = delete;

		Hook(Hook&& h) noexcept
			: BasicPatch(std::move(h))
		{
			this->m_function = h.m_function;
			this->p_function = h.p_function;
		}

		~Hook() = default;
	};
}
