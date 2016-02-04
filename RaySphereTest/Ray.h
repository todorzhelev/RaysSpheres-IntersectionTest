#pragma once
#include "Vector3D.h"

struct Ray
{
	Ray();

	Ray(const Vector3D& startPos, const Vector3D& direction);

	Vector3D m_startPos;
	Vector3D m_direction;
};