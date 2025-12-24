#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{	
	void DLLAPI VarSys_CreateCmd(ConstName name)
	{
		BZCC::VarSys::CreateCmd(name);
	}

	bool DLLAPI IFace_DeleteItem(ConstName name)
	{
		return BZCC::VarSys::DeleteItem(name);
	}

	void DLLAPI VarSys_RegisterHandler(ConstName name, VarSysHandler handler, unsigned long magic)
	{
		BZCC::VarSys::RegisterHandler(name, handler, magic);
	}
}