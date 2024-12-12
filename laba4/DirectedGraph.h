#pragma once
#include "DictionaryOnSequence.h"
#include "SetOnSequence.h"
#include "Vertex.h"
#include "IGraph.h"

template <class T>
class DirectedGraph : IGraph<T>
{
private:
    DictionaryOnSequence<int, Vertex<T>*> vertices; 

public:

    DirectedGraph() : vertices() {}

    DirectedGraph(const DirectedGraph& other) : vertices()
    {
        for (int i = 0; i < other.vertices.GetCount(); ++i)
        {
            Vertex<T>* original = other.vertices.Get(i + 1);
            vertices.Add(i + 1, new Vertex<T>(*original));
        }
    }

    ~DirectedGraph()
    {
        for (int i = 0; i < vertices.GetCount(); ++i)
        {
            delete vertices.Get(i + 1);
        }
    }

    void AddVertex() override
    {
        vertices.Add(vertices.GetCount() + 1, new Vertex<T>(vertices.GetCount() + 1));
    }

    void AddEdge(int from_id, int to_id, T weight) override
    {
        vertices.Get(from_id)->AddEdge(to_id, weight);
    }

    int GetVertexCount() const override
    {
        return vertices.GetCount();
    }

    Vertex<T>* GetVertex(int id) const override
    {
        if (vertices.ContainsKey(id))
        {
            return vertices.Get(id);
        }
        else
        {
            throw "Vertex doesnt exist";
        }
    }

    void ColorGraph() override 
    {
        SetOnSequence<int> used_colors;

        for (int i = 0; i < vertices.GetCount(); ++i)
        {
            Vertex<T>* vertex = vertices.Get(i + 1);

            SetOnSequence<int> neighborColors;

            const DictionaryOnSequence<int, int>& outgoings = vertex->GetOutgoings();

            for (int j = 0; j < outgoings.GetCount(); ++j)
            {
                int toId = outgoings.GetKeyAtIndex(j);
                Vertex<T>* neighbor = vertices.Get(toId);

                if (neighbor->GetColor() != -1) 
                {
                    neighborColors.Insert(neighbor->GetColor());
                }
            }
            int color = 0;
            while (neighborColors.Contains(color))  
            {
                ++color;
            }
            vertex->SetColor(color);
        }
    }

    T FindShortestDistance(int start_id, int end_id) const override
    {
        const int maxi = 2147483647;
        if (!vertices.ContainsKey(start_id) || !vertices.ContainsKey(end_id))
        {
            throw std::runtime_error("One or both vertices not found");
        }

        DictionaryOnSequence<int, T> distances;
        for (int i = 0; i < vertices.GetCount(); ++i)
        {
            distances.Add(i + 1, maxi);
        }
        distances.Set(start_id, 0); 

        SetOnSequence<int> visited;

        while (visited.GetLength() < vertices.GetCount())
        {
            int current_id = -1;
            T min_distance = maxi;
            for (int i = 0; i < distances.GetCount(); ++i)
            {
                int vertex_id = distances.GetKeyAtIndex(i);
                if (!visited.Contains(vertex_id) && distances.Get(vertex_id) < min_distance)
                {
                    current_id = vertex_id;
                    min_distance = distances.Get(vertex_id);
                }
            }

            if (current_id == -1)
            {
                break;
            }

            visited.Insert(current_id);

            if (current_id == end_id)
            {
                break;
            }
            Vertex<T>* current_vertex = vertices.Get(current_id);
            const DictionaryOnSequence<int, T>& outgoings = current_vertex->GetOutgoings();

            for (int i = 0; i < outgoings.GetCount(); ++i)
            {
                int neighbor_id = outgoings.GetKeyAtIndex(i);
                T weight = outgoings.Get(neighbor_id);

                if (distances.Get(current_id) + weight < distances.Get(neighbor_id))
                {
                    distances.Set(neighbor_id, distances.Get(current_id) + weight);
                }
            }
        }

        T result = distances.Get(end_id);
        if (result == maxi)
        {
            throw std::runtime_error("No path found");
        }
        return result;
    }

};

