#pragma once
#include "Requirements.h"
#include "SortedSequenceOnSequence.h"
#include <cmath> 
#include <functional>

template <is_ok T>
using Sqrt = std::function<T(const T&)>;

template <is_ok T>
class Statistic
{
public:
    Statistic() = default;

    T Mean(SortedSequenceOnSequence<T>* seq)
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

    T StandardDeviation(SortedSequenceOnSequence<T>* seq, Sqrt<T> sqrt = [](const T& x) { return std::sqrt(x); })
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

    T RootMeanSquare(SortedSequenceOnSequence<T>* seq, Sqrt<T> sqrt = [](const T& x) { return std::sqrt(x); })
    {
        int size = seq->GetLength();
        if (size == 0) 
        {
            throw std::runtime_error("Cannot calculate root mean square of an empty sequence.");
        }
        T sumOfSquares = 0;
        for (int i = 0; i < size; ++i)
        {
            sumOfSquares += seq->Get(i) * seq->Get(i);
        }
        return sqrt(sumOfSquares / size);
    }

    T Min(SortedSequenceOnSequence<T>* seq)
    {
        if (seq->GetLength() == 0)
        {
            throw std::runtime_error("Cannot calculate standard deviation of an empty sequence.");
        }

        return seq->Get(0);
    }

    T Max(SortedSequenceOnSequence<T>* seq)
    {
        if (seq->GetLength() == 0)
        {
            throw std::runtime_error("Cannot calculate standard deviation of an empty sequence.");
        }
        return seq->Get(seq->GetLength()-1);
    }

    T Median(SortedSequenceOnSequence<T>* seq)
    {
        int size = seq->GetLength();
        if (seq->GetLength() == 0)
        {
            throw std::runtime_error("Cannot calculate standard deviation of an empty sequence.");
        }
        if (size % 2 == 0)
        {
            return (seq->Get(size / 2 - 1) + seq->Get(size / 2)) / 2;
        }
        return seq->Get(size / 2);
    }

    void PrintStatistics(std::ostream& out, SortedSequenceOnSequence<T>& seq)
    {
        out << "Max element - " << Max(&seq) << "\n";
        out << "Min element - " << Min(&seq) << "\n";
        out << "Mean of set - " << Mean(&seq) << "\n";
        out << "Standard Deviation of set - " << StandardDeviation(&seq) << "\n";
        out << "Root Mean Square of set - " << RootMeanSquare(&seq) << "\n";
        out << "Median of set - " << Median(&seq) << "\n";
        
    }

};
