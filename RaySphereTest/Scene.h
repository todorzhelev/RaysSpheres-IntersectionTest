#pragma once
#include<vector>
#include<iostream>
#include"IntersectionInfo.h"

//////////////////////////////////////////////////////

class Timer;
class Ray;
class Sphere;
class BVH;
class BVHNode;

//////////////////////////////////////////////////////

class Scene
{
public:
	Scene(Timer* timer);

	void GenerateObjects();
	void CheckForIntersections(BVH* bvh);
	bool RayBVHTest(Ray* ray, BVH* bvh, BVHNode* node, std::vector<IntersectionInfo>& info);
	int m_numberOfRays;
	int m_numberOfSpheres;

	Ray* m_rays;
	Sphere* m_spheres;
	Timer* m_timer;
};

//////////////////////////////////////////////////////