#include "BVH.h"
#include<algorithm>
#include "Scene.h"

////////////////////////////////////////////////////////////////////////////////////////////
int dimensionSplit = 1; //1 - x, 2 - y, 3 - z

BVH::BVH(Scene* scene)
{
	m_scene = scene;
	m_nodesAmount = 0;
	Build();
}

////////////////////////////////////////////////////////////////////////////////////////////

void BVH::Build()
{
	m_nodes = new BVHNode[2 * m_scene->m_numberOfSpheres - 1];
	
	m_objects.resize(m_scene->m_numberOfSpheres);

	m_objects[0] = &m_scene->m_spheres[0];
	m_nodes[0].m_boundingSphere.m_radius = m_scene->m_spheres[0].m_radius;
	m_nodes[0].m_boundingSphere.m_center = m_scene->m_spheres[0].m_center;

	m_nodesAmount = 1;

	for (int i = 1; i < m_scene->m_numberOfSpheres; i++)
	{
		Sphere* sphere = &m_scene->m_spheres[i];
		m_objects[i] = sphere;

		m_nodes[0].m_boundingSphere.Expand(*sphere);
	}

	BuildRecursive(0, m_scene->m_numberOfSpheres-1, &m_nodes[0], 0);
}

////////////////////////////////////////////////////////////////////////////////////////////

void BVH::BuildRecursive(int leftIndex, int rightIndex, BVHNode* node, int depth)
{
	int amountOfObjects = rightIndex - leftIndex + 1;

	if (amountOfObjects <= BVH::maxObjectsInLeaf)
	{
		node->MakeLeaf(leftIndex, amountOfObjects);
	}
	else
	{
		//sort the spheres in the range [leftIndex,rightIndex] by x coordinate
		std::sort(m_objects.begin() + leftIndex, m_objects.begin() + rightIndex, [](Sphere* sphere1, Sphere* sphere2)
		{
			
			return sphere1->m_center.m_reg128.m128_f32[dimensionSplit] < sphere2->m_center.m_reg128.m128_f32[dimensionSplit];
		});

		int splitIndex = CalculateSplitIndex(leftIndex,rightIndex);

		//we cannot split the objects anymore, group them as one
		if( splitIndex == rightIndex )
		{
			node->MakeLeaf(leftIndex, amountOfObjects);
			return;
		}

		if (splitIndex == leftIndex)
		{
			node->MakeLeaf(leftIndex, amountOfObjects);
			return;
		}

		//we are interested in the position of the first child of the node
		//in the node list, not in the objects list. Each parent node has 2 children,
		//so we need the position only of the first one
		node->MakeNode(m_nodesAmount + 1, rightIndex - leftIndex);

		BVHNode* leftNode = &m_nodes[++m_nodesAmount];
		BVHNode* rightNode = &m_nodes[++m_nodesAmount];

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

		leftNode->m_boundingSphere.m_radius  = leftNodeBoundingSphere.m_radius;
		leftNode->m_boundingSphere.m_center = leftNodeBoundingSphere.m_center;

		rightNode->m_boundingSphere.m_radius = rightNodeBoundingSphere.m_radius;
		rightNode->m_boundingSphere.m_center = rightNodeBoundingSphere.m_center;

		BuildRecursive(leftIndex, splitIndex, leftNode, depth + 1);
		BuildRecursive(splitIndex, rightIndex, rightNode, depth + 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

int BVH::CalculateSplitIndex(int leftIndex, int rightIndex)
{
	float sphere1CenterX = m_objects[leftIndex]->m_center.m_reg128.m128_f32[dimensionSplit];
	float sphere2CenterX = m_objects[rightIndex]->m_center.m_reg128.m128_f32[dimensionSplit];

	float splitValue = (sphere1CenterX + sphere2CenterX) / 2.0f;

	int splitIndex = leftIndex;
	for (int i = leftIndex; i <= rightIndex; i++)
	{
		if( m_objects[i]->m_center.m_reg128.m128_f32[dimensionSplit] > splitValue)
		{
			splitIndex = i;
			break;
		}
	}
	return splitIndex;
}

////////////////////////////////////////////////////////////////////////////////////////////