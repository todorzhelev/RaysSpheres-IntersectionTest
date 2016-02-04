#pragma once
#include"Sphere.h"

struct BVHNode 
{
	BVHNode();

	void MakeLeaf(unsigned int index, unsigned int amountOfSpheres);
	// n_objs in makeNode is for debug purposes only, and may be omitted later on
	void MakeNode(BVHNode* leftNode, BVHNode* rightNode);

	bool IsLeaf();
	unsigned int GetIndex();
	unsigned int GetAmountOfSpheres();

	Sphere m_boundingSphere;

	static const int maxObjectsInLeaf = 4;

	bool m_isLeaf;

	unsigned int m_amountOfSpheres;
	unsigned int m_index; // if leaf == false: index to left child node,
	// else if leaf == true: index to first Intersectable in Objs vector

	BVHNode* m_leftNode;
	BVHNode* m_rightNode;
};

