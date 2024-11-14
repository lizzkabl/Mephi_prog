#pragma once
#include "C:\Users\user\source\repos\WindowsProject1_help\ListSequenceMutable.h"
#include "ISort.h"
#include "C:\Users\user\source\repos\WindowsProject1_help\ShrdPtr.h"
#include <functional>
#include "framework.h"

template <class T>
using Comparator = std::function<bool(const T&, const T&)>;

template <class T>
class BubleSort : public ISort<T>
{
public:
    BubleSort() = default;

    void Sort(ShrdPtr<ListSequenceMutable<T>> seq,
        Comparator<T> comp = std::less<T>(), Comparator<T> isEqual = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size != 0)
        {
            for (int i = 0; i < size - 1; ++i)
            {
                for (int j = 0; j < size - i - 1; ++j)
                {
                    if (!comp(seq->Get(j), seq->Get(j + 1)))
                    {
                        seq->Swap(j, j + 1);
                    }
                }
            }
        }
    }
    void ShowSort(ShrdPtr<ListSequenceMutable<T>> seq, HWND hWnd,
        Comparator<T> comp = std::less<T>(),
        Comparator<T> isEqual = std::equal_to<T>()) override
    {
        size_t size = seq->GetLength();
        if (size != 0)
        {
            for (int i = 0; i < size - 1; i++)
            {
                for (int j = 0; j < size - i - 1; j++)
                {
                    if (!comp(seq->Get(j), seq->Get(j + 1)) && !isEqual(seq->Get(j), seq->Get(j + 1)))
                    {
                        VisualizeCurrentState(hWnd, seq, j, j + 1);
                        Sleep(1500);

                        seq->Swap(j, j + 1);

                        VisualizeCurrentState(hWnd, seq, j, j + 1);
                        Sleep(1500);
                    }
                }
            }
        }
    }
};


/*O(n²)
Мы сортируем массив, используя несколько проходов.
После первого прохода максимальный элемент перемещается в конец (его правильная позиция).
Точно так же после второго прохода второй по величине элемент перемещается в предпоследнюю позицию и так далее.
В каждом проходе мы обрабатываем только те элементы, которые еще не переместились в правильное положение.
После k проходов самые большие k элементов должны быть перемещены в последние k позиций.
В проходе мы рассматриваем оставшиеся элементы и сравниваем все смежные и меняем местами,
если больший элемент находится перед меньшим.
Если мы продолжим делать это, мы получим наибольший (среди оставшихся элементов) в его правильной позиции.
*/