#pragma once
#include "MutableSequence.h"
#include "LinkedList.h"
#include "ShrdPtr.h"
#include <vector>

template <class T>
class ListSequenceMutable : public MutableSequence<T>
{
private:
    ShrdPtr<LinkedList<T>> items;
public:
    ListSequenceMutable() : items{ new LinkedList<T>() } {}
    ListSequenceMutable(ShrdPtr<LinkedList<T>>&& other) : items{ std::move(other) } {}
    ListSequenceMutable(T* item, int count) : items{ new LinkedList<T>(item, count) } {}
    ListSequenceMutable(const LinkedList<T>& other) : items{ LinkedList<T>(other) } {}
    ListSequenceMutable(T elem, int count) : items{ new LinkedList<T>(count, elem) } {}
    ListSequenceMutable(const ListSequenceMutable<T>& other): items{ new LinkedList<T>(*other.items) } {}

    T GetFirst() const override
    {
        return this->items->GetFirst();
    }

    T GetLast() const override
    {
        return this->items->GetLast();
    }

    T Get(const int index) const override
    {
        return this->items->Get(index);
    }

    int GetLength() const override
    {
        return this->items->GetLength();
    }

    void Append(const T& item) override
    {
        this->items->Append(item);
    }

    void Prepend(const T& item) override
    {
        this->items->Prepend(item);
    }

    void InsertAt(const T& item, const int index) override
    {
        this->items->InsertAt(item, index);
    }

    ShrdPtr<ListSequenceMutable<T>> GetSubsequence(const int start_index, const int end_index) const
    {
        ShrdPtr<LinkedList<T>> sub_list = this->items->GetSubList(start_index, end_index);
        return ShrdPtr<ListSequenceMutable<T>>(new ListSequenceMutable<T>(std::move(sub_list)));
    }
    void Swap(int n1, int n2)
    {
        this->items->Swap(n1, n2);
    }

    void Merge(const ListSequenceMutable<T>& other)
    {
        for (int i = 0; i < other.GetLength(); i++)
        {
            this->Append(other.Get(i));
        }
    }
};
