#pragma once
#include "ArraySequenceMutable.h"
#include "ISet.h"
#include <exception>

template <class T>
class SetOnSequence: public ISet<T>
{
private:
	ArraySequenceMutable<T> data;
	Comparator<T> comp;
	Comparator<T> is_equal;

public:
	SetOnSequence() : 
		comp{ std::less<T>() },
		is_equal{ std::equal_to<T>() } {}


	SetOnSequence(const SetOnSequence<T>& other,
					Comparator<T> comp = std::less<T>(),
					Comparator<T> is_equal = std::equal_to<T>()):
		data{ other.data },
		comp{ comp },
		is_equal{ is_equal } {}

	SetOnSequence(const ArraySequenceMutable<T>& other,
					Comparator<T> comp = std::less<T>(),
					Comparator<T> is_equal = std::equal_to<T>()) :
		data{ ArraySequenceMutable<T>() },
		comp{ comp },
		is_equal{ is_equal }
	{
		size_t size = other.GetLength();
		for (size_t i = 0; i < size; i++)
		{
			this->Insert(other.Get(i));
		}
	}
	
	bool Empty() const override 
	{
		return data.GetLength() == 0;
	}

	void Insert(T element) override
	{
		if (Contains(element)) return; 

		size_t size = data.GetLength();
		if (size == 0 || comp(element, data.Get(0))) 
		{
			data.Prepend(element);
			return;
		}
		if (!comp(element, data.Get(size - 1)))
		{
			data.Append(element);
			return;
		}
		for (size_t i = 0; i < size - 1; i++)
		{
			if (comp(data.Get(i), element) && comp(element, data.Get(i + 1)))
			{
				data.InsertAt(element, i + 1);
				return;
			}
		}
	}	
	
	T Get(int index) const override
	{
		if (index < 0 || index >= data.GetLength())
		{
			throw std::out_of_range("Index out of range");
		}
		return data.Get(index);
	}

	void Pop(T element) override
	{
		data.Pop(element);
	}

	int GetLength() const override
	{
		return data.GetLength();
	}

	bool Contains(T element) const override
	{
		for (int i = 0; i < data.GetLength(); i++)
		{
			if (data.Get(i) == element)
			{
				return true;
			}
		}
		return false;
	}

	bool SubSet(ISet<T>* set) const override
	{
		for (int i = 0; i < set->GetLength(); i++)
		{
			bool flag = false;
			for (int j = 0; j < data.GetLength(); j++)
			{
				if (is_equal(data.Get(j), set->Get(i)))
				{
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				return false;
			}
		}
		return true;
	}
};