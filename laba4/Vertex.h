#pragma once

#include "DictionaryOnSequence.h"

template <class T>
class Vertex
{
private:
    int id;
    int color;
    DictionaryOnSequence<int, T> outgoings;


public:
    Vertex(int other) : id(other), outgoings(), color(-1) {}
    Vertex(int other, const DictionaryOnSequence<int, T>& other_out) : id(other), outgoings(other_out) {}

    int GetId()
    {
        return id;
    }

    void AddEdge(int out, T weight)
    {
        outgoings.Add(out, weight);
    }

    const DictionaryOnSequence<int, T>& GetOutgoings() const
    {
        return outgoings;
    }

    int GetCountOut()
    {
        return outgoings.GetCount();
    }

    int GetColor() const { return color; }
    void SetColor(int color) { this->color = color; }

};