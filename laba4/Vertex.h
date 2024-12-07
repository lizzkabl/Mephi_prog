#pragma once
#include "Edge.h"
class Vertex
{
private:
    int id;
    Edge** outgoings;
    int edge_count;
    int edge_capacity;

    void ResizeEdges()
    {
        int new_capacity = edge_capacity == 0 ? 4 : edge_capacity * 2;

        Edge** new_edges = new Edge * [new_capacity];
        for (int i = 0; i < edge_count; ++i)
        {
            new_edges[i] = outgoings[i];
        }
        delete[] outgoings;
        outgoings = new_edges;
        edge_capacity = new_capacity;
    }

public:

    Vertex(int other) : id(other), outgoings(nullptr), edge_count(0), edge_capacity(0) {}

    ~Vertex()
    {
        delete[] outgoings;
    }

    void AddEdge(Edge* edge)
    {
        if (edge_count == edge_capacity)
        {
            ResizeEdges();
        }
        outgoings[edge_count++] = edge;
    }

    int GetId()
    {
        return id;
    }
};