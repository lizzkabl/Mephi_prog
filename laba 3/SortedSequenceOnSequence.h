#pragma once
#include "ArraySequenceMutable.h"
#include "ISortedSequence.h"

template <class T>
class SortedSequenceOnSequence: public ISortedSequence<T>
{
private:
	ArraySequenceMutable<T> data;
	Comparator<T> comp;
	Comparator<T> is_equal;
public: 
	SortedSequenceOnSequence():
		comp{ std::less<T>() },
		is_equal{ std::equal_to<T>() } {}

	SortedSequenceOnSequence(const SortedSequenceOnSequence<T>& other,
							Comparator<T> comp = std::less<T>(),
							Comparator<T> is_equal = std::equal_to<T>()):
		data{ other.data },
		comp{ comp },
		is_equal{ is_equal } {}


	SortedSequenceOnSequence(const ArraySequenceMutable<T>& other,
							Comparator<T> comp = std::less<T>(),
							Comparator<T> is_equal = std::equal_to<T>()):
		comp{ comp },
		is_equal{ is_equal }
	{
		for (size_t i = 0; i < other.GetLength(); i++)
		{
			Add(other.Get(i));
		}
	}

	int GetLength() const override
	{
		return data.GetLength();
	}

	bool IsEmpty() const override
	{
		return data.GetLength()==0;
	}

	T Get(int index) const override
	{
		return data.Get(index);
	}

	T GetFirst() const override
	{
		return data.GetFirst();
	}

	T GetLast() const override 
	{
		return data.GetLast();
	}

	int IndexOf(T element) const override  
	{
		for (int i = 0; i < data.GetLength(); i++)
		{
			if (data.Get(i) == element)
			{
				return i;
			}
		}
		throw  "ElementOutOfRange";
	}

	SortedSequenceOnSequence<T>* GetSubsequence(int start_index, int end_index) const override
	{
		return new SortedSequenceOnSequence(*(data.GetSubsequence(start_index, end_index)));
	}

	void Add(T element) override
	{
		if (IsEmpty() || comp(element, data.Get(0)))
		{
			data.Prepend(element);
			return;
		}

		for (size_t i = 0; i < data.GetLength(); i++)
		{
			if (comp(element, data.Get(i)))
			{
				data.InsertAt(element, i);
				return;
			}
		}
		data.Append(element);
	}



	bool BinarySearch(T element) const
	{
		int left = 0;
		int right = data.GetLength() - 1;

		while (left <= right)
		{
			int mid = left + (right - left) / 2;

			if (is_equal(element, data.Get(mid)))
			{
				return true; 
			}

			if (comp(element, data.Get(mid)))
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1; 
			}
		}
		return false; 
	}

	bool operator==(const SortedSequenceOnSequence<T>& other) const
	{
		if (GetLength() != other.GetLength())
		{
			return false;
		}
		for (size_t i = 0; i < GetLength(); i++)
		{
			if (!is_equal(Get(i), other.Get(i)))
			{
				return false;
			}
		}
		return true;
	}


	void Clear()
	{
		data.Clear();
	}
	void Swap(int i, int j)
	{
		data.Swap(i, j);
	}
};