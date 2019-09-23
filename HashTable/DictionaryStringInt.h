#pragma once
#include<iostream>
#define N 221
struct Node
{
	Node(std::string key, unsigned value)
	{
		this->key = key;
		this->value = value;
		next = nullptr;
	}
	std::string key;
	unsigned value;
	Node* next;
};



class Dictionary
{

private:
	Node** hashTable;
	void insertBegin(std::string key, int value,int index);
	Node* getNodeByKey(std::string key, int index);
	unsigned hashFunction(std::string key);

	void CopyFrom(const Dictionary& other);
	void Free();
public:
	Dictionary();

	Dictionary(const Dictionary& other);
	Dictionary& operator=(const Dictionary& other);
	~Dictionary();

	bool remove(std::string);
	bool put(std::string, int value);
	bool contains(std::string);
	int get(std::string);
	
};
