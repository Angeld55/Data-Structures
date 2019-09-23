#pragma once
#include <iostream>

class BinaryHeap
{
    int* arr;
    int capacity;
    int count;
	void swap(int i, int j);
	int closestPowerOfTwo(int n);
	void resizeArr(int newCap);
	void printHelp(int el, int space);
	int LeftChildIndex(int i);
	int RightChildIndex(int i);
	int ParentIndex(int i);

	void CopyFrom(const BinaryHeap& other);
	void Free();
    public:

	BinaryHeap(); //Empty
    BinaryHeap(const int* a, int len);
	
	BinaryHeap(const BinaryHeap& other);
	BinaryHeap& operator=(const BinaryHeap& other);

	void Add(int el);
   
	int ExtractMax();

	void Heapyfy(int* arr,int el, int count);
    
	void Print();
	~BinaryHeap();

};

void BinaryHeap::swap(int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int BinaryHeap::closestPowerOfTwo(int n)
{
	int res = 1;
	while (res<n)
		res *= 2;
	return res;
}

void BinaryHeap::resizeArr(int newCap)
{
	int* temp = arr;
	arr = new int[newCap];
	for (size_t i = 0; i < count; i++)
		arr[i] = temp[i];
	capacity = newCap;
	delete[] temp;
}

void BinaryHeap::printHelp(int elIndex, int space)
{
	if (elIndex>=count)
		return;

	// Increase distance between levels  
	space += 10;

	// Process right child first  
	printHelp(RightChildIndex(elIndex), space);
	
	// Print current node after space  
	// count  
	std::cout << std::endl;

	for (int i = 10; i < space; i++)
		std::cout << " ";
	std::cout << arr[elIndex] << "\n";

	// Process left child  
	printHelp(LeftChildIndex(elIndex), space);
}

BinaryHeap::BinaryHeap()
{
	capacity = 8;
	arr = new int[capacity];
	count = 0;
}
BinaryHeap::BinaryHeap(const int* a, int len)
{
	capacity = closestPowerOfTwo(len);
	arr = new int[capacity];
	count = len;
	for (int i = 0; i<len; i++)
		arr[i] = a[i];
	for (int i = len / 2; i >= 0; i--)
		Heapyfy(arr,i, count);
}

BinaryHeap::BinaryHeap(const BinaryHeap& other)
{
	CopyFrom(other);
}

int BinaryHeap::LeftChildIndex(int i)
{
	return i * 2 + 1;
}
int BinaryHeap::RightChildIndex(int i)
{
	return i * 2 + 2;
}
int BinaryHeap::ParentIndex(int i)
{
	return (i - 1) / 2;
}

void BinaryHeap::CopyFrom(const BinaryHeap& other)
{
	arr = new int[other.capacity];
	for (int i = 0; i < other.count; i++)
		arr[i] = other.arr[i];
	capacity = other.capacity;
	count = other.count;
}

void BinaryHeap::Free()
{
	delete[] arr;
}

BinaryHeap& BinaryHeap::operator=(const BinaryHeap& other)
{
	if (this!=&other)
	{
		Free();
		CopyFrom(other);
	}
	return  *this;
}

void BinaryHeap::Add(int el)
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

int BinaryHeap::ExtractMax()
{
	int max = arr[0];
	swap(0, count - 1);
	count--;
	Heapyfy(arr,0, count - 1);
	if (count > 1 && count < capacity / 2)
		resizeArr(capacity / 2);
	return max;
}
void BinaryHeap::Heapyfy(int* arr,int el, int count)
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
void BinaryHeap::Print()
{
	printHelp(0, 0);
}
BinaryHeap::~BinaryHeap()
{
	delete[] arr;
}

//Not the best implementation! For better code, see Algorithms repository
void HeapSort(int* arr,int len)
{
    BinaryHeap heap(arr,len); //O(n)
    for(int i =len-1;i>=0;i--)  //n times
        arr[i]=heap.ExtractMax(); //O(logn)

}
int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	BinaryHeap b(arr, 6);
	//b.ExtractMax();
	b.Print();
}
