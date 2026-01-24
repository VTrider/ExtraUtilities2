#pragma once

#include <cstdint>

namespace Offsets
{
    constexpr uintptr_t ArgCount = 0x350D80;
    constexpr uintptr_t GetArgFloat = 0x350DD8;
    constexpr uintptr_t GetArgInteger = 0x351049;
    constexpr uintptr_t GetArgString = 0x351018;
    constexpr uintptr_t DeleteItem = 0x34C3D7;
    constexpr uintptr_t CreateCmd = 0x34C3F7;
    constexpr uintptr_t RegisterHandler = 0x34C337;
    constexpr uintptr_t inSatellite = 0x277848;
    constexpr uintptr_t netPlayerInfoArray = 0x1C705C;
} // namespace Offsets