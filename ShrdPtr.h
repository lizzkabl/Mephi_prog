#pragma once
#include <iostream>
#include <stdexcept>
#include "WeakPtr.h"
#include "Counter.h"

template <typename T>
class WeakPtr;

template <class T>
class ShrdPtr
{
private:
    T* ptr;
    Counter* count;

public:
    ShrdPtr() : ptr{ nullptr }, count{ nullptr } {}

    ShrdPtr(T* other) : ptr{ other }
    {
        count = new Counter();
        (*count)++;
    }

    ShrdPtr(const ShrdPtr<T>& other) : ptr{ other.ptr }, count{ other.count }
    {
        if (count) (*count)++;
    }

    ShrdPtr(const WeakPtr<T>& other) : ptr{ other.ptr }
    {
        count = other.count;
        (*count)++;
    }

    ~ShrdPtr() {
        if (count != nullptr && ptr != nullptr) {
            (*count)--;
            if (count->Get() == 0) 
            {
                delete ptr;
                delete count;
            }
        }
    }

    T& operator*() const
    {
        return *ptr;
    }
    T* operator->() const
    {
        return ptr;
    }
    T* Get() const
    {
        return ptr;
    }

    ShrdPtr& operator=(const ShrdPtr& other)
    {
        if (this != &other)
        {
            if (count)
            {
                (*count)--;
                if (count->Get() == 0)
                {
                    delete ptr;
                    delete count;
                }
            }
            ptr = other.ptr;
            count = other.count;
            if (count) (*count)++;
        }
        return *this;
    }

    ShrdPtr& operator=(T* other)
    {
        count = new Counter();
        (*count)++;
        ptr = other;
        return *this;
    }

    int Use_count() const
    {
        return count ? count->Get() : 0;
    }

    void Swap(ShrdPtr<T>& other)
    {
        std::swap(ptr, other.ptr);
        std::swap(count, other.count);
    }

    explicit operator bool() const
    {
        return ptr != nullptr;
    }

    bool operator!() const
    {
        return ptr == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return ptr != nullptr;
    }

    bool operator==(std::nullptr_t) const
    {
        return ptr == nullptr;
    }

    friend class WeakPtr<T>;
};


