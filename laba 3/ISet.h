#pragma once
#include <functional>
template <class T>
using Comparator = std::function<bool(const T&, const T&)>;
template <class T>
class ISet
{
public:
	virtual bool Empty() const = 0;
	virtual void Insert(T element) = 0;
	virtual T Get(int index) const = 0;
	virtual int GetLength() const = 0;
	virtual void Pop(T element) = 0;
	virtual bool Contains(T element) const = 0;
	virtual bool SubSet(ISet<T>* set) const = 0;

};