#pragma once

#include <cstdint>

namespace Offsets::V208
{
    constexpr uintptr_t ArgCount = 0x3773DB;
    constexpr uintptr_t GetArgFloat = 0x377391;
    constexpr uintptr_t GetArgInteger = 0x377661;
    constexpr uintptr_t GetArgString = 0x377630;
    constexpr uintptr_t DeleteItem = 0x3727CD;
    constexpr uintptr_t CreateCmd = 0x3727EF;
    constexpr uintptr_t RegisterHandler = 0x37272E;
    constexpr uintptr_t inSatellite = 0x297D07;
    constexpr uintptr_t netPlayerInfoArray = 0x1DF546;
    constexpr uintptr_t activeConfigMod = 0x10DA1C;
    constexpr uintptr_t misnExport = 0xA7D69;
    constexpr uintptr_t globalHandler = 0x371FD6;
    constexpr uintptr_t GameObjectClass_Find = 0x178E79;
    constexpr uintptr_t SchedPlan_GoodSpot = 0x2C648C;
    constexpr uintptr_t Armory_StartBuild = 0x143BFC;
    constexpr uintptr_t Constructor_QueueBuild = 0xC0A3F;
    constexpr uintptr_t Factory_QueueBuild = 0x168D32;
    constexpr uintptr_t Armory_CancelBuild = 0x143D76;
    constexpr uintptr_t Constructor_CancelBuild = 0xC08CC;
    constexpr uintptr_t Factory_CancelBuild = 0x1690BA;
    constexpr uintptr_t Armory_FinishBuild = 0x14306C;
    constexpr uintptr_t Constructor_FinishBuild = 0x152F85;
    constexpr uintptr_t Factory_FinishBuild = 0x167C86;
} // namespace Offsets
