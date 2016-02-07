#include "BVHNode.h"

/////////////////////////////////////////////////////////

BVHNode::BVHNode()
{
	m_bIsLeaf		  = true;
	m_leftNode		  = nullptr;
	m_rightNode		  = nullptr;
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
