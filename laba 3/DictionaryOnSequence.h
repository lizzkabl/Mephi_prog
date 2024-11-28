#pragma once
#include "IDictionary.h"
#include "ArraySequenceMutable.h"
template <class K, class T>
class DictionaryOnSequence : IDictionary<K, T>
{
private:
	ArraySequenceMutable<K> key;
	ArraySequenceMutable<T> data;

	Comparator<K> is_equal_K;

public:
	DictionaryOnSequence():
		is_equal_K{ std::equal_to<K>() }  {}


	DictionaryOnSequence(const DictionaryOnSequence<K, T>& other):
		key{ other.key },
		data{ other.data },
		is_equal_K{ other.is_equal_K } {}


	DictionaryOnSequence(const K other_k, const T other_el):
		key{ ArraySequenceMutable<K>(other_k) },
		data{ ArraySequenceMutable<T>(other_el) },
		is_equal_K{ std::equal_to<K>() } 
	{
		if (other_k.GetLength() != other_el.GetLength())
		{
			throw std::invalid_argument("Keys and values must have the same length");
		}
	}

	DictionaryOnSequence(const ArraySequenceMutable<K> k, const ArraySequenceMutable<T> el):
		key{ k },
		data{ el },
		is_equal_K{ std::equal_to<K>() } {}
	
	int GetCount() const override
	{
		return key.GetLength();
	}

	int GetCapacity() const override
	{
		return 0; //ArraySequenceMutable have been written without capacity, so when one elements adds it's changes
	}

	T Get(K k) const
	{
		for (int i = 0; i < key.GetLength(); i++)
		{
			if (is_equal_K(key.Get(i), k))
			{
				return data.Get(i);
			}
		}
		throw "KeyOutOfRange";
	}

	bool ContainsKey(K k) const
	{
		for (int i = 0; i < key.GetLength(); i++)
		{
			if (is_equal_K(key.Get(i), k))
			{
				return true;
			}
		}
		return false;
	}

	void Add(K k, T el)
	{
		if (!ContainsKey(k))
		{
			key.Append(k);
			data.Append(el);
		}
		else 
		{
			throw "KeyAlreadyExist";
		}
	}

	void Remove(K k)
	{
		for (int i = 0; i < key.GetLength(); i++)
		{
			if (is_equal_K(key.Get(i), k))
			{
				key.Pop(k);
				data.Pop(data.Get(i));
				break;
			}
		}
	}
};