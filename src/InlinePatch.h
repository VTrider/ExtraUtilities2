#pragma once

#include "BasicPatch.h"

#include <vector>

namespace exu2
{
	class InlinePatch : public BasicPatch
	{
	private:
		std::vector<uint8_t> m_payload;

		void DoPatch() override
		{
			uint8_t* p_address = reinterpret_cast<uint8_t*>(m_address);

			VirtualProtect(p_address, m_length, PAGE_EXECUTE_READWRITE, &m_oldProtect);

			std::memcpy(p_address, m_payload.data(), m_length);

			VirtualProtect(p_address, m_length, m_oldProtect, &dummyProtect);

			m_status = Status::ACTIVE;
		}

	public:
		// Inline patch from buffer
		InlinePatch(uintptr_t address, const void* payload, size_t length, Status status)
			: BasicPatch(address, length, status), m_payload((uint8_t*)payload, (uint8_t*)payload + length)
		{
			if (m_status == Status::ACTIVE)
			{
				DoPatch();
			}
		}

		// Shellcode inline patch
		InlinePatch(uintptr_t address, std::vector<uint8_t> payload, Status status)
			: BasicPatch(address, payload.size(), status), m_payload(payload)
		{
			if (m_status == Status::ACTIVE)
			{
				DoPatch();
			}
		}

		// Single byte inline patch
		InlinePatch(uintptr_t address, uint8_t value, size_t length, Status status)
			: BasicPatch(address, length, status), m_payload(length, value)
		{
			if (m_status == Status::ACTIVE)
			{
				DoPatch();
			}
		}

		// Multi byte/pointer inline patch
		template <typename T>
		InlinePatch(uintptr_t address, T value, Status status)
			: BasicPatch(address, sizeof(T), status), m_payload((uint8_t*)&value, (uint8_t*)&value + sizeof(T))
		{
			if (m_status == Status::ACTIVE)
			{
				DoPatch();
			}
		}

		InlinePatch(InlinePatch& p) = delete;

		InlinePatch(InlinePatch&& p) noexcept
			: BasicPatch(std::move(p))
		{
			this->m_payload = std::move(p.m_payload);
		}

		~InlinePatch() = default;
	};
}