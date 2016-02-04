#pragma once
#include "Vector3D.h"

class Ray
{
public:

	Ray(Vector3D startPos, Vector3D direction);

	Vector3D m_startPos;
	Vector3D m_direction;
};