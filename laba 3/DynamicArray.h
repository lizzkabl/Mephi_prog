#pragma once
#include <stdexcept>
#include "functional"
template <class T>
using Comparator = std::function<bool(const T&, const T&)>;


template <class T>
class DynamicArray{
	private:
		size_t size;
		T* array;
		Comparator<T> is_equal;
	public:
		DynamicArray(): is_equal{ std::equal_to<T>() }
		{
			this->size = 0;
			this->array = new T[0];
		}

		DynamicArray(const size_t size, Comparator<T> is_equal = std::equal_to<T>()): is_equal{ is_equal }
		{
			this->size = size;
			this->array = new T[size];
			for (int i = 0; i < size; i++)
			{
				this->array[i] = NULL;
			}
		}

		DynamicArray(const T elem, Comparator<T> is_equal = std::equal_to<T>()): is_equal{ is_equal }
		{
			this->size = 1;
			this->array = new T[size];
			this->array[0] = elem;
			
		}

		DynamicArray(const T* items, const size_t count, Comparator<T> is_equal = std::equal_to<T>()): is_equal{ is_equal }
		{
			this->size = count;
			this->array = new T[count];
			for (int i = 0; i < count; i++)
			{
				this->array[i] = items[i];
			}
		}
		
		DynamicArray(const DynamicArray<T> &other) : size{ other.size }, is_equal{ other.is_equal }
		{
			this->array = new T[size];
			std::copy(other.array, other.array + size, this->array);		 
		}

		~DynamicArray()
		{
			if (array)
			{
				delete[] array;
			}
		}

		DynamicArray& operator=(const DynamicArray& other)
		{
			array = other.array;
			size = other.size;
			is_equal = other.is_equal;

			return *this;
		}

		size_t GetSize() const
		{
			return this->size;
		}
		
		T Get(int index) const
		{
			if ((index >= this->GetSize()) || (index < 0))
			{
				throw  "IndexOutOfRange";
			}
			return this->array[index];
		}

		void Set(const int index, const T &value)
		{			
			if ((index >= this->GetSize()) || (index < 0) )
			{
				throw  "IndexOutOfRange";
			}
			this->array[index] = value;
		}

		void Clear()
		{
			this->Resize(0);
		}

		void Resize(const size_t new_size) 
		{
			T* new_arr = new T[new_size];
			size_t copy_size = std::min(new_size, size);
			for (size_t i = 0; i < copy_size; i++) 
			{
				new_arr[i] = array[i];
			}
			delete[] array;
			array = new_arr;
			size = new_size;
		}

		void Append(const T &item)
		{
			T* new_arr = new T[this->size + 1];
			std::copy(this->array, this->array + this->size, new_arr);
			new_arr[this->size] = item;
			this->size = this->size + 1;
			delete[] this->array;
			this->array = new T[size];
			for (int i = 0; i < size; i++)
			{
				this->array[i] =new_arr[i];
			}
			delete[] new_arr;
		}

		void Swap(int i, int j)
		{
			if (i < 0 || i >= GetSize() || j < 0 || j >= GetSize())
			{
				throw std::out_of_range("Index out of range");
			}
			T help = array[i];
			array[i] = array[j];
			array[j] = help;
		}
		void Pop(T element) 
		{
			size_t count = 0;
			for (size_t i = 0; i < this->size; i++) 
			{
				if (is_equal(this->array[i],  element))
				{
					count++;
				}
			}
			if (count == 0) 
			{
				return;
			}
			T* new_arr = new T[this->size - count];
			size_t j = 0; 
			for (size_t i = 0; i < this->size; i++) {
				if (!is_equal(this->array[i] , element)) 
				{
					new_arr[j] = this->array[i];
					j++;
				}
			}
			this->size -= count;
			delete[] this->array;
			this->array = new_arr;
		}
};
