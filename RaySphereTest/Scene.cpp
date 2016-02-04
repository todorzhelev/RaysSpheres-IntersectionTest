#include "Scene.h"

////////////////////////////////////////////////////////////////////////////////////////////

void Scene::GenerateObjects()
{
	m_numberOfRays = GetRG()->GetRandomInt(0, 300);
	m_numberOfSpheres = GetRG()->GetRandomInt(0, 2000);

	m_rays = new Ray[m_numberOfRays];
	m_spheres= new Sphere[m_numberOfSpheres];

	for (int i = 0; i < m_numberOfRays; i++)
	{
		Vector3D pos = GetRG()->GetRandomPosition(0, 10000);
		Vector3D dir = GetRG()->GetRandomPosition(0, 10000);

		m_rays[i] = Ray(pos, dir);
	}

	for (int i = 0; i < m_numberOfSpheres; i++)
	{
		Vector3D pos = GetRG()->GetRandomPosition(0, 10000);
		float radius = GetRG()->GetRandomFloat(0, 1);

		m_spheres[i] = Sphere(pos, radius);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

void Scene::CheckForIntersections()
{
	int intersectionsAmount = 0;

	for (int i = 0; i < m_numberOfRays; i++)
	{
		for (int j = 0; j < m_numberOfSpheres; j++)
		{
			Vector3D resultPoint(0, 0, 0);

			IntersectionInfo info;
			
			bool intersect = m_spheres[j].GetIntersection(m_rays[i], info);

			if (intersect)
			{
				std::cout << intersectionsAmount << " Intersection point: " << info.m_intersPoint << std::endl;

				intersectionsAmount++;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////