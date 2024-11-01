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

    void release()
    {
        if (count) {
            count->DecrementWeak();
            if (count->GetMain() == 0 && count->GetWeak() == 0) {
                delete count;
                count = nullptr;
            }
        }
    }

public:
    WeakPtr() : ptr(nullptr), count(nullptr) {}

    WeakPtr(const WeakPtr& other) : ptr{ other.ptr }, count{ other.count }
    {
        if (count)
        {
            count->IncrementWeak();
        }
    }

    WeakPtr(const ShrdPtr<T>& other) : ptr{ other.ptr }, count{ other.count }
    {
        if (count)
        {
            count->IncrementWeak();
        }
    }

    ~WeakPtr()
    {
        release();
    }


    WeakPtr& operator=(const WeakPtr& other)
    {
        if (this != &other) 
        {
            release();
            ptr = other.ptr;
            count = other.count;
            if (count) count->IncrementWeak();
        }
        return *this;
    }

    WeakPtr& operator=(const ShrdPtr<T>& other)
    {
        release();
        ptr = other.ptr;
        count = other.count;
        if (count) count->IncrementWeak();
        return *this;
    }

    int Use_count() const
    {
        return count ? count->GetMain() : 0;
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
