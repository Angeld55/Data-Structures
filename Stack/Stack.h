#include <assert.h>
class Stack
{
private:
	int* data;
	int count;
	int capacity;
	void resize();
	void CopyFrom(const Stack& other);
	void Free();
public:
	Stack(int capacity);
	Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& other);
	~Stack();
	void Push(int);
	int Pop();
	int Peek();

};