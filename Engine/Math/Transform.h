#pragma once
#include "Vector2.h"
#include "Matrix3x3.h"
#include "MathUtils.h"

namespace neu
{
	struct Transform
	{
		Vector2 position;
		float rotation;
		Vector2 scale{ 1, 1 };

		operator Matrix3x3 () const
		{
			Matrix3x3 mxScale = Matrix3x3::CreateScale(scale);
			Matrix3x3 mxRotation = Matrix3x3::CreateRotation(math::DegToRad(rotation));
			Matrix3x3 mxTranslation = Matrix3x3::CreateTranslation(position);

			return { mxScale * mxRotation * mxTranslation };
		}
	};
}
