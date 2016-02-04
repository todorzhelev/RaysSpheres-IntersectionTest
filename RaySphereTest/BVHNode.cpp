#include "BVHNode.h"

BVHNode::BVHNode()
{
	m_isLeaf = true;
	m_leftNode = nullptr;
	m_rightNode = nullptr;
	m_amountOfSpheres = 0;
}

void BVHNode::MakeLeaf(unsigned int index, unsigned int amountOfSpheres)
{
	m_isLeaf = true;
}

void BVHNode::MakeNode(BVHNode* leftNode, BVHNode* rightNode)
{
	m_isLeaf = false;
	m_leftNode = leftNode;
	m_rightNode = rightNode;
}

bool BVHNode::IsLeaf() 
{ 
	return m_isLeaf; 
}

unsigned int BVHNode::GetIndex() 
{ 
	return m_index; 
}

unsigned int BVHNode::GetAmountOfSpheres() 
{ 
	return m_amountOfSpheres; 
}
