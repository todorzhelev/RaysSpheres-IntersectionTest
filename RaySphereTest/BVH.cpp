#include "BVH.h"

Sphere BVH::GetBoundingSphere(Sphere s0, Sphere s1)
{
	Sphere s(Vector3D(0,0,0),0);

	// Compute the squared distance between the sphere centers
	Vector3D d = s1.m_centerPosition - s0.m_centerPosition;
	float dist2 = DotProduct(d, d);

	// The sphere with the larger radius encloses the other;
	// just set s to be the larger of the two spheres
	if ((s1.m_radius - s0.m_radius)*(s1.m_radius - s0.m_radius) >= dist2) 
	{
		s1.m_radius >= s0.m_radius ? s = s1 : s = s0;
	}
	else 
	{
		// Spheres partially overlapping or disjoint
		float dist = sqrt(dist2);
		s.m_radius = (dist + s0.m_radius + s1.m_radius) * 0.5f;
		s.m_centerPosition = s0.m_centerPosition;
		if (dist > 0.0001)
		{
			s.m_centerPosition += ((s.m_radius - s0.m_radius) / dist) * d;
		}
	}

	return s;
}