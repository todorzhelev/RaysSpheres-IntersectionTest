#pragma once
#include<vector>
#include<iostream>
#include"Ray.h"
#include"Sphere.h"
#include"RandomGenerator.h"
#include "BVH.h"

class Scene
{
public:

	void GenerateObjects();
	void CheckForIntersections(bool bWithAllSpheres, BVH& bvh);
	bool RayBVHTest(Ray& ray, BVHNode* node, IntersectionInfo& info);
	int m_numberOfRays;
	int m_numberOfSpheres;
	Ray* m_rays;
	Sphere* m_spheres;	
};