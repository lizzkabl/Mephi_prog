#pragma once
#include "ShrdPtr.h"
template<typename T>
struct Node
{
	T data;
	ShrdPtr<Node<T>> prev;
	ShrdPtr<Node<T>> next;

	Node() : data{ NULL }, prev{ nullptr }, next{ nullptr } { }
	Node(const T& item) : data{ item }, prev{ nullptr }, next{ nullptr } { }
};

template <class T>
class LinkedList {
private:
	size_t size;
	ShrdPtr<Node<T>> head;
	ShrdPtr<Node<T>> tail;

public:
	~LinkedList() = default;

	LinkedList()
	{
		this->head = this->tail = nullptr;
		this->size = 0;
	}

	LinkedList(const LinkedList <T>& other) :size{ other.size }
	{
		ShrdPtr<Node<T>> help = other.head;
		for (int i = 0; i < size; i++)
		{
			Node<T>* p = new Node<T>(help->data);
			p->prev = this->tail;

			if (tail != NULL)
			{
				this->tail->next = p;
			}
			if (head == NULL)
			{
				this->head = p;
			}
			this->tail = p;
			if (help->next != NULL)
			{
				help = help->next;
			}
		}
	}

	LinkedList(T* items, size_t count)
	{
		this->size = count;
		for (int i = 0; i < count; i++)
		{
			Node<T>* p = new Node<T>(items[i]);
			p->prev = this->tail;
			if (tail != NULL)
			{
				this->tail->next = p;
			}
			if (head == NULL)
			{
				this->head = p;
			}
			this->tail = p;
		}
	}

	T GetFirst() const
	{
		if (this->GetLength() == 0)
		{
			throw  "IndexOutOfRange";
		}
		return this->head->data;
	}

	T GetLast() const
	{
		if (this->GetLength() == 0)
		{
			throw  "IndexOutOfRange";
		}
		return this->tail->data;
	}


	T Get(int index) const
	{

		if (index >= this->GetLength() or index < 0)
		{
			throw  "IndexOutOfRange";
		}

		ShrdPtr<Node<T>> elem = head;
		for (int i = 0; i < index; i++)
		{
			elem = elem->next;
		}
		return elem->data;
	}

	int GetLength() const
	{
		return this->size;
	}

	ShrdPtr<LinkedList<T>> GetSubList(int startIndex, int endIndex) const
	{
		if (startIndex >= this->GetLength() || startIndex < 0 || endIndex >= this->GetLength() || endIndex < 0)
		{
			throw std::out_of_range("Index out of range");
		}

		ShrdPtr<LinkedList<T>> sub_list(new LinkedList<T>());

		ShrdPtr<Node<T>> elem = this->head;
		for (int i = 0; i <= endIndex; i++)
		{
			if (i >= startIndex)
			{
				sub_list->Append(elem->data);
			}
			elem = elem->next;
		}
		return sub_list;
	}



	void Append(const T& item)
	{
		Node<T>* p = new Node<T>(item);

		p->prev = this->tail;

		if (tail != NULL)
		{
			this->tail->next = p;
		}
		else
		{
			this->head = p;
		}
		this->tail = p;
		this->size += 1;
	}

	void Prepend(const T& item)
	{
		Node<T>* p = new Node<T>(item);
		p->next = head;
		if (this->head != NULL)
		{
			this->head->prev = p;
		}
		else
		{
			this->tail = p;
		}
		this->head = p;
		this->size += 1;
	}

	void InsertAt(const T& item, int index)
	{
		if (index >= this->GetLength() or index <= 0)
		{
			throw  "IndexOutOfRange";
		}
		ShrdPtr<Node<T>> right = head;
		for (int i = 0; i < index; i++)
		{
			right = right->next;
		}
		if (right == NULL)
		{
			this->Append(item);
		}
		ShrdPtr<Node<T>> left = right->prev;

		if (right == NULL)
		{
			this->Prepend(item);
		}
		ShrdPtr < Node<T>> p = new Node<T>(item);
		p->prev = left;
		p->next = right;
		left->next = p;
		right->prev = p;
		this->size += 1;
	}
};

