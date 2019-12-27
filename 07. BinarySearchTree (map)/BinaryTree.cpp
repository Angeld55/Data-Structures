#pragma once
#include <iostream>

void swap(int& i, int& j);


//Binary Tree
struct Node
{
	Node(int k)
	{
		
		key = k;
		left = nullptr;
		right = nullptr;
	}
	int key;
	Node* left;
	Node* right;
};
Node* findMinNode(Node* st);
void addNode(Node*& dest, int key)
{
	if (dest == nullptr)
	{
		Node* newNode = new Node(key);
		dest = newNode;
	}
	else
	{
		if (key > dest->key)
			addNode(dest->right, key);
		else if (key < dest->key)
			addNode(dest->left, key);
		else
			throw "Element with number exist";
	}
}
Node* search(Node* st, int key)
{
	if (st == nullptr)
		return nullptr;
	else if (st->key == key)
		return st;
	else if (st->key>key)
		return search(st->left, key);
	else  (st->key < key);
	return search(st->right, key);
};
void deleteNode(Node*& st, int key)
{
	if (st == nullptr)
		return;
	else if (st->key == key)
	{
		if (st->left == nullptr&&st->right == nullptr) // No subtrees
		{
			delete st;
			st = nullptr;
		}
		else if (st->left == nullptr) //only right subtree
		{
			Node* temp = st->right;
			delete st;
			st = temp;
		}
		else if (st->right == nullptr) //only left subtree
		{
			Node*temp = st->left;
			delete st;
			st = temp;
		}
		else   // left and right subtrees
		{
			Node* min = findMinNode(st->right);//finding na min element from the right subtree
			
			//swaping two elements;
			swap(min->key, st->key);

			deleteNode(st->right, key); // we could use it directly the pointer min,but we wouldn't take care of the pointer from the parrent 
		}
	}
	else if (key > st->key)
		deleteNode(st->right, key);
	else
		deleteNode(st->left, key);
}
Node* findMinNode(Node* st)
{
	if (st == nullptr)
		return nullptr;
	if (st->left != nullptr)
		return findMinNode(st->left);
	else
		return st;
}
int countNodes(Node* root)
{
	if (root == nullptr)
		return 0;
	return 1 + countNodes(root->left) + countNodes(root->right);
}
void printNode(Node* node)
{
	if (node == nullptr)
		std::cout << "No node\n";
	else
		std::cout << "Node with key: " << node->key << std::endl;
}
void swap(int& i,int& j)
{
	int temp = i;
	i = j;
	j = temp;
}
void FreeTree(Node* root)
{
	if (root==nullptr)
		return;
	FreeTree(root->left);
	FreeTree(root->right);
	delete root;
}
int main()
{
	Node* parent = new Node(5);
	addNode(parent, 3);
	addNode(parent, 6);
	addNode(parent, 99);
	addNode(parent, 4);
	addNode(parent, 2);
	addNode(parent, 70);
	addNode(parent, 100);
	std::cout<<countNodes(parent);
	deleteNode(parent, 99);
	std::cout<<countNodes(parent);
	FreeTree(parent);
	return 0;

}
