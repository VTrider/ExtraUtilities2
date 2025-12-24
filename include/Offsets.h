#pragma once

#include <cstdint>

namespace Offsets
{
    constexpr uintptr_t ArgCount = 0x34FA60;
    constexpr uintptr_t GetArgFloat = 0x34FAB8;
    constexpr uintptr_t GetArgInteger = 0x34FD29;
    constexpr uintptr_t GetArgString = 0x34FCF8;
    constexpr uintptr_t DeleteItem = 0x34B0AD;
    constexpr uintptr_t CreateCmd = 0x34B0CD;
    constexpr uintptr_t RegisterHandler = 0x34B00D;
} // namespace Offsets