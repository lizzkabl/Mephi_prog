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

    void release()
    {
        if (count)
        {
            count->DecrementMain();
            if (count->GetMain() == 0)
            {
                delete ptr;
                ptr = nullptr;
                if (count->GetWeak() == 0)
                {
                    delete count;
                    count = nullptr;
                }
            }
        }
    }

public:
    ShrdPtr() : ptr{ nullptr }, count{ nullptr } {}

    ShrdPtr(T* other) : ptr{ other }
    {
        count = new Counter();
        count->IncrementMain();
    }


    ShrdPtr(const ShrdPtr<T>&other) : ptr{ other.ptr }, count{ other.count }
    {
        if (count) 
        {
            count->IncrementMain();
        }
            
    }
    

    ShrdPtr(const WeakPtr<T>& other) : ptr{ other.ptr }
    {
        count = other.count;
        count->IncrementMain();
    }

    ~ShrdPtr()
    {
        release();
    }

    T& operator*() const
    {
        if (ptr) {
            return *ptr;
        }
        else {
            throw std::runtime_error("Dereferencing a null pointer.");
        }
    }

    T* operator->() const
    {
        if (ptr)
        {
            return ptr;
        }
        else
        {
            return nullptr;
        }
    }
    T* Get() const
    {
        if (ptr)
        {
            return ptr;
        }
        else
        {
            return nullptr;
        }
    }

    ShrdPtr& operator=(const ShrdPtr& other) {
        if (this != &other) 
        {
            release();
            ptr = other.ptr;
            count = other.count;
            if (count) 
            {
                count->IncrementMain();
            }
        }
        return *this;
    }


    ShrdPtr& operator=(T* other)
    {
        if (count) 
        {
            count->DecrementMain();
            if (count->GetMain() == 0) {
                delete ptr;
                if (count->GetWeak() == 0) {
                    delete count;
                }
            }
        }
        ptr = other;
        if (other) 
        {
            count = new Counter();
        }
        else 
        {
            count = nullptr;
        }

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


