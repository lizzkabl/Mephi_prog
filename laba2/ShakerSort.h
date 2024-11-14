#pragma once
#include "C:\Users\user\source\repos\WindowsProject1_help\ListSequenceMutable.h"
#include "ISort.h"
#include "C:\Users\user\source\repos\WindowsProject1_help\ShrdPtr.h"
#include <functional>

template <class T>
using Comparator = std::function<bool(const T&, const T&)>;

template <class T>
class ShakerSort : public ISort<T>
{
public:
    ShakerSort() = default;

    void Sort(ShrdPtr<ListSequenceMutable<T>> seq,
        Comparator<T> comp = std::less<T>(), Comparator<T> isEqual = std::equal_to<T>()) override
	{
        size_t size = seq->GetLength();
        if (size <= 1) return;

        int left = 0;
        int right = size - 1;

        while (left < right)
        {
            for (int j = left; j < right; j++)
            {
                if (comp(seq->Get(j + 1), seq->Get(j)))
                {
                    seq->Swap(j, j + 1);
                }
            }
            right--;

            for (int j = right; j > left; j--)
            {
                if (comp(seq->Get(j), seq->Get(j - 1)))
                {
                    seq->Swap(j, j - 1);
                }
            }
            left++;
        }
    }

    void ShowSort(ShrdPtr<ListSequenceMutable<T>> seq, HWND hWnd,
        Comparator<T> comp = std::less<T>(),
        Comparator<T> isEqual = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size <= 1) return;  

        int left = 0;
        int right = size - 1;

        while (left < right)
        {
            for (int j = left; j < right; j++)
            {
                if (comp(seq->Get(j + 1), seq->Get(j)))
                {
                    VisualizeCurrentState(hWnd, seq, j, j + 1);
                    Sleep(700); 

                    seq->Swap(j, j + 1);

                    VisualizeCurrentState(hWnd, seq, j, j + 1);
                    Sleep(700);
                }
            }
            right--;  

            for (int j = right; j > left; j--)
            {
                if (comp(seq->Get(j), seq->Get(j - 1)))
                {
                    VisualizeCurrentState(hWnd, seq, j, j - 1);
                    Sleep(700);

                    seq->Swap(j, j - 1);

                    VisualizeCurrentState(hWnd, seq, j, j - 1);
                    Sleep(700);
                }
            }
            left++;
        }
    }

	
};
/*O(n²)
Первый этап проходит по массиву слева направо, как и сортировка пузырьком. 
Во время цикла сравниваются соседние элементы, и если значение слева больше значения справа, то значения меняются местами. 
В конце первой итерации наибольшее число будет находиться в конце массива.
Второй этап проходит по массиву в обратном направлении — начиная с элемента, 
который находится прямо перед последним отсортированным элементом, и возвращаясь к началу массива. 
Здесь также сравниваются соседние элементы и при необходимости меняются местами.
*/