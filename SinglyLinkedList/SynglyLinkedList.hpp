#include <iostream>

template <typename T>
class LinkedList
{
	struct Node
	{
		Node(T data)
		{
			this->data = data;
			next = nullptr;
		}
		T data;
		Node* next;
	};
	Node* head;
	Node* tail;
public:
	LinkedList();

	void AddLast(T);
	void AddFirst(T);

	T RemoveFirst();
    T RemoveLast();
	
	T PeekFirst();
	T PeekLast();
	

    void Print();
	
    T GetAtIndex(int index);
	
    ~LinkedList();
};
template <typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

template <typename T>
void LinkedList<T>::AddLast(T el)
{
	Node* newNode = new Node(el);
	if (head == nullptr&&tail == nullptr)//if its empty
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}
template <typename T>
void LinkedList<T>::AddFirst(T el)
{
	Node* newNode = new Node(el);
	if (head == nullptr&&tail == nullptr)//if its empty
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode->next = head;
		head = newNode;
	}
}
template <typename T>
T LinkedList<T>::PeekFirst()
{
	return head->data;
}
template <typename T>
T LinkedList<T>::PeekLast()
{
	return tail->data;
}
template <typename T>
T LinkedList<T>::RemoveLast()
{
	if (head == nullptr&&tail == nullptr)
		throw "The list is empty";
	else if (head == tail)
	{
		T el = head->data;
		delete head;
		head = nullptr;
		tail = nullptr;
		return el;
	}
	else
	{
		Node* prev = head;
		Node* current = head->next;
		while (current != tail)
		{
			prev = prev->next;
			current = current->next;
		}
		T el = tail->data;
		delete tail;
		tail = prev;
		prev->next = nullptr;
		return el;

	}

}
template <typename T>
T LinkedList<T>::RemoveFirst()
{
	if (head == nullptr&&tail == nullptr)
		throw "The list is empty";
	else if (head == tail)
	{
		T el = head->data;
		delete head;
		head = nullptr;
		tail = nullptr;
		return el;
	}
	else
	{
		T el = head->data;
		Node* temp = head->next;
		delete head;
		head = temp;
		return el;
	}

}

template <typename T>
void LinkedList<T>::Print()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		std::cout << iter->data;
		if (iter->next != nullptr)
			std::cout << "->";
		iter = iter->next;
	}
	std::cout << std::endl;

}
template <typename T>
T LinkedList<T>::GetAtIndex(int index)
{
	Node* res = head;
	for (int i = 0; res != nullptr&&i< index; i++)
		res = res->next;

	if (res == nullptr)
		throw "No such index";
	return res->data;
}
template <typename T>
LinkedList<T>::~LinkedList()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* next = iter->next;
		delete iter;
		iter = next;
	}
}

