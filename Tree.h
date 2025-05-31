#pragma once

struct Node
{
	int Data;
	Node* pLeft;
	Node* pRight;
};

class Tree
{
	friend void Recursion(Node* pTemp);
public:
	Tree();
	~Tree();
	void readFile(std::ifstream& rf);

	void PrintTree();

private:
	void add(int data);
	void DeleteTree(Node* pTemp);
	Node* pHead;
};