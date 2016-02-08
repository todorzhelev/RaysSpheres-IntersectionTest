#pragma once
#include"Sphere.h"

struct BVHNode 
{
	BVHNode();
	void MakeLeaf(int indexInObjectList, int amountOfObjects);
	void MakeNode(int firstChildIndex, int amountOfObjects);

	//the bounding sphere of the node
	Sphere m_boundingSphere;

	//is the node leaf?
	bool m_bIsLeaf;

	//amount of objects in this node
	int m_amountOfObjectsInNode;

	//starting index of the node
	int m_indexInNodeList;
	int m_indexInObjectList;

	int m_firstChildIndexInNodeList;
};

