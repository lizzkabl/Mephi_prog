#pragma once

template <class T>
class MutableSequence
{
public:
	virtual ~MutableSequence() = default;
	virtual T GetFirst() const =  0;
	virtual T GetLast() const = 0;
	virtual T Get(const int index) const = 0;
	virtual MutableSequence<T>* GetSubsequence(const int startIndex, const int endIndex)const =0;
	virtual int GetLength() const = 0;
	virtual void Append(const T &item) = 0;
	virtual void Prepend(const T &item) = 0;
	virtual void InsertAt(const T &item, int index) = 0;
	virtual MutableSequence<T>* Concat(const MutableSequence <T>* list) const = 0;	
	virtual void Swap(int i, int j) = 0;
};
