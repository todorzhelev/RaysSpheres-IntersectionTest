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

	static const int maxObjectsInLeaf = 4;

private:

	BVHNode* m_rootNode;
	std::vector<Sphere*> m_objects;

	Scene* m_scene;
};