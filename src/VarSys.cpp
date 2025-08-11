#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{
	bool DLLAPI IFace_DeleteItem(ConstName name)
	{
		return BZCC::VarSys::DeleteItem(name);
	}
}