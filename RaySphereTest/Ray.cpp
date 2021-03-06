#include "Ray.h"

////////////////////////////////////////////////////////////////////////////////////////////

Ray::Ray()
{
	m_startPos  = Vector3D(0, 0, 0, 0);
	m_direction = Vector3D(0, 0, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////

Ray::Ray(const Vector3D& startPos, const Vector3D& direction):
m_startPos(startPos), m_direction(direction)
{
	m_direction.Normalize();
}

////////////////////////////////////////////////////////////////////////////////////////////