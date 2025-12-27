#pragma once

#include <cstdint>

namespace Offsets
{
    constexpr uintptr_t ArgCount = 0x3505F0;
    constexpr uintptr_t GetArgFloat = 0x350648;
    constexpr uintptr_t GetArgInteger = 0x3508B9;
    constexpr uintptr_t GetArgString = 0x350888;
    constexpr uintptr_t DeleteItem = 0x34BC44;
    constexpr uintptr_t CreateCmd = 0x34BC64;
    constexpr uintptr_t RegisterHandler = 0x34BBA4;
} // namespace Offsets