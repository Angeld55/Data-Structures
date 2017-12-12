#include <iostream>
#include <string>


//Binary Tree ,searching by key
struct Node
{
	Node(int k,std::string d)
	{
		data = d;
		key = k;
		data = d;
		left = nullptr;
		right = nullptr;
	}
	std::string data;
	int key;
	Node* left;
	Node* right;
};
Node* findMinNode(Node* st);
void addNode(Node*& dest,int key, std::string data)
{
	if (dest == nullptr)
	{
		Node* newNode = new Node(key, data);
		dest = newNode;
	}
	else
	{
		if (key > dest->key)
			addNode(dest->right, key, data);
		else if (key < dest->key)
			addNode(dest->left, key, data);
		else
			std::cout << "Element with such key exist\n";
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
			std::string minData = min->data;
			int minKey = min->key;
			min->data = st->data;
			min->key = st->key;
			st->data =minData;
			st->key = minKey;

			deleteNode(st->right,key); // we could use it directly the pointer min,but we wouldn't take care of the pointer from the parrent 
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
void printNode(Node* node)
{
	if (node == nullptr)
		std::cout << "No node\n";
	else
		std::cout << "Node with key: " << node->key << " Data: " << node->data << std::endl;
}

int main()
{
	Node* parent = new Node(5, "Angel");
	addNode(parent, 3, "Ivan");
	addNode(parent, 6, "Stefan");
	addNode(parent, 99, "Petko");
	addNode(parent, 4, "Gosho");
	addNode(parent, 2, "Iliqn");
	addNode(parent, 70, "Deba");
	addNode(parent, 100, "Peshkata");
	deleteNode(parent, 99);
	return 0;

}
