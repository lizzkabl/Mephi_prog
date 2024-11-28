#pragma once
#include <stdexcept>
#include "MutableSequence.h"
#include "DynamicArray.h"
#include <iostream>

template <class T>
class ArraySequenceMutable :public  MutableSequence <T>
{
	private:
		DynamicArray<T> items;
		Comparator<T> is_equal;
public:
	ArraySequenceMutable(const ArraySequenceMutable& other)
		: items{ other.items }, is_equal{ other.is_equal } {}


	ArraySequenceMutable& operator=(const ArraySequenceMutable& other) 
	{
		items = other.items;
		is_equal = other.is_equal;
		return *this;
	}

	ArraySequenceMutable() :items{ DynamicArray<T>() }, is_equal{ std::equal_to<T>() } {}

	ArraySequenceMutable(const DynamicArray <T>& other) : items{ other}, is_equal{ std::equal_to<T>() } {}

	ArraySequenceMutable(const T& other) : items{ other }, is_equal{ std::equal_to<T>() } {}

	ArraySequenceMutable(const T* item, const int count) : items{ DynamicArray<T>(item , count) }, is_equal{ std::equal_to<T>() } {}

	int GetLength()  const override
	{
		return this->items.GetSize();
	}

	T GetFirst()  const override  
	{
		if (this->items.GetSize() == 0)
		{
			throw  "IndexOutOfRange";
		}
		return this->items.Get(0);
	}

	T GetLast() const override 
	{
		if (this->items.GetSize()==0)
		{
			throw  "IndexOutOfRange";
		}
		return this->items.Get(GetLength() - 1);
	}

	T Get(const int index) const override 
	{		
		if (index >= this->items.GetSize() or index<0)
		{
			throw  "IndexOutOfRange";
		}
		return this->items.Get(index);
	}

	void InsertAt(const T &item, int index) override
	{
		if (index >= this->GetLength() or index < 0)
		{
			throw  "IndexOutOfRange";
		}

		this->items.Resize(this->items.GetSize() + 1);

		for (int i = this->items.GetSize() - 1; i > index; i--)
		{
			this->items.Set(i, this->items.Get(i - 1));
		}
		this->items.Set(index, item);
	}

	ArraySequenceMutable<T>* &operator+=(const T& item)
	{
		this->items.Resize(this->items.GetSize() + 1);
		this->items.Set(this->items.GetSize() - 1, item);
		return *this;
	}

	void Append(const T &item) override
	{
		items.Append(item);
	}

	void Prepend(const T &item)  override
	{
		this->items.Resize(this->items.GetSize() + 1);


		for (int i = this->items.GetSize()-1; i > 0; i--)
		{
			this->items.Set(i, this->items.Get(i - 1));
		}

		this->items.Set(0, item);
	}

	ArraySequenceMutable<T>* GetSubsequence(const int startIndex, const  int endIndex) const override
	{
		if (startIndex >= this->items.GetSize() or startIndex < 0 or endIndex >= this->items.GetSize() or endIndex < 0)
		{
			throw  "IndexOutOfRange";
		}
		ArraySequenceMutable<T>* sub_seq = new ArraySequenceMutable<T>();
		for (int i = startIndex; i < endIndex + 1; i++)
		{
			sub_seq->Append(this->items.Get(i));
		}
		return sub_seq;
	}

	ArraySequenceMutable <T>* Concat(const MutableSequence<T>* list) const override 
	{
		DynamicArray<T> concated_array(this->items);
		for (int i = 0; i < list->GetLength(); i++)
		{
			concated_array.Append(list->Get(i));
		}
		return new ArraySequenceMutable<T> (concated_array);
	}

	void Swap(int i, int j) override
	{
		items.Swap(i, j);
	}

	void Pop(T element)
	{
		items.Pop(element);
	}
	void Clear()
	{
		items.Clear();
	}

	bool operator==(const ArraySequenceMutable<T>& other) const
	{
		if (other.GetLength() != this->GetLength())
		{
			return false;
		}
		for (int i = 0; i < GetLength(); i++)
		{
			if (!is_equal(other.Get(i), Get(i)))
			{
				return false;
			}
		}
		return true;
	}
};


