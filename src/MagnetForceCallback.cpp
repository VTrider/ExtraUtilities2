#include "BZCC.h"
#include "ExtraUtils.h"

#include <safetyhook.hpp>

namespace exu2
{
	using namespace BZCC;

	MagnetForceCallback_t magnetForceCallback = nullptr;

	// Notes: Each magnet function has two passes, the first is for objects, and the second is for ordnance,
	// so each one requires two hooks.
	SafetyHookMid magnetGunObjHook;
	SafetyHookMid magnetGunOrdHook;

	// Notes: MagnetGun* (this) in esi, GameObject* (target) in edx
	void MagnetGunObjHook(SafetyHookContext& ctx)
	{
		Weapon* weapon = reinterpret_cast<Weapon*>(ctx.esi);
		GameObject* targetObj = reinterpret_cast<GameObject*>(ctx.edx);

		MagnetForceInfo info{};
		info.magnetHandle = 0;
		info.magnetOwner = weapon->owner->handle;
		info.magnetTeam = GetTeamNum(info.magnetOwner);
		info.magnetOdf = weapon->wpnClass->odf;

		info.targetType = MagnetTarget::GAME_OBJECT;
		info.targetHandle = targetObj->handle;
		info.targetTeam = GetTeamNum(info.targetHandle);
		char odf[64];
		if (GetObjInfo(info.targetHandle, Get_ODF, odf))
			info.targetOdf = odf;

		if (magnetForceCallback)
			magnetForceCallback(MagnetType::GUN, &info);
	}

	// TODO:
	// Notes: MagnetGun* (this) in esi, Ordnance* (target) in edx
	void MagnetGunOrdHook(SafetyHookContext& ctx)
	{
		Weapon* weapon = reinterpret_cast<Weapon*>(ctx.esi);
		uintptr_t targetOrd = ctx.edx;

		MagnetForceInfo info{};
		info.magnetHandle = 0;
		info.magnetOwner = weapon->owner->handle;
		info.magnetTeam = GetTeamNum(info.magnetOwner);
		info.magnetOdf = weapon->wpnClass->odf;

		info.targetType = MagnetTarget::ORDNANCE;
		info.targetOrdnance = targetOrd;
		info.targetTeam = GetTeamNum(info.targetHandle);
		char odf[64];
		if (GetObjInfo(info.targetHandle, Get_ODF, odf))
			info.targetOdf = odf;

		if (magnetForceCallback)
			magnetForceCallback(MagnetType::GUN, &info);
	}


	void DLLAPI SetMagnetForceCallback(MagnetForceCallback_t callback)
	{
		magnetForceCallback = callback;

		if (!magnetGunObjHook.target())
			magnetGunObjHook = safetyhook::create_mid(BZCC::moduleBase + 0x22000A, MagnetGunObjHook);

		if (!magnetGunOrdHook.target())
			magnetGunOrdHook = safetyhook::create_mid(BZCC::moduleBase + 0x2203F1, MagnetGunOrdHook);
	}
}