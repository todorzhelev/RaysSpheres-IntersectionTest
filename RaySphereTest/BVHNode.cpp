#include "BVHNode.h"

/////////////////////////////////////////////////////////

BVHNode::BVHNode()
{
	m_bIsLeaf = true;
	m_amountOfObjectsInNode = 0;
}

/////////////////////////////////////////////////////////

void BVHNode::MakeLeaf(int index, int amountOfObjects)
{
	m_bIsLeaf = true;
	m_index = index;
	m_amountOfObjectsInNode = amountOfObjects;
}

/////////////////////////////////////////////////////////

void BVHNode::MakeNode(int firstChildIndex, int amountOfObjects)
{
	m_firstChildIndex = firstChildIndex;
	m_bIsLeaf = false;
	m_amountOfObjectsInNode = amountOfObjects;
}

/////////////////////////////////////////////////////////
