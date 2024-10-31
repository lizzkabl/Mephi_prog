#pragma once
#include <iostream>
#include <stdexcept>
#include "ShrdPtr.h"
#include "Counter.h"

template <typename T>
class ShrdPtr;


template <class T>
class WeakPtr
{
private:
    T* ptr;
    Counter* count;

public:
    WeakPtr() : ptr(nullptr), count(nullptr) {}

    WeakPtr(const WeakPtr& other) : ptr{ other.ptr }, count{ other.count }
    {
        if (count) (*count)++;
    }

    WeakPtr(const ShrdPtr<T>& other) : ptr{ other.ptr }, count{ other.count }
    {
        if (count) (*count)++;
    }

    ~WeakPtr()
    {
        if (count)
        {
            (*count)--;
            if (count->Get() == 0)
            {
                delete count;
            }
        }
    }

    WeakPtr& operator=(const WeakPtr& other)
    {
        if (this != &other)
        {
            reset();
            ptr = other.ptr;
            count = other.count;
            if (count) (*count)++;
        }
        return *this;
    }

    WeakPtr& operator=(const ShrdPtr<T>& other)
    {
        reset();
        ptr = other.ptr;
        count = other.count;
        if (count) (*count)++;
        return *this;
    }

    int Use_count() const
    {
        return count ? count->Get() : 0;
    }

    void reset()
    {
        if (count)
        {
            (*count)--;
            if (count->Get() == 0)
            {
                delete count;
            }
        }
        ptr = nullptr;
        count = nullptr;
    }

    void Swap(WeakPtr& other)
    {
        std::swap(ptr, other.ptr);
        std::swap(count, other.count);
    }

    bool expired() const
    {
        return Use_count() == 0;
    }

    ShrdPtr<T> lock() const
    {
        return expired() ? ShrdPtr<T>() : ShrdPtr<T>(*this);
    }

    friend class ShrdPtr<T>;
};
