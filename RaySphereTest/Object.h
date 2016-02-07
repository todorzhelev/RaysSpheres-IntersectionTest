#pragma once
#include"Ray.h"
#include"Sphere.h"
#include"IntersectionInfo.h"

struct Object
{
	virtual bool GetIntersection(Ray* ray, IntersectionInfo& info) = 0;
};