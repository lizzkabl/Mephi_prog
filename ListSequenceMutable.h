#pragma once
#include "MutableSequence.h"
#include "LinkedList.h"
#include "ShrdPtr.h"
#include <iostream>

template <class T>
class ListSequenceMutable : public MutableSequence<T>
{
private:
    LinkedList<T> items;

public:
    ListSequenceMutable() : items{ LinkedList<T>() } {}
    ListSequenceMutable(T* item, int count) : items{ LinkedList<T>(item, count) } {}
    ListSequenceMutable(const LinkedList<T>& other) : items{ LinkedList<T>(other) } {}

    T GetFirst() const override
    {
        return this->items.GetFirst();
    }

    T GetLast() const override
    {
        return this->items.GetLast();
    }

    T Get(const int index) const override
    {
        return this->items.Get(index);
    }


    int GetLength() const override
    {
        return this->items.GetLength();
    }

    void Append(const T& item) override
    {
        this->items.Append(item);
    }

    void Prepend(const T& item) override
    {
        this->items.Prepend(item);
    }

    void InsertAt(const T& item, const int index) override
    {
        this->items.InsertAt(item, index);
    }

    ShrdPtr<ListSequenceMutable<T>> GetSubsequence(const int startIndex, const int endIndex) const 
    {
        ShrdPtr<LinkedList<T>> sub_list = this->items.GetSubList(startIndex, endIndex);
        return ShrdPtr<ListSequenceMutable<T>>(new ListSequenceMutable<T>(*sub_list));
    }

};
