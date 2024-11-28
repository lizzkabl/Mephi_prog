#pragma once
#include "SortedSequenceOnSequence.h"
#include "DictionaryOnSequence.h"
#include <functional>
template <class T>
using Comparator = std::function<bool(const T&, const T&)>;

template <class T>
class Histogram
{
public:
	Histogram() = default;
	DictionaryOnSequence<int, T> CreateHistogram(SortedSequenceOnSequence<T> seq, int range, Comparator<T> comp = std::less<T>())
	{
		if (seq.GetLength() == 0)
		{
			throw std::runtime_error("Sequence is empty.");
		}
		else if (range <1)
		{
			throw std::runtime_error("Range must be greater than zero.");
		}
		int ind=0;
		int start = 0;
		DictionaryOnSequence<int, T> dict;
		for (int i = 0; i < seq.GetLength(); i++)
		{
			if (comp(seq.Get(start) + range-1, seq.Get(i)))
			{
				dict.Add(ind, start);
				ind++;
				start = i;
			}
		}
		dict.Add(ind, start);
		return dict;
	}

	void PrintHistogram(std::ostream& out, DictionaryOnSequence<int, T>& dict, int length)
	{
		for (int i = 0; i < dict.GetCount() - 1; i++)
		{
			out << "set " << i << " ";
			for (int j = 0; j < (-dict.Get(i) + dict.Get(i + 1)); j++)
			{
				out << "o";
			}
			out << "\n";
		}

		out << "set " << dict.GetCount() - 1 << " ";
		for (int j = dict.Get(dict.GetCount() - 1); j < length; j++)
		{
			out << "o";
		}
		out << "\n";
	}



};