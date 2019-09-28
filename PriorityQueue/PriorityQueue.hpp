#pragma once
#include <iostream>

template<typename T>
class PriorityQueue
{
	T* arr;
	int capacity;
	int count;
	void swap(int i, int j);
	int closestPowerOfTwo(int n);
	void resizeArr(int newCap);
	
	int LeftChildIndex(int i);
	int RightChildIndex(int i);
	int ParentIndex(int i);

	void Heapyfy(T* arr, int el, int count);
	
	void CopyFrom(const PriorityQueue& other);
	void Free();
	
	
public:

	PriorityQueue(); //Empty
	PriorityQueue(const T* a, int len);

	PriorityQueue(const PriorityQueue& other);
	PriorityQueue& operator=(const PriorityQueue& other);
	~PriorityQueue();

	void Add(T el);
	T Get();
	T Peek();
	
	bool isEmpty();



};

template <typename T>
void PriorityQueue<T>::swap(int i, int j)
{
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template <typename T>
int PriorityQueue<T>::closestPowerOfTwo(int n)
{
	int res = 1;
	while (res<n)
		res *= 2;
	return res;
}

template <typename T>
void PriorityQueue<T>::resizeArr(int newCap)
{
	T* temp = arr;
	arr = new T[newCap];
	for (size_t i = 0; i < count; i++)
		arr[i] = temp[i];
	capacity = newCap;
	delete[] temp;
}

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	capacity = 8;
	arr = new T[capacity];
	count = 0;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const T* a, int len)
{
	capacity = closestPowerOfTwo(len);
	arr = new int[capacity];
	count = len;
	for (int i = 0; i<len; i++)
		arr[i] = a[i];
	for (int i = len / 2; i >= 0; i--)
		Heapyfy(arr, i, count);
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& other)
{
	CopyFrom(other);
}

template <typename T>
int PriorityQueue<T>::LeftChildIndex(int i)
{
	return i * 2 + 1;
}

template <typename T>
int PriorityQueue<T>::RightChildIndex(int i)
{
	return i * 2 + 2;
}

template <typename T>
int PriorityQueue<T>::ParentIndex(int i)
{
	return (i - 1) / 2;
}

template <typename T>
void PriorityQueue<T>::Heapyfy(T* arr, int el, int count)
{
	int elIndex = el;
	while (true)
	{
		int leftChIndex = LeftChildIndex(elIndex);
		int rightChIndex = RightChildIndex(elIndex);

		bool isSmallerThanLeft = leftChIndex<count && arr[elIndex]<arr[leftChIndex];
		bool isSmallerThanRight = rightChIndex<count && arr[elIndex]<arr[rightChIndex];

		if (isSmallerThanLeft&&!isSmallerThanRight)
		{
			swap(elIndex, LeftChildIndex(elIndex));
			elIndex = LeftChildIndex(elIndex);
		}
		else if (!isSmallerThanLeft&&isSmallerThanRight)
		{
			swap(elIndex, RightChildIndex(elIndex));
			elIndex = RightChildIndex(elIndex);
		}
		else if (isSmallerThanLeft&&isSmallerThanRight)
		{
			if (arr[LeftChildIndex(elIndex)]>arr[RightChildIndex(elIndex)])
			{
				swap(elIndex, LeftChildIndex(elIndex));
				elIndex = LeftChildIndex(elIndex);
			}
			else
			{
				swap(elIndex, RightChildIndex(elIndex));
				elIndex = RightChildIndex(elIndex);
			}
		}
		else
			break;

	}
}


template <typename T>
void PriorityQueue<T>::CopyFrom(const PriorityQueue& other)
{
	arr = new T[other.capacity];
	for (int i = 0; i < other.count; i++)
		arr[i] = other.arr[i];
	capacity = other.capacity;
	count = other.count;
}

template <typename T>
void PriorityQueue<T>::Free()
{
	delete[] arr;
}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return  *this;
}

template <typename T>
void PriorityQueue<T>::Add(T el)
{
	if (count == capacity)
		resizeArr(capacity * 2);
	arr[count] = el;
	int indexOfAdded = count;
	int indexOfparent = ParentIndex(indexOfAdded);
	while ((indexOfAdded != 0) && (arr[indexOfAdded]>arr[indexOfparent]))
	{
		swap(indexOfAdded, indexOfparent);
		indexOfAdded = indexOfparent;
		indexOfparent = ParentIndex(indexOfAdded);
	}
	count++;
}

template <typename T>
T PriorityQueue<T>::Get()
{
	if(count==0)
		throw "No elements";
	T max = arr[0];
	swap(0, count - 1);
	count--;
	Heapyfy(arr, 0, count);
	if (count > 1 && count < capacity / 2)
		resizeArr(capacity / 2);
	return max;
}
template <typename T>
T PriorityQueue<T>::Peek()
{
	if(count==0)
		throw "No elements";
	return arr[0];
}
template <typename T>
bool PriorityQueue<T>::isEmpty()
{
	return count==0;
}


template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	delete[] arr;
}


int main()
{
	PriorityQueue<char> b;

	std::cout<<b.isEmpty();

}
