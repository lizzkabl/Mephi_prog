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

    void Release()
    {
        if (count) {
            count->DecrementWeak();
            if (count->GetMain() == 0 && count->GetWeak() == 0) 
            {
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
        Release();
    }


    WeakPtr& operator=(const WeakPtr& other)
    {
        if (this != &other) 
        {
            Release();
            ptr = other.ptr;
            count = other.count;
            if (count) count->IncrementWeak();
        }
        return *this;
    }

    WeakPtr& operator=(const ShrdPtr<T>& other)
    {
        Release();
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

    bool Expired() const
    {
        return Use_count() == 0;
    }

    ShrdPtr<T> Lock() const
    {
        return Expired() ? ShrdPtr<T>() : ShrdPtr<T>(*this);
    }

    friend class ShrdPtr<T>;
};
