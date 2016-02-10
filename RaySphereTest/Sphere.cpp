#include "Sphere.h"

////////////////////////////////////////////////////////////////////////////////////////////

Sphere::Sphere()
{
	m_center = Vector3D(0, 0, 0);
	m_radius = 0;

}

////////////////////////////////////////////////////////////////////////////////////////////

Sphere::Sphere(const Vector3D& center, float radius):
m_center(center), m_radius(radius)
{

}

////////////////////////////////////////////////////////////////////////////////////////////

void Sphere::Expand(Sphere& sphere)
{
	Vector3D centerVec	= sphere.m_center - m_center;
	float radiusDiff	= sphere.m_radius - m_radius;
	float distanceSqr	= centerVec.LengthSqr();

	//if one of the spheres is inside the other
	if(radiusDiff*radiusDiff >= distanceSqr)
	{
		//if the current sphere is inside the other, we have to expand it
		if( radiusDiff >= 0.0f )
		{
			m_center = sphere.m_center;
			m_radius = sphere.m_radius;
		}
	}
	else
	{
		float distance = sqrt(distanceSqr);
		float t = (distance + sphere.m_radius - m_radius) / (2 * distance);
		Vector3D newCenter = m_center + t*centerVec;
		float newRadius = (distance + sphere.m_radius + m_radius) / 2;

		m_center = newCenter;
		m_radius = newRadius;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

bool Sphere::GetIntersection(Ray* ray, IntersectionInfo& info)
{
	Vector3D m = ray->m_startPos - m_center;
	float b = DotProduct(m, ray->m_direction);
	float c = DotProduct(m, m) - m_radius * m_radius;

	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b*b - c;

	if (discr < 0.0f)
	{
		return false;
	}

	float t = -b - sqrt(discr);

	if (t < 0.0f) t = 0.0f;
	info.m_intersPoint = ray->m_startPos + t * ray->m_direction;
	info.m_object = this;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////