#pragma once
#include<vector>
#include<iostream>
#include"Ray.h"
#include"Sphere.h"
#include"RandomGenerator.h"

class Scene
{
public:

	void GenerateObjects();
	void CheckForIntersections(bool bWithAllSpheres);

private:

	Ray* m_rays;
	Sphere* m_spheres;

	int m_numberOfRays;
	int m_numberOfSpheres;
};