#pragma once
#include"Vector3D.h"

class Object;

struct IntersectionInfo 
{
	float m_t;				 // Intersection distance along the ray
	Object* m_object;		 // Object that was hit
	Vector3D m_intersPoint;	 // Location of the intersection
};