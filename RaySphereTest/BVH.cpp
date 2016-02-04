#include "BVH.h"


int BVH::CalculateSplitIndex()
{
	return 42;
}

void BVH::Build(const std::vector<Sphere*>& spheres)
{
		//•Create new vector for the nodes ??

		std::vector<Sphere*> objects;

		std::vector<BVHNode*> nodes; //??

		BVHNode* rootNode = new BVHNode;
		Sphere boundingSphere;

		for (auto& sphere : spheres)
		{
			objects.push_back(sphere);
			boundingSphere.Expand(*sphere);
		}

		rootNode->m_boundingSphere = boundingSphere;

		BuildRecursive(0, objects.size(), rootNode, 0);
}

void BVH::BuildRecursive(int leftIndex, int rightIndex, BVHNode* node, int depth)
{
	int amount = rightIndex - leftIndex;

	if (amount <= 4)
	{
		node->MakeLeaf(leftIndex, amount);
	}
	else
	{
		int splitIndex = CalculateSplitIndex();

		BVHNode* leftNode = new BVHNode;
		BVHNode* rightNode = new BVHNode;
		Sphere leftBoundingSphere;
		Sphere rightBoundingSphere;

		leftNode->m_boundingSphere = leftBoundingSphere;
		rightNode->m_boundingSphere = rightBoundingSphere;

		node->MakeNode(leftNode, rightNode);

		BuildRecursive(leftIndex, splitIndex, leftNode, depth + 1);
		BuildRecursive(splitIndex, rightIndex, rightNode, depth + 1);
	}
}