#pragma once
#include "ListSequenceMutable.h"
#include "ISort.h"
#include "ShrdPtr.h"
#include <functional>
#include "framework.h"


template <class T>
class ImprovedSelectionSort : public ISort<T>
{
public:
    ImprovedSelectionSort() = default;

    void Sort(ShrdPtr<MutableSequence<T>> seq,
        Comparator<T> comp = std::less<T>(),
        Comparator<T> is_equal = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size != 0)
        {
            for (int i = 0, j = size - 1; i < j; i++, j--)
            {
                T min = seq->Get(i);
                T max = seq->Get(i);
                int min_i = i, max_i = i;

                for (int k = i; k <= j; k++)
                {
                    T elem = seq->Get(k);
                    if (!comp(elem, max))
                    {
                        max = elem;
                        max_i = k;
                    }
                    else if (comp(elem, min))
                    {
                        min = elem;
                        min_i = k;
                    }
                }
                seq->Swap(i, min_i);

                if (is_equal(seq->Get(min_i), max))
                {
                    seq->Swap(j, min_i);
                }
                else
                {
                    seq->Swap(j, max_i);
                }
            }
        }
    }

    void ShowSort(ShrdPtr<MutableSequence<T>> seq, HWND hWnd,
        Comparator<T> comp = std::less<T>(),
        Comparator<T> is_equal = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size != 0)
        {
            for (int i = 0, j = size - 1; i < j; i++, j--)
            {
                T min = seq->Get(i);
                T max = seq->Get(i);
                int min_i = i, max_i = i;

                for (int k = i; k <= j; k++)
                {
                    T elem = seq->Get(k);
                    if (!comp(elem, max))
                    {
                        max = elem;
                        max_i = k;
                    }
                    else if (comp(elem, min))
                    {
                        min = elem;
                        min_i = k;
                    }
                }

                if (i != min_i)
                {
                    VisualizeCurrentState(hWnd, seq, i, min_i);
                    Sleep(1500);
                    seq->Swap(i, min_i);
                    VisualizeCurrentState(hWnd, seq, i, min_i);
                    Sleep(1500);
                }

                if (is_equal(seq->Get(min_i), max))
                {
                    if (!is_equal(seq->Get(j), seq->Get(min_i)))
                    {
                        VisualizeCurrentState(hWnd, seq, j, min_i);
                        Sleep(1500);
                        seq->Swap(j, min_i);
                        VisualizeCurrentState(hWnd, seq, j, min_i);
                        Sleep(1500);
                    }
                }
                else
                {
                    if (!is_equal(seq->Get(j), seq->Get(max_i)))
                    {
                        VisualizeCurrentState(hWnd, seq, j, max_i);
                        Sleep(1500);
                        seq->Swap(j, max_i);
                        VisualizeCurrentState(hWnd, seq, j, max_i);
                        Sleep(1500);
                    }
                }
            }
        }
    }
};



/* O(n²)
Идея состоит в том, чтобы брать также максимум на каждом проходе и помещать его в правильное положение. 
Таким образом, на каждом проходе мы отслеживаем как максимум, так и минимум,
и массив становится отсортированным с обоих концов.
*/