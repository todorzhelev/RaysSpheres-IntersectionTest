#pragma once
#include<vector>
#include<iostream>
#include"Ray.h"
#include"Sphere.h"
#include"RandomGenerator.h"
#include "BVH.h"
#include "Timer.h"

class Scene
{
public:
	Scene(Timer* timer);

	void GenerateObjects();
	void CheckForIntersections(BVH* bvh);
	bool RayBVHTest(Ray* ray, BVH* bvh, BVHNode* node, std::vector<IntersectionInfo>& info);
	int m_numberOfRays;
	int m_numberOfSpheres;

	BVH* m_bvh;
	Ray* m_rays;
	Sphere* m_spheres;
	Timer* m_timer;
};