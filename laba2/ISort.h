#pragma once
template <class T>
class ISort
{
public: 
	virtual void Sort(ShrdPtr<ListSequenceMutable<T>> seq) = 0;
	//virtual T Mean() = 0;
	//virtual T Median() = 0;
	//virtual T StandartDeviation() = 0;
};