#pragma once
#include"Sphere.h"

struct BVHNode 
{
	BVHNode();

	//the bounding sphere of the node
	Sphere m_boundingSphere;

	//is the node leaf?
	bool m_bIsLeaf;

	//amount of objects in this node
	int m_amountOfObjects;

	BVHNode* m_leftNode;
	BVHNode* m_rightNode;
};

