#pragma once
template <class T>
using Comparator = std::function<bool(const T&, const T&)>;

template <class K, class T>
class IDictionary
{
public:
	virtual int GetCount() const = 0;
	virtual int GetCapacity() const = 0;
	virtual T Get(K key) const = 0;
	virtual bool ContainsKey(K key) const = 0;
	virtual void Add(K key, T element) = 0;
	virtual void Remove(K key) = 0;
};
