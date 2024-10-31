#pragma once

class Counter
{
private:
    int count;

    // Deleted copy constructor to prevent copying
    Counter(const Counter& other) : count(other.count) {}
    

public:
    // Default constructor initializes count to 1 (useful for shared pointer)
    Counter() : count(1) {}

    void Reset()
    {
        count = 0;
    }

    int Get() const
    {
        return count;
    }

    // Prefix increment
    Counter& operator++()
    {
        ++count;
        return *this;
    }

    // Postfix increment
    Counter operator++(int)
    {
        Counter temp = *this;
        count++;
        return temp;
    }

    // Prefix decrement
    Counter& operator--()
    {
        --count;
        return *this;
    }

    // Postfix decrement
    Counter operator--(int)
    {
        Counter temp = *this;
        count--;
        return temp;
    }
};
