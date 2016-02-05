#include "Scene.h"
#include <fstream>

////////////////////////////////////////////////////////////////////////////////////////////

void Scene::GenerateObjects()
{
	m_numberOfRays = GetRG()->GetRandomInt(0, 3);
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
		Vector3D pos = GetRG()->GetRandomPosition(0, 100000);
		float radius = GetRG()->GetRandomFloat(0, 1);

		m_spheres[i] = Sphere(pos, radius);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

void Scene::CheckForIntersections()
{
	std::ofstream stream;
	stream.open("log.txt");

	int intersectionsAmount = 0;

	stream << "Total rays: " << m_numberOfRays << " Total spheres: " << m_numberOfSpheres << std::endl;

	for (int i = 0; i < m_numberOfRays; i++)
	{
		for (int j = 0; j < m_numberOfSpheres; j++)
		{
			Vector3D resultPoint(0, 0, 0);

			IntersectionInfo info;
			
			bool intersect = m_spheres[j].GetIntersection(m_rays[i], info);

			if (intersect)
			{
				stream << intersectionsAmount << ": Ray " << i << " start: " << m_rays[i].m_startPos << " dir: " << m_rays[i].m_direction;
				stream << "Sphere " << j << " c: " << m_spheres[j].m_center << " rad: " << m_spheres[j].m_radius;
				stream << " Inters. point: " << info.m_intersPoint << std::endl;

				intersectionsAmount++;
			}
		}
	}

	stream.close();
}

////////////////////////////////////////////////////////////////////////////////////////////