#pragma once
#include <iostream>
#include <stdexcept>


template <class T>
class UnqPtr
{
private:
	T* ptr;

public:
	UnqPtr() : ptr{ nullptr } {}
	UnqPtr(T* other) : ptr{ other } {}
	UnqPtr(const UnqPtr&) = delete;
	UnqPtr(const UnqPtr&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
	~UnqPtr()
	{
		if (ptr)
		{
			delete ptr;
		}
	}
	UnqPtr& operator=(UnqPtr<T>&& other)
	{
		if (this != &other)
		{
			delete ptr;
			ptr = other.ptr_;
			other.ptr_ = nullptr;
		}
		return *this;
	}

	T* Get() const
	{
		return ptr;
	}
	T* Release()
	{
		T* temp = ptr;
		ptr = nullptr;
		delete ptr;
		return *temp;
	}
	void Reset(T* other)
	{
		delete ptr;
		ptr = other;
	}

	T& operator*() 
	{
		if (ptr)
		{
			return *ptr;
		}
		else
		{
			throw std::runtime_error("Dereferencing a null pointer.");
		}
		
	}

	const T& operator*() const
	{
		if (ptr)
		{
			return *ptr;
		}
		else
		{
			throw std::runtime_error("Dereferencing a null pointer.");
		}
	}

	T* operator->()
	{
		if (ptr)
		{
			return ptr;
		}
		else
		{
			throw std::runtime_error("Dereferencing a null pointer.");
		}
	}

	const T* operator->() const
	{
		if (ptr)
		{
			return ptr;
		}
		else
		{
			throw std::runtime_error("Dereferencing a null pointer.");
		}
	}

	explicit operator bool() const
	{
		return ptr != nullptr;
	}

	void Swap(UnqPtr<T> other)
	{
		T* temp = ptr;
		ptr = other.ptr;
		other.ptr = temp;
	}
};
