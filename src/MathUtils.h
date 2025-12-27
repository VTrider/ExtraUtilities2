#pragma once

#include <ScriptUtils.h>

// Stuff from 1.3 C++ Missions

namespace exu2
{
	struct Vector4
	{
		float x, y, z, w;

		constexpr Vector4() : x(0.0), y(0.0), z(0.0f), w(0.0f) {}
		constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		constexpr Vector4(const Vector& v) : x(v.x), y(v.y), z(v.z), w(1.0f) {}

		Vector xyz() const { return Vector(x, y, z); }

		friend constexpr Vector4 operator*(const Vector4& v, float s)
		{
			return Vector4(v.x * s, v.y * s, v.z * s, v.w * s);
		}

		friend constexpr Vector4 operator/(const Vector4& v, float s)
		{
			return v * (1 / s);
		}
	};

	constexpr Vector Vector_Transform (const Matrix &M, const Vector &v)
	{
		Vector out{};

		out.x = M.right.x * v.x + M.up.x * v.y + M.front.x * v.z + M.posit.x;
		out.y = M.right.y * v.x + M.up.y * v.y + M.front.y * v.z + M.posit.y;
		out.z = M.right.z * v.x + M.up.z * v.y + M.front.z * v.z + M.posit.z;

		return out;
	}

	constexpr Vector4 Vector_Transform (const Matrix &M, const Vector4 &v)
	{
		Vector4 out{};
		
		out.x = M.right.x * v.x + M.up.x * v.y + M.front.x * v.z + M.posit.x * v.w;
		out.y = M.right.y * v.x + M.up.y * v.y + M.front.y * v.z + M.posit.y * v.w;
		out.z = M.right.z * v.x + M.up.z * v.y + M.front.z * v.z + M.posit.z * v.w;
		out.w = M.rightw * v.x + M.upw * v.y + M.frontw * v.z + M.positw * v.w;

		return out;
	}

	constexpr Matrix Matrix_Multiply(const Matrix& A, const Matrix& B)
	{
		Matrix M{};

		M.right.x = A.right.x * B.right.x + A.right.y * B.up.x + A.right.z * B.front.x + A.rightw * B.posit.x;
		M.right.y = A.right.x * B.right.y + A.right.y * B.up.y + A.right.z * B.front.y + A.rightw * B.posit.y;
		M.right.z = A.right.x * B.right.z + A.right.y * B.up.z + A.right.z * B.front.z + A.rightw * B.posit.z;
		M.rightw  = A.right.x * B.rightw  + A.right.y * B.upw  + A.right.z * B.frontw  + A.rightw * B.positw;

		M.up.x    = A.up.x    * B.right.x + A.up.y    * B.up.x + A.up.z    * B.front.x + A.upw * B.posit.x;
		M.up.y    = A.up.x    * B.right.y + A.up.y    * B.up.y + A.up.z    * B.front.y + A.upw * B.posit.y;
		M.up.z    = A.up.x    * B.right.z + A.up.y    * B.up.z + A.up.z    * B.front.z + A.upw * B.posit.z;
		M.upw     = A.up.x    * B.rightw  + A.up.y    * B.upw  + A.up.z    * B.frontw  + A.upw * B.positw;

		M.front.x = A.front.x * B.right.x + A.front.y * B.up.x + A.front.z * B.front.x + A.frontw * B.posit.x;
		M.front.y = A.front.x * B.right.y + A.front.y * B.up.y + A.front.z * B.front.y + A.frontw * B.posit.y;
		M.front.z = A.front.x * B.right.z + A.front.y * B.up.z + A.front.z * B.front.z + A.frontw * B.posit.z;
		M.frontw  = A.front.x * B.rightw  + A.front.y * B.upw  + A.front.z * B.frontw  + A.frontw * B.positw;

		M.posit.x = A.posit.x * B.right.x + A.posit.y * B.up.x + A.posit.z * B.front.x + A.positw * B.posit.x;
		M.posit.y = A.posit.x * B.right.y + A.posit.y * B.up.y + A.posit.z * B.front.y + A.positw * B.posit.y;
		M.posit.z = A.posit.x * B.right.z + A.posit.y * B.up.z + A.posit.z * B.front.z + A.positw * B.posit.z;
		M.positw  = A.posit.x * B.rightw  + A.posit.y * B.upw  + A.posit.z * B.frontw  + A.positw * B.positw;

		return M;
	}
}
