#pragma once
#include "Vector3D.h"
#include "Object.h"

struct Sphere : public Object
{
	Sphere();

	Sphere(const Vector3D& center, float radius);
	void Expand(Sphere& sphere);

	virtual bool GetIntersection(Ray* ray, IntersectionInfo& info) override;

	//virtual Sphere GetBoundingSphere() override;

	float m_radius;
	Vector3D m_center;
};