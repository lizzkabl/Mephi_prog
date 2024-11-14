//#pragma once
//#include "framework.h"
//#include <functional>
//template <class T>
//class ISort
//{
//public: 
//	virtual void Sort(ShrdPtr<ListSequenceMutable<T>> seq,
//		Comparator<T> comp = std::less<T>(), Comparator<T> is_equal = std::equal_to<T>(), bool visualize = false, HWND hWnd = nullptr) = 0;
//
//	virtual void ShowSort(ShrdPtr<ListSequenceMutable<T>> seq, HWND hWnd,
//		Comparator<T> comp = std::less<T>(),
//		Comparator<T> is_equal = std::equal_to<T>()) = 0;
//};

#pragma once
#include <functional>
#include "framework.h"

template <class T>
using Comparator = std::function<bool(const T&, const T&)>;

template <class T>
class ISort
{
public:
    virtual void Sort(
        ShrdPtr<MutableSequence<T>> seq,
        Comparator<T> comp = std::less<T>(),
        Comparator<T> is_equal = std::equal_to<T>()) = 0;

    virtual void ShowSort(
        ShrdPtr<MutableSequence<T>> seq,
        HWND hWnd,
        Comparator<T> comp = std::less<T>(),
        Comparator<T> is_equal = std::equal_to<T>()) = 0;
};
