#pragma once

#include <cstdint>

namespace Offsets::V205_3
{
    constexpr uintptr_t ArgCount = 0x363183;
    constexpr uintptr_t GetArgFloat = 0x3631DB;
    constexpr uintptr_t GetArgInteger = 0x363451;
    constexpr uintptr_t GetArgString = 0x363420;
    constexpr uintptr_t DeleteItem = 0x35E6BB;
    constexpr uintptr_t CreateCmd = 0x35E6DD;
    constexpr uintptr_t RegisterHandler = 0x35E61C;
    constexpr uintptr_t inSatellite = 0x2869AC + 2;
    constexpr uintptr_t netPlayerInfoArray = 0x1D3E5C;
    constexpr uintptr_t activeConfigMod = 0x107C53;
    constexpr uintptr_t misnExport = 0xA5B28;
    constexpr uintptr_t globalHandler = 0x35DF21;
    constexpr uintptr_t GameObjectClass_Find = 0x170212;
    constexpr uintptr_t SchedPlan_GoodSpot = 0x2B402E;
} // namespace Offsets
