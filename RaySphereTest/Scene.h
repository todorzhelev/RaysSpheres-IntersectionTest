#pragma once
#include<vector>
#include<iostream>
#include"Ray.h"
#include"Sphere.h"
#include"RandomGenerator.h"
#include"BVH.h"

class Scene
{
public:

	void GenerateObjects();
	void CheckForIntersections();
	bool IntersectRaySphere(Ray& ray, Sphere& sphere, Vector3D& intersectionPoint);

private:

	std::vector<Ray> rays;
	std::vector<Sphere> spheres;
};