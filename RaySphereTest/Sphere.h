#pragma once
#include "Vector3D.h"

class Sphere
{
public:

	Sphere(Vector3D centerPosition, float radius);

	float m_radius;
	Vector3D m_centerPosition;
};