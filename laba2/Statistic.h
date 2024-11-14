#pragma once
#include "Requirements.h"
#include "ShrdPtr.h"
#include "ListSequenceMutable.h"
#include <cmath> 
#include <functional>

template <is_ok T>
using Sqrt = std::function<T(const T&)>;

template <is_ok T>
class Statistic
{
public:
    Statistic() = default;

    T Mean(ShrdPtr<MutableSequence<T>> seq)
    {
        T sum = 0;
        int size = seq->GetLength();
        if (size == 0) 
        {
            throw std::runtime_error("Cannot calculate mean of an empty sequence.");
        }
        for (int i = 0; i < size; ++i)
        {
            sum += seq->Get(i);
        }
        return sum / size;
    }

    T StandartDeviation(ShrdPtr<MutableSequence<T>> seq, Sqrt<T> sqrt = [](const T& x) { return std::sqrt(x); })
    {
        int size = seq->GetLength();
        if (size == 0) {
            throw std::runtime_error("Cannot calculate standard deviation of an empty sequence.");
        }

        T mean = Mean(seq);
        T sumOfSquares = 0;

        for (int i = 0; i < size; ++i)
        {
            T deviation = seq->Get(i) - mean;
            sumOfSquares += deviation * deviation;
        }

        return sqrt(sumOfSquares / size);
    }

    T RootMeanSquare(ShrdPtr<MutableSequence<T>> seq, Sqrt<T> sqrt = [](const T& x) { return std::sqrt(x); })
    {
        int size = seq->GetLength();
        if (size == 0) 
        {
            throw std::runtime_error("Cannot calculate standard deviation of an empty sequence.");
        }
        T sumOfSquares = 0;
        for (int i = 0; i < size; ++i)
        {
            sumOfSquares += seq->Get(i) * seq->Get(i);
        }
        return sqrt(sumOfSquares / size);
    }
};
