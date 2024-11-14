#pragma once
#include "C:\Users\user\source\repos\WindowsProject1_help\ListSequenceMutable.h"
#include "ISort.h"
#include "C:\Users\user\source\repos\WindowsProject1_help\ShrdPtr.h"
#include <functional>

template <class T>
using Comparator = std::function<bool(const T&, const T&)>;

template <class T>
class QuickSort : public ISort<T>
{
private:
    int Partition(ShrdPtr<ListSequenceMutable<T>> seq, int low, int high, Comparator<T> comp, Comparator<T> isEqual)
    {
        T pivot = seq->Get(high);
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (comp(seq->Get(j), pivot) || isEqual(seq->Get(j), pivot))
            {
                i++;
                seq->Swap(i, j);
            }
        }
        seq->Swap(i + 1, high);
        return i + 1;
    }

    int PartitionShow(ShrdPtr<ListSequenceMutable<T>> seq, int low, int high, HWND hWnd, Comparator<T> comp, Comparator<T> isEqual)
    {
        T pivot = seq->Get(high);
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (comp(seq->Get(j), pivot) || isEqual(seq->Get(j), pivot))
            {
                i++;
                if (!isEqual(seq->Get(j), seq->Get(i)))
                {
                    VisualizeCurrentState(hWnd, seq, i, j);
                    Sleep(1500);
                    seq->Swap(i, j);
                    VisualizeCurrentState(hWnd, seq, i, j);
                    Sleep(1500);
                }
            }
        }
        if (!isEqual(seq->Get(i + 1), seq->Get(high)))
        {
            VisualizeCurrentState(hWnd, seq, i + 1, high);
            Sleep(1500);
            seq->Swap(i + 1, high);
            VisualizeCurrentState(hWnd, seq, i + 1, high);
            Sleep(1500);
        }
        return i + 1;
    }

    void QSort(ShrdPtr<ListSequenceMutable<T>> seq, int low, int high, Comparator<T> comp, Comparator<T> isEqual)
    {
        if (low < high)
        {
            int pi = Partition(seq, low, high, comp, isEqual);
            QSort(seq, low, pi - 1, comp, isEqual);
            QSort(seq, pi + 1, high, comp, isEqual);
        }
    }

    void QSortShow(ShrdPtr<ListSequenceMutable<T>> seq, int low, int high, HWND hWnd, Comparator<T> comp, Comparator<T> isEqual)
    {
        if (low < high)
        {
            int pi = PartitionShow(seq, low, high, hWnd, comp, isEqual);
            QSortShow(seq, low, pi - 1, hWnd, comp, isEqual);
            QSortShow(seq, pi + 1, high, hWnd, comp, isEqual);
        }
    }

public:
    void Sort(ShrdPtr<ListSequenceMutable<T>> seq, Comparator<T> comp = std::less<T>(), Comparator<T> isEqual = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size != 0)
        {
            QSort(seq, 0, size - 1, comp, isEqual);
        }
    }

    void ShowSort(ShrdPtr<ListSequenceMutable<T>> seq, HWND hWnd, Comparator<T> comp = std::less<T>(), Comparator<T> isEqual = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size != 0)
        {
            QSortShow(seq, 0, size - 1, hWnd, comp, isEqual);
        }
    }
};


/*O(n*log(n))
QuickSort — это алгоритм сортировки на основе сравнения,
который использует подход «разделяй и властвуй» для сортировки массива или списка элементов. 
Его можно реализовать с помощью двух функций:

partition(): Это ключевой процесс в алгоритме быстрой сортировки. 
Он включает выбор опорного элемента и переупорядочивание массива таким образом, 
чтобы все элементы, меньшие опорного, размещались слева, а элементы, большие опорного, размещались справа. 
Точка, в которой размещается опорный элемент, называется индексом разбиения и возвращается вызывающему его quickSort ().
quickSort (): Это основная рекурсивная функция, реализующая стратегию «разделяй и властвуй». 
Она делит заданный массив на два подмассива на основе индекса разбиения, возвращаемого функцией partition (). 
Затем она продолжает вызывать себя для этих двух подмассивов, пока весь массив не будет отсортирован.
*/