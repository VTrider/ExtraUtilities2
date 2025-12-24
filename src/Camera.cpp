#include "BZCC.h"
#include "ExtraUtils.h"

#include <ScriptUtils.h>

namespace exu2
{
	EXUAPI Matrix DLLAPI GetPerspectiveMatrix()
	{
		return BZCC::Camera::mainCamera->perspective;
	}

	EXUAPI Vector DLLAPI WorldToScreen(const Vector& worldPosition)
	{
		using namespace BZCC;

		// TODO: operators
		// Camera::mainCamera->perspective * Camera::mainCamera->view * worldPosition;
		return {};
	}

	EXUAPI Matrix DLLAPI GetViewMatrix()
	{
		return BZCC::Camera::mainCamera->view;
	}
}
