
#include "DictionaryStringInt.h"

Node* CopyNode(Node* n)
{
	if (n == nullptr)
		return nullptr;
	return new Node(*n);
}
Dictionary::Dictionary()
{
	hashTable = new Node*[N];
	for (int i = 0; i < N; i++)
		hashTable[i] = nullptr;
}

Dictionary::Dictionary(const Dictionary& other)
{
	CopyFrom(other);
}

Dictionary& Dictionary::operator=(const Dictionary& other)
{
	if (this != & other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

Dictionary::~Dictionary()
{
	Free();
}

void Dictionary::insertBegin(std::string key, int value,int index)
{
	Node* newNode = new Node(key, value);
	newNode->next = hashTable[index];
	hashTable[index] = newNode;
}
Node* Dictionary::getNodeByKey(std::string key, int index){
	Node* iter = hashTable[index];
	while (iter != nullptr)
	{
		if (iter->key == key)
			return iter;
		iter = iter->next;
	}
	return nullptr;
}

unsigned Dictionary::hashFunction(std::string key)
{
		return 0;
		int keyLength = key.length();
		int result = keyLength;
		for (int i = 0; i < keyLength; i++)
			result = (result << 4) ^ (result >> 8) ^ (key[i]);
		return result%N;
}

void Dictionary::CopyFrom(const Dictionary& other)
{
	
	hashTable = new Node*[N];
	for (int i = 0; i < N; i++)
	{
		hashTable[i] = CopyNode(other.hashTable[i]);
		Node* iter = hashTable[i];
		if (!iter)
			continue;
		while (iter->next!=nullptr)
		{
			iter->next = CopyNode(iter->next);
			iter = iter->next;
		}
	}
}

void Dictionary::Free()
{
	for (int i = 0; i < N; ++i)
	{
		Node* iter = hashTable[i];
		while (iter!=nullptr)
		{
			Node* past = iter;
			iter = iter->next;
			delete past;
		}
	}
	delete[] hashTable;
}

bool Dictionary::put(std::string key, int value)
{
	unsigned result = hashFunction(key);
	if (getNodeByKey(key,result) != nullptr)
		return false; //exists
	insertBegin(key, value, result);
	return true;

}
bool Dictionary::remove(std::string key)
{
	unsigned result = hashFunction(key);
	Node* Iter = hashTable[result];
	if (Iter == nullptr)
		return false;
	if (Iter->next == nullptr)
	{
		if (Iter->key == key)
		{
			delete Iter;
			hashTable[result] = nullptr;
			return true;
		}
		return false;

	}
	Node* prev = Iter;
	Iter = prev->next;

	while (Iter != nullptr)
	{
		if (Iter->key == key)
		{
		
			prev->next = Iter->next;
			delete Iter;
			return true;
		}
	
	}
	return false;

}
int Dictionary::get(std::string key)
{
	unsigned result = hashFunction(key);
	Node* iter = hashTable[result];
	while (iter)
	{
		if (iter->key == key)
			return iter->value;
		iter = iter->next;
	}
	return -1;/// stupid

}
