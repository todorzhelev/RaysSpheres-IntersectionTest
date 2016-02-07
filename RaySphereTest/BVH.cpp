#include "BVH.h"
#include<algorithm>
#include "Scene.h"

////////////////////////////////////////////////////////////////////////////////////////////

BVH::BVH(Scene* scene)
{
	m_scene = scene;
	Build();
}

////////////////////////////////////////////////////////////////////////////////////////////

void BVH::Build()
{
	m_rootNode = new BVHNode;

	m_objects.push_back(&m_scene->m_spheres[0]);
	m_rootNode->m_boundingSphere = m_scene->m_spheres[0];

	for (int i = 1; i < m_scene->m_numberOfSpheres; i++)
	{
		Sphere* sphere = &m_scene->m_spheres[i];

		m_objects.push_back(sphere);

		m_rootNode->m_boundingSphere.Expand(*sphere);
	}

	BuildRecursive(0, m_scene->m_numberOfSpheres-1, m_rootNode, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////

void BVH::BuildRecursive(int leftIndex, int rightIndex, BVHNode* node, int depth)
{
	int amountOfObjects = rightIndex - leftIndex + 1;

	if (amountOfObjects <= BVH::maxObjectsInLeaf)
	{
		node->m_bIsLeaf = true;
		return;
	}
	else
	{
		//sort the spheres in the range [leftIndex,rightIndex] by x coordinate
		std::sort(m_objects.begin() + leftIndex, m_objects.begin() + rightIndex, [](Sphere* sphere1, Sphere* sphere2)
		{
			int sortDimension = 1; //1 - x, 2 - y, 3 - z
			return sphere1->m_center.m_reg128.m128_f32[sortDimension] < sphere2->m_center.m_reg128.m128_f32[sortDimension];
		});

		int splitIndex = CalculateSplitIndex(leftIndex,rightIndex);

		//we cannot split the objects anymore, group them as one
		if( splitIndex == rightIndex )
		{
			node->m_bIsLeaf = true;
			return;
		}

		if (splitIndex == leftIndex)
		{
			node->m_bIsLeaf = true;
			return;
		}

		node->m_leftNode  = new BVHNode;
		node->m_rightNode = new BVHNode;

		Sphere leftNodeBoundingSphere = *m_objects[leftIndex];;
		Sphere rightNodeBoundingSphere = *m_objects[splitIndex];

		for (int i = leftIndex+1; i < splitIndex; i++)
		{
			leftNodeBoundingSphere.Expand(*m_objects[i]);
		}

		for (int i = splitIndex+1; i <= rightIndex; i++)
		{
			rightNodeBoundingSphere.Expand(*m_objects[i]);
		}

		node->m_leftNode->m_boundingSphere  = leftNodeBoundingSphere;
		node->m_rightNode->m_boundingSphere = rightNodeBoundingSphere;

		node->m_bIsLeaf = false;
		//node->m_amountOfObjects = amountOfObjects;

		BuildRecursive(leftIndex, splitIndex, node->m_leftNode, depth + 1);
		BuildRecursive(splitIndex, rightIndex, node->m_rightNode, depth + 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

int BVH::CalculateSplitIndex(int leftIndex, int rightIndex)
{
	float sphere1CenterX = m_objects[leftIndex]->m_center.m_reg128.m128_f32[1];
	float sphere2CenterX = m_objects[rightIndex]->m_center.m_reg128.m128_f32[1];

	float splitValue = (sphere1CenterX + sphere2CenterX) / 2.0f;

	int splitIndex = leftIndex;
	for (int i = leftIndex; i <= rightIndex; i++)
	{
		if( m_objects[i]->m_center.m_reg128.m128_f32[1] > splitValue)
		{
			splitIndex = i;
			break;
		}
	}
	return splitIndex;
}

////////////////////////////////////////////////////////////////////////////////////////////