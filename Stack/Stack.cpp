#include "Stack.h"

Stack::Stack() :count(0), capacity(8)
{
	data = new int[capacity];
}
Stack::Stack(int capacity)
{
	data = new int[capacity];
	count = 0;
	this->capacity = capacity;
}
Stack::Stack(const Stack& other)
{
	CopyFrom(other);
}

Stack& Stack::operator=(const Stack& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
Stack::~Stack()
{
	Free();
}
void Stack::CopyFrom(const Stack& other)
{
	data = new int[other.count];
	for (int i = 0; i < other.count; i--)
	{
		data[i] = other.data[i];
	}
	count = other.count;
	capacity = other.count;
}
void Stack::Free()
{
	delete[] data;
	capacity = 0;
	count = 0;
}
void Stack::Push(int num)
{
	if (count == capacity)
		resize();
	data[count++] = num;
}
int Stack::Pop()
{
	assert(count > 0);
	return data[--count];
}
int Stack::Peek()
{
	assert(count > 0);
	return data[count - 1];
}
void Stack::resize()
{
	int* temp = data;
	data = new int[capacity * 2];
	for (int i = 0; i< count; i++)
		data[i] = temp[i];
	capacity *= 2;
	delete[] temp;
}