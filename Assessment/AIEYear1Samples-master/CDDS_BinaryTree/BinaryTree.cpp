#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>

using namespace std;


BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while(m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const 
{ 
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue)
{

	if (IsEmpty()) { 
		m_pRoot = new TreeNode(a_nValue); 
		return;
	}

	TreeNode* currentNode = m_pRoot;
	TreeNode* parentNode = currentNode;

	while (currentNode != nullptr)
	{
		if (a_nValue < currentNode->GetData())
		{
			parentNode = currentNode;
			currentNode = currentNode->GetLeft();
			continue;
		}
		if (a_nValue > currentNode->GetData())
		{
			parentNode = currentNode;
			currentNode = currentNode->GetRight();
			continue;
		}
		if (a_nValue == currentNode->GetData())
		{
			return;
		}
	}

	if (a_nValue < parentNode->GetData()) 
	{ 
		TreeNode* newNode = new TreeNode(a_nValue);
		parentNode->SetLeft(newNode);
	}
	else 
	{
		TreeNode* newNode = new TreeNode(a_nValue);
		parentNode->SetRight(newNode);
	}

	//Assert::AreEqual(a_nValue, currentNode->GetData());
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	ppOutNode = m_pRoot;
	while (ppOutNode != nullptr) 
	{
		if (a_nSearchValue == ppOutNode->GetData()) {
			return (ppOutNode);
		}
		else {
			if (a_nSearchValue < ppOutNode->GetData()) ppOutNode = ppOutNode->GetLeft();
			else ppOutNode = ppOutNode->GetRight();
		}
	}

	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	TreeNode* currentNode = Find(a_nValue);

	////is currentNode leaf
	//if (currentNode->GetRight() == nullptr && currentNode->GetLeft() == nullptr)
	//{
	//	currentNode = nullptr;
	//	return;
	//}

	////is currentNode branch
	//if (currentNode->GetRight() != nullptr && currentNode->GetRight() != nullptr) 
	//{
	//	TreeNode* childNode = currentNode->GetRight();
	//	TreeNode* parentNode = childNode;
	//	while (childNode->GetLeft() != nullptr) {
	//		parentNode = childNode;
	//		childNode = childNode->GetLeft();
	//	}
	//	currentNode->SetData(childNode->GetData());
	//	if (currentNode == parentNode->GetLeft()) {
	//		parentNode->GetLeft()->SetData(childNode->GetRight()->GetData());
	//	}
	//	if (currentNode == parentNode->GetRight()) {
	//		parentNode->GetRight()->SetData(childNode->GetRight()->GetData());
	//	}
	//}
	////right has node but left doesnt
	//if (currentNode->GetRight() != nullptr && currentNode->GetLeft() == nullptr) 
	//{

	//}
	////left has node but right doesnt
	//if (currentNode->GetRight() == nullptr && currentNode->GetLeft() != nullptr) 
	//{
	//	
	//}
	////if (currentNode == parentNode->GetLeft()) {
	////	parentNode->GetLeft()->SetData(currentNode->GetLeft()->GetData());
	////}
	////if (currentNode == parentNode->GetRight()) {
	////	parentNode->GetRight()->SetData(currentNode->GetLeft()->GetData());
	////}
	////if (currentNode == m_pRoot) {
	////	m_pRoot->SetData(currentNode->GetLeft()->GetData());
	////}

}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
    PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			
			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}