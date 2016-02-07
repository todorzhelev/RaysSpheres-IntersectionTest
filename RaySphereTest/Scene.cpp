#include "Scene.h"
#include <fstream>

////////////////////////////////////////////////////////////////////////////////////////////

Scene::Scene(Timer* timer)
{
	m_timer = timer;
}

////////////////////////////////////////////////////////////////////////////////////////////

void Scene::GenerateObjects()
{
	m_timer->Start();

	m_numberOfRays = GetRG()->GetRandomInt(10000, 20000);
	m_numberOfSpheres = GetRG()->GetRandomInt(1000, 4000);

	m_rays = new Ray[m_numberOfRays];
	m_spheres= new Sphere[m_numberOfSpheres];

	for (int i = 0; i < m_numberOfRays; i++)
	{
		Vector3D pos = GetRG()->GetRandomPosition(0, 10000);
		Vector3D dir = GetRG()->GetRandomPosition(0, 100);

		m_rays[i] = Ray(pos, dir);
	}

	for (int i = 0; i < m_numberOfSpheres; i++)
	{
		Vector3D pos = GetRG()->GetRandomPosition(0, 10000);
		float radius = GetRG()->GetRandomFloat(0, 10);

		m_spheres[i] = Sphere(pos, radius);
	}

	auto elapsed = m_timer->Stop();

	std::cout << "Objects generation: " << elapsed.count() << " milliseconds" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////

void Scene::CheckForIntersections(BVH* bvh)
{
	std::ofstream stream;
	stream.open("logRegular.txt");

	std::ofstream stream1;
	stream1.open("logBVH.txt");

	int intersectionsAmount = 0;

	stream << "Total rays: " << m_numberOfRays << " Total spheres: " << m_numberOfSpheres << std::endl;
	stream1 << "Total rays: " << m_numberOfRays << " Total spheres: " << m_numberOfSpheres << std::endl;

	m_timer->Start();

	for (int i = 0; i < m_numberOfRays; i++)
	{
		std::vector<IntersectionInfo> intersInfo;
		BVHNode* rootNode = &bvh->m_nodes[0];
		bool bIntersect = RayBVHTest(&m_rays[i], bvh, rootNode, intersInfo);

		if (bIntersect)
		{
			for (auto& it : intersInfo)
			{
				stream1 << intersectionsAmount << ": Ray " << i << " start:" << m_rays[i].m_startPos << " dir:" << m_rays[i].m_direction;
				stream1 << "Sphere " << " c:" << it.m_object->m_center << " rad:" << it.m_object->m_radius;
				stream1 << " Inters. point:" << it.m_intersPoint << std::endl;
			}
		}
	}

	auto elapsed = m_timer->Stop();

	std::cout << "Intersection test with BVH: " << elapsed.count() << " milliseconds" << std::endl;

	m_timer->Start();

	for (int i = 0; i < m_numberOfRays; i++)
	{
		for (int j = 0; j < m_numberOfSpheres; j++)
		{
			Vector3D resultPoint(0, 0, 0);

			IntersectionInfo info;
			
			bool intersect = m_spheres[j].GetIntersection(&m_rays[i], info);

			if (intersect)
			{
				stream << intersectionsAmount << ": Ray " << i << " start:" << m_rays[i].m_startPos << " dir:" << m_rays[i].m_direction;
				stream << "Sphere " << j << " c:" << m_spheres[j].m_center << " rad:" << m_spheres[j].m_radius;
				stream << " Inters. point:" << info.m_intersPoint << std::endl;
				
				intersectionsAmount++;
			}
		}
	}

	elapsed = m_timer->Stop();

	std::cout << "Intersection test with O(M.N) complexity: " << elapsed.count() << " milliseconds" << std::endl;

	stream.close();
	stream1.close();
}

////////////////////////////////////////////////////////////////////////////////////////////

bool Scene::RayBVHTest(Ray* ray, BVH* bvh, BVHNode* node, std::vector<IntersectionInfo>& intersectInfo)
{
	if( node )
	{
		bool isLeaf = false;
		bool bAnyIntersects = false;
		if (node->m_bIsLeaf)
		{
			isLeaf = true;
			for (int i = node->m_index; i < node->m_index + node->m_amountOfObjectsInNode; i++)
			{
				IntersectionInfo info;
				bool bIntersect = bvh->m_objects[i]->GetIntersection(ray, info);

				if (bIntersect)
				{
					bAnyIntersects = true;
					intersectInfo.push_back(info);
				}
			}

			//if we had atleast one intersect return true
			if (bAnyIntersects)
			{
				return true;
			}
		}

		if(!isLeaf)
		{
			IntersectionInfo info;

			bool bIntersect = node->m_boundingSphere.GetIntersection(ray, info);
			bool bIntersectsFromLeftTree = false, bIntersectsFromRightTree = false;

			if (bIntersect)
			{
				//left node
				bIntersectsFromLeftTree = RayBVHTest(ray, bvh, &bvh->m_nodes[node->m_firstChildIndex], intersectInfo);

				//right node
				bIntersectsFromRightTree = RayBVHTest(ray, bvh, &bvh->m_nodes[node->m_firstChildIndex + 1], intersectInfo);

				return bIntersectsFromLeftTree || bIntersectsFromRightTree;
			}
			else
			{
				return false;
			}
		}
	}
	
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////