#pragma once
#include"Vector3D.h"

class Sphere;

struct IntersectionInfo 
{
	Sphere* m_object;	
	Vector3D m_intersPoint;
};