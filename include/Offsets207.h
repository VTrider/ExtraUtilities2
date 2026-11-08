#pragma once

#include <cstdint>

namespace Offsets::V207
{
    constexpr uintptr_t ArgCount = 0x37477B;
    constexpr uintptr_t GetArgFloat = 0x374731;
    constexpr uintptr_t GetArgInteger = 0x374A01;
    constexpr uintptr_t GetArgString = 0x3749D0;
    constexpr uintptr_t DeleteItem = 0x36FC15;
    constexpr uintptr_t CreateCmd = 0x36FC37;
    constexpr uintptr_t RegisterHandler = 0x36FB76;
    constexpr uintptr_t inSatellite = 0x295327;
    constexpr uintptr_t netPlayerInfoArray = 0x1DD2B9;
    constexpr uintptr_t activeConfigMod = 0x10C402;
    constexpr uintptr_t misnExport = 0xA7288;
    constexpr uintptr_t globalHandler = 0x36F486;
    constexpr uintptr_t GameObjectClass_Find = 0x177232;
    constexpr uintptr_t SchedPlan_GoodSpot = 0x2C39FA;
    constexpr uintptr_t Armory_StartBuild = 0x1423EF;
    constexpr uintptr_t Constructor_QueueBuild = 0xBFF5B;
    constexpr uintptr_t Factory_QueueBuild = 0x1670EE;
    constexpr uintptr_t Armory_CancelBuild = 0x142568;
    constexpr uintptr_t Constructor_CancelBuild = 0xBFDE8;
    constexpr uintptr_t Factory_CancelBuild = 0x167475;
    constexpr uintptr_t Armory_FinishBuild = 0x141A7B;
    constexpr uintptr_t Constructor_FinishBuild = 0x1516E9;
    constexpr uintptr_t Factory_FinishBuild = 0x166046;
} // namespace Offsets