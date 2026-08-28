#pragma once

#include <cstdint>

namespace Offsets::V205_3
{
    constexpr uintptr_t ArgCount = 0x363183;
    constexpr uintptr_t GetArgFloat = 0x3631D9;
    constexpr uintptr_t GetArgInteger = 0x363451;
    constexpr uintptr_t GetArgString = 0x363420;
    constexpr uintptr_t DeleteItem = 0x35E6BB;
    constexpr uintptr_t CreateCmd = 0x35E6DD;
    constexpr uintptr_t RegisterHandler = 0x35E61C;
    constexpr uintptr_t inSatellite = 0x286989;
    constexpr uintptr_t netPlayerInfoArray = 0x1D3E56;
    constexpr uintptr_t activeConfigMod = 0x107C53;
    constexpr uintptr_t misnExport = 0xA5B28;
    constexpr uintptr_t globalHandler = 0x35DF21;
    constexpr uintptr_t GameObjectClass_Find = 0x170212;
    constexpr uintptr_t SchedPlan_GoodSpot = 0x2B402E;
    constexpr uintptr_t Armory_StartBuild = 0x13C55C;
    constexpr uintptr_t Constructor_QueueBuild = 0xBE6B8;
    constexpr uintptr_t Factory_QueueBuild = 0x16073C;
    constexpr uintptr_t Armory_CancelBuild = 0x13C6D5;
    constexpr uintptr_t Constructor_CancelBuild = 0xBE545;
    constexpr uintptr_t Factory_CancelBuild = 0x160AC3;
} // namespace Offsets