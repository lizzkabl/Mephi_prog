#pragma once
#include "MutableSequence.h"
#include "LinkedList.h"
#include "ShrdPtr.h"
#include <iostream>

template <class T>
class ListSequenceMutable : public MutableSequence<T>
{
private:
    ShrdPtr<LinkedList<T>> items;

public:
    ListSequenceMutable() : items{ LinkedList<T>() } {}
    ListSequenceMutable(ShrdPtr<LinkedList<T>>&& other) : items{ std::move(other) } {}
    ListSequenceMutable(T* item, int count) : items{ new LinkedList<T>(item, count) } {}
    ListSequenceMutable(const LinkedList<T>& other) : items{ LinkedList<T>(other) } {}

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

    //ShrdPtr<ListSequenceMutable<T>> GetSubsequence(const int start_index, const int end_index) const
    //{
    //    return ShrdPtr<ListSequenceMutable<T>>(new ListSequenceMutable<T>(this->items->GetSubList(start_index, end_index)));
    //}

    ShrdPtr<ListSequenceMutable<T>> GetSubsequence(const int start_index, const int end_index) const
    {
        ShrdPtr<LinkedList<T>> sub_list = this->items->GetSubList(start_index, end_index);
        return ShrdPtr<ListSequenceMutable<T>>(new ListSequenceMutable<T>(std::move(sub_list)));
    }

};
