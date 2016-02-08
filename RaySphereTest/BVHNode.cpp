#include "BVHNode.h"

/////////////////////////////////////////////////////////

BVHNode::BVHNode()
{
	m_bIsLeaf = false;
	m_amountOfObjectsInNode = 0;
}

/////////////////////////////////////////////////////////

void BVHNode::MakeLeaf(int indexInObjectList, int amountOfObjects)
{
	m_bIsLeaf = true;
	m_indexInObjectList = indexInObjectList;
	m_amountOfObjectsInNode = amountOfObjects;
}

/////////////////////////////////////////////////////////

void BVHNode::MakeNode(int firstChildIndexInNodeList, int amountOfObjects)
{
	m_firstChildIndexInNodeList = firstChildIndexInNodeList;
	m_bIsLeaf = false;
	m_amountOfObjectsInNode = amountOfObjects;
}

/////////////////////////////////////////////////////////
