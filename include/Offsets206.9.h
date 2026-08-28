#pragma once

#include <cstdint>

namespace Offsets::V206_9
{
    constexpr uintptr_t ArgCount = 0x366A63;
    constexpr uintptr_t GetArgFloat = 0x366AB9;
    constexpr uintptr_t GetArgInteger = 0x366D31;
    constexpr uintptr_t GetArgString = 0x366D00;
    constexpr uintptr_t DeleteItem = 0x361F9A;
    constexpr uintptr_t CreateCmd = 0x361FBC;
    constexpr uintptr_t RegisterHandler = 0x361EFB;
    constexpr uintptr_t inSatellite = 0x28A0A9;
    constexpr uintptr_t netPlayerInfoArray = 0x1D64B3;
    constexpr uintptr_t activeConfigMod = 0x1094E3;
    constexpr uintptr_t misnExport = 0xA5CFA;
    constexpr uintptr_t globalHandler = 0x361800;
    constexpr uintptr_t GameObjectClass_Find = 0x171FB7;
    constexpr uintptr_t SchedPlan_GoodSpot = 0x2B77D6;
    constexpr uintptr_t Armory_StartBuild = 0x13DF9B;
    constexpr uintptr_t Constructor_QueueBuild = 0xBE8A0;
    constexpr uintptr_t Factory_QueueBuild = 0x1621A5;
    constexpr uintptr_t Armory_CancelBuild = 0x13E114;
    constexpr uintptr_t Constructor_CancelBuild = 0xC3E4E;
    constexpr uintptr_t Factory_CancelBuild = 0x16252C;
} // namespace Offsets