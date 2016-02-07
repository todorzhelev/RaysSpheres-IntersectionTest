#pragma once
#include"Vector3D.h"

class Sphere;

struct IntersectionInfo 
{
	float m_t;				 // Intersection distance along the ray
	Sphere* m_object;		 // Object that was hit
	Vector3D m_intersPoint;	 // Location of the intersection
};