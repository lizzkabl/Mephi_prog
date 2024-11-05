#pragma once
#include "C:\Users\user\source\repos\WindowsProject1_help\ListSequenceMutable.h"
#include "ISort.h"
#include "C:\Users\user\source\repos\WindowsProject1_help\ShrdPtr.h"
#include <iostream>
template <class T>
class QuickSort : public ISort<T>
{
private:
	bool (*compare)(const T&, const T&);
	bool (*is_equal)(const T&, const T&);
	bool (*is_not_equal)(const T&, const T&);

public:
	QuickSort(bool (*comp)(const T&, const T&), bool (*is_equal)(const T&, const T&), bool (*is_not_equal)(const T&, const T&)) : compare(comp), is_equal(is_equal), is_not_equal(is_not_equal){}
	
	void Sort(ShrdPtr<ListSequenceMutable<T>> seq) override
	{
        for (int i = 0; i < seq->GetLength() - 1; ++i)
		{
            for (int j = 0; j < seq->GetLength() - i - 1; ++j)
			{
                if (!compare(seq->Get(j), seq->Get(j+1)) )
				{
					seq->Swap(j, j+1);
                }
            }
        }
	}
};