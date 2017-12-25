#include "Dictionary.h"

Dictionary::Dictionary()
{
	hashTable = new Node*[N];
	for (int i = 0; i < N; i++)
		hashTable[i] = nullptr;
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
		int keyLength = key.length();
		int result = keyLength;
		for (int i = 0; i < keyLength; i++)
			result = (result << 4) ^ (result >> 8) ^ (key[i]);
		return result%N;
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
