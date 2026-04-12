#include "BZCC.h"
#include "ExtraUtils.h"

namespace exu2
{
	TerrainQueryResult DLLAPI IsTerrainBuildable(int team, const char* odf, Vector& pos, const Vector& front)
	{
		using namespace BZCC;
		GameObjectClass* buildClass = GameObjectClass::Find(odf);
		if (!buildClass)
			return TerrainQueryResult::INVALID_ODF;

		bool result = SchedPlan::GoodSpot(team, buildClass, pos, front);

		return result ? TerrainQueryResult::BUILDABLE : TerrainQueryResult::NOT_BUILDABLE;
	}
}