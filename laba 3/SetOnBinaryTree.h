#pragma once
#include "BinaryTree.h"
#include "ISet.h"
#include <exception>

template <class T>
class SetOnBinaryTree : public ISet<T>
{
private:
	BinaryTree<T> data;
	Comparator<T> comp;
	Comparator<T> is_equal;

public:
	SetOnBinaryTree() :
		comp{ std::less<T>() },
		is_equal{ std::equal_to<T>() } {}

	SetOnBinaryTree(const SetOnBinaryTree<T>& other,
		Comparator<T> comp = std::less<T>(),
		Comparator<T> is_equal = std::equal_to<T>()) :
		data{ other.data },
		comp{ comp },
		is_equal{ is_equal } {}

	SetOnBinaryTree(const BinaryTree<T>& other,
		Comparator<T> comp = std::less<T>(),
		Comparator<T> is_equal = std::equal_to<T>()) :
		data{ BinaryTree<T>() },
		comp{ comp },
		is_equal{ is_equal }
	{
		size_t size = other.GetLength();
		for (size_t i = 0; i < size; i++)
		{
			try
			{
				this->Insert(other.Get(i));
			}
			catch(...){}
		}
	}

	bool Empty() const override
	{
		return data.IsEmpty();
	}

	void Insert(T element) override
	{
		data.Insert(element);
	}

	T Get(int index) const override
	{
		if (index < 0)
		{
			throw std::out_of_range("Index must be non-negative.");
		}
		return data.Get( index);
	}

	void Pop(T element) override
	{
		data.DeleteNode(element);
	}

	int GetLength() const override
	{
		return data.GetLength();
	}

	bool Contains(T element) const override
	{
		try
		{
			data.Search(element);
			return true;
		}
		catch (...) 
		{
			return false;
		}
	}

	bool SubSet(ISet<T>* set) const override
	{
		for (int i = 1; i < set->GetLength() * set->GetLength(); i++)
		{
			try
			{
				if (!Contains(set->Get(i)))
				{
					return false;
				}
			}
			catch(...){}
		}
		return true;
	}

};