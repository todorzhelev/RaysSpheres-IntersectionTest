#pragma once
#include<vector>
#include "BVHNode.h"

class Scene;

class BVH
{
public:

	BVH(Scene* scene);

	void Build();

	void BuildRecursive(int leftIndex, int rightIndex, BVHNode* node, int depth);

	int BVH::CalculateSplitIndex(int leftIndex, int rightIndex);

	static const int maxObjectsInLeaf = 30;

	std::vector<Sphere*> m_objects;
	int m_nodesAmount;
	BVHNode* m_nodes;
	Scene* m_scene;
};