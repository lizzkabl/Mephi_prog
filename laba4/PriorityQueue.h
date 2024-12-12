#pragma once
#include "MutableSequence.h"
#include <stdexcept>

template <class T, class K>
class PriorityQueue : public MutableSequence<T>
{
private:
    struct Item
    {
        T value;
        K priority;
    };

    Item* elements;
    int size;
    int capacity;

    void EnsureCapacity()
    {
        if (size >= capacity)
        {
            capacity *= 2;
            Item* new_elem = new Item[capacity];
            for (int i = 0; i < size; ++i) {
                new_elem[i] = elements[i];
            }
            delete[] elements;
            elements = new_elem;
        }
    }

    T GetFirst() const override
    {
        if (size == 0)
        {
            throw std::out_of_range("Queue is empty");
        }
        return elements[0].value;
    }

    T GetLast() const override
    {
        if (size == 0)
        {
            throw std::out_of_range("Queue is empty");
        }
        return elements[size - 1].value;
    }

    T Get(int index) const override
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return elements[index].value;
    }

    void ShiftUp(int index)
    {
        while (index > 0 && elements[index].priority < elements[(index - 1) / 2].priority)
        {
            Swap(index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }

    void ShiftDown(int index)
    {
        int min_ind = index;
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;

        if (left_child < size && elements[left_child].priority < elements[min_ind].priority)
        {
            min_ind = left_child;
        }

        if (right_child < size && elements[right_child].priority < elements[min_ind].priority)
        {
            min_ind = right_child;
        }

        if (index != min_ind)
        {
            Swap(index, min_ind);
            ShiftDown(min_ind);
        }
    }

    void Append(const T& item) override
    {
        Enqueue(item, K());
    }

    void Prepend(const T& item) override
    {
        Enqueue(item, K());
    }

    void InsertAt(const T& item, int index) override
    {
        if (index < 0 || index >= size)
        {
            throw std::invalid_argument("Invalid index");
        }
        Enqueue(item, K());
    }

public:
    PriorityQueue(int init_capacity = 10) : size(0), capacity(init_capacity)
    {
        elements = new Item[capacity];
    }

    PriorityQueue(const PriorityQueue<T, K>& other) : size(other.size), capacity(other.capacity)
    {
        elements = new Item[capacity];
        for (int i = 0; i < size; ++i)
        {
            elements[i] = other.elements[i];
        }
    }

    PriorityQueue(const T* array, const K* priorities, int length)
        : size(length), capacity(length)
    {
        elements = new Item[capacity];
        for (int i = 0; i < size; ++i)
        {
            elements[i].value = array[i];
            elements[i].priority = priorities[i];
        }

        for (int i = (size / 2) - 1; i >= 0; --i)
        {
            ShiftDown(i);
        }
    }

    ~PriorityQueue()
    {
        delete[] elements;
    }

    MutableSequence<T>* GetSubsequence(const int startIndex, const int endIndex) const override
    {
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex)
        {
            throw std::invalid_argument("Invalid indices for subsequence");
        }

        PriorityQueue<T, K>* subsequence = new PriorityQueue<T, K>(endIndex - startIndex + 1);

        for (int i = startIndex; i <= endIndex; ++i)
        {
            subsequence->Enqueue(elements[i].value, elements[i].priority);
        }

        return subsequence;
    }

    int GetLength() const override
    {
        return size;
    }

    void Swap(int i, int j) override
    {
        Item temp = elements[i];
        elements[i] = elements[j];
        elements[j] = temp;
    }

    T Peek(int index) const 
    {
        return Get(index);
    }

    T PeekFirst() const 
    {
        if (size == 0)
        {
            throw std::out_of_range("Queue is empty");
        }
        return GetFirst();
    }

    T PeekLast() const 
    {
        if (size == 0)
        {
            throw std::out_of_range("Queue is empty");
        }
        return GetLast();
    }

    void Enqueue(T item, K priority) 
    {
        EnsureCapacity();
        elements[size].value = item;
        elements[size].priority = priority;
        ++size;
        ShiftUp(size - 1);
    }

    T Dequeue()
    {
        if (size == 0)
        {
            throw std::out_of_range("Queue is empty");
        }
        T result = elements[0].value;
        elements[0] = elements[size - 1];
        --size;
        ShiftDown(0);
        return result;
    }
};
