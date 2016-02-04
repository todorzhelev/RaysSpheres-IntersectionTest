#pragma once
#include<vector>
#include "BVHNode.h"

class BVH
{
	void Build(const std::vector<Sphere*>& spheres);

	void BuildRecursive(int leftIndex, int rightIndex, BVHNode* node, int depth);

	int CalculateSplitIndex();

};