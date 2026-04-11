#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{	
	using namespace BZCC::VarSys;
	void DLLAPI VarSys_CreateCmd(ConstName name)
	{
		CreateCmd(name);
		VarSys_SetVarFlag(name, VarFlag::NODELETE, false);
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

	void DLLAPI VarSys_InstallGlobalHandler(VarSysHandler handler)
	{
		customHandler = handler;
		(*p_gScope)->handler = GlobalHandlerHook;
	}

	void DLLAPI VarSys_UninstallGlobalHandler()
	{
		(*p_gScope)->handler = stockHandler;
	}

	bool DLLAPI VarSys_GetVarFlag(ConstName name, VarFlag flag, bool& flagStatus)
	{
		const VarItem* item = FindVarItem(name);
		if (!item)
			return false;

		flagStatus = (item->flags & (std::to_underlying(flag))) != 0;

		return true;
	}

	bool DLLAPI VarSys_SetVarFlag(ConstName name, VarFlag flag, bool status)
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