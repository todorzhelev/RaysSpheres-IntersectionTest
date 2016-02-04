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


}

////////////////////////////////////////////////////////////////////////////////////////////

bool Sphere::GetIntersection(Ray& ray, IntersectionInfo& info)
{
	Vector3D m = ray.m_startPos - m_center;
	float b = DotProduct(m, ray.m_direction);
	float c = DotProduct(m, m) - m_radius * m_radius;

	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b*b - c;

	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.0f)
	{
		return false;
	}

	// Ray now found to intersect sphere, compute smallest t value of intersection
	float t = -b - sqrt(discr);

	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.0f) t = 0.0f;
	info.m_intersPoint = ray.m_startPos + t * ray.m_direction;
	info.m_t = t;
	info.m_object = this;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////