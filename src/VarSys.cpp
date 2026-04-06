#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{	
	using namespace BZCC::VarSys;
	void DLLAPI VarSys_CreateCmd(ConstName name)
	{
		CreateCmd(name);
		VarSys_SetVarFlag(name, VarFlag::NODELETE, false);

		// VarItem* item = BZCC::VarSys::FindVarItem(name);

		// clear NODELETE on custom cmds which is enabled by default
		// and I have no idea how the game does it so we just do it manually
		//if (item)
		//	item->flags &= ~std::to_underlying(VarItem::Flag::NODELETE);
	}

	bool DLLAPI IFace_DeleteItem(ConstName name)
	{
		return DeleteItem(name);
	}

	void DLLAPI VarSys_RegisterHandler(ConstName name, VarSysHandler handler, unsigned long magic)
	{
		RegisterHandler(name, handler, magic);
	}

	VarSysHandler customHandler = nullptr;
	VarSysHandler stockHandler = (*p_gScope)->handler;

	void GlobalHandlerHook(unsigned long crc)
	{
		if (customHandler)
		{
			customHandler(crc);
		}
		stockHandler(crc);
	}

	EXUAPI void DLLAPI VarSys_InstallGlobalHandler(VarSysHandler handler)
	{
		customHandler = handler;
		(*p_gScope)->handler = GlobalHandlerHook;
	}

	EXUAPI void DLLAPI VarSys_UninstallGlobalHandler()
	{
		(*p_gScope)->handler = stockHandler;
	}

	EXUAPI bool DLLAPI VarSys_GetVarFlag(ConstName name, VarFlag flag, bool& flagStatus)
	{
		const VarItem* item = FindVarItem(name);
		if (!item)
			return false;

		flagStatus = (item->flags & (std::to_underlying(flag))) != 0;

		return true;
	}

	EXUAPI bool DLLAPI VarSys_SetVarFlag(ConstName name, VarFlag flag, bool status)
	{
		VarItem* item = FindVarItem(name);
		if (!item)
			return false;

		item->flags &= ~(std::to_underlying(flag));
		if (status)
			item->flags |= std::to_underlying(flag);

		return true;
	}
}