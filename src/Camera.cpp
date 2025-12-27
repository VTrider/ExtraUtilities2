#include "BZCC.h"
#include "ExtraUtils.h"
#include "MathUtils.h"

#include <ScriptUtils.h>
#include <format>
namespace exu2
{
	EXUAPI Matrix DLLAPI GetPerspectiveMatrix()
	{
		return BZCC::Camera::mainCamera->perspective;
	}

	EXUAPI Matrix DLLAPI GetViewMatrix()
	{
		return BZCC::Camera::mainCamera->view;
	}

	EXUAPI bool DLLAPI WorldToScreen(const Vector& worldPosition, Vector* outScreen)
	{
		using namespace BZCC;

		// Row major: not divine
		Vector4 clipSpace =  Vector_Transform(Matrix_Multiply(Camera::mainCamera->view, Camera::mainCamera->perspective), Vector4(worldPosition));

		if (clipSpace.w < 0)
			return false;

		Vector ndc = (clipSpace / clipSpace.w).xyz();

		if (ndc.x < -1.0f or ndc.x > 1.0f or
			ndc.y < -1.0f or ndc.y > 1.0f or
			ndc.z < 0.0f or ndc.z > 1.0f)
		{
			return false;
		}

		if (outScreen)
		{
			outScreen->x = ndc.x * 0.5f + 0.5f;
			outScreen->y = 1.0f - (ndc.y * 0.5f + 0.5f);
			outScreen->z = ndc.z;

			return true;
		}
		else
		{
			return false;
		}
	}
}
