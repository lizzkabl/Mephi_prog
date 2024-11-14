#pragma once
class Counter
{
private:
    int main_count;  
    int weak_count;    

public:

    Counter() : main_count(1), weak_count(0) {}

    void IncrementMain() 
    {
        ++main_count;
    }

    void DecrementMain() 
    {
        --main_count;
    }

    void IncrementWeak() 
    {
        ++weak_count;
    }
    void DecrementWeak() 
    {
        --weak_count;
    }
    int GetMain() const 
    {
        return main_count;
    }
    int GetWeak() const 
    {
        return weak_count;
    }
};
