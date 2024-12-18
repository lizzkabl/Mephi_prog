#pragma once
#include "ListSequenceMutable.h"
#include "ISort.h"
#include "ShrdPtr.h"
#include <functional>



template <class T>
class QuickSort : public ISort<T>
{
private:
    int Partition(ShrdPtr<MutableSequence<T>> seq, int low, int high, Comparator<T> comp, Comparator<T> is_equal)
    {
        T pivot = seq->Get(high);
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (comp(seq->Get(j), pivot) || is_equal(seq->Get(j), pivot))
            {
                i++;
                seq->Swap(i, j);
            }
        }
        seq->Swap(i + 1, high);
        return i + 1;
    }

    int PartitionShow(ShrdPtr<MutableSequence<T>> seq, int low, int high, HWND hWnd, Comparator<T> comp, Comparator<T> is_equal)
    {
        T pivot = seq->Get(high);
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (comp(seq->Get(j), pivot) || is_equal(seq->Get(j), pivot))
            {
                i++;
                if (!is_equal(seq->Get(j), seq->Get(i)))
                {
                    VisualizeCurrentState(hWnd, seq, i, j);
                    Sleep(1500);
                    seq->Swap(i, j);
                    VisualizeCurrentState(hWnd, seq, i, j);
                    Sleep(1500);
                }
            }
        }
        if (!is_equal(seq->Get(i + 1), seq->Get(high)))
        {
            VisualizeCurrentState(hWnd, seq, i + 1, high);
            Sleep(1500);
            seq->Swap(i + 1, high);
            VisualizeCurrentState(hWnd, seq, i + 1, high);
            Sleep(1500);
        }
        return i + 1;
    }

    void QSort(ShrdPtr<MutableSequence<T>> seq, int low, int high, Comparator<T> comp, Comparator<T> is_equal)
    {
        if (low < high)
        {
            int pi = Partition(seq, low, high, comp, is_equal);
            QSort(seq, low, pi - 1, comp, is_equal);
            QSort(seq, pi + 1, high, comp, is_equal);
        }
    }

    void QSortShow(ShrdPtr<MutableSequence<T>> seq, int low, int high, HWND hWnd, Comparator<T> comp, Comparator<T> is_equal)
    {
        if (low < high)
        {
            int pi = PartitionShow(seq, low, high, hWnd, comp, is_equal);
            QSortShow(seq, low, pi - 1, hWnd, comp, is_equal);
            QSortShow(seq, pi + 1, high, hWnd, comp, is_equal);
        }
    }

public:
    void Sort(ShrdPtr<MutableSequence<T>> seq, Comparator<T> comp = std::less<T>(), Comparator<T> is_equal = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size != 0)
        {
            QSort(seq, 0, size - 1, comp, is_equal);
        }
    }

    void ShowSort(ShrdPtr<MutableSequence<T>> seq, HWND hWnd, Comparator<T> comp = std::less<T>(), Comparator<T> is_equal = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size != 0)
        {
            QSortShow(seq, 0, size - 1, hWnd, comp, is_equal);
        }
    }
};


/*O(n*log(n))
QuickSort � ��� �������� ���������� �� ������ ���������,
������� ���������� ������ ��������� � �������� ��� ���������� ������� ��� ������ ���������. 
��� ����� ����������� � ������� ���� �������:

partition(): ��� �������� ������� � ��������� ������� ����������. 
�� �������� ����� �������� �������� � ������������������ ������� ����� �������, 
����� ��� ��������, ������� ��������, ����������� �����, � ��������, ������� ��������, ����������� ������. 
�����, � ������� ����������� ������� �������, ���������� �������� ��������� � ������������ ����������� ��� quickSort ().
quickSort (): ��� �������� ����������� �������, ����������� ��������� ��������� � ��������. 
��� ����� �������� ������ �� ��� ���������� �� ������ ������� ���������, ������������� �������� partition (). 
����� ��� ���������� �������� ���� ��� ���� ���� �����������, ���� ���� ������ �� ����� ������������.
*/