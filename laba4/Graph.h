#pragma once
#include "Vertex.h"
#include "Edge.h"

class Graph {
private:
    Vertex** vertices;  
    int vertex_count;     
    int vertex_capacity;  

    Edge** edges;        
    int edge_count;       
    int edge_capacity;

    void ResizeVertices() 
    {
        int new_capacity = vertex_capacity == 0 ? 4 : vertex_capacity * 2;
        Vertex** new_vertices = new Vertex * [new_capacity];
        for (int i = 0; i < vertex_count; ++i) 
        {
            new_vertices[i] = vertices[i];
        }
        delete[] vertices;
        vertices = new_vertices;
        vertex_capacity = new_capacity;
    }

    void ResizeEdges() 
    {
        int new_capacity = edge_capacity == 0 ? 4 : edge_capacity * 2;
        Edge** new_edges = new Edge * [new_capacity];
        for (int i = 0; i < edge_count; ++i)
        {
            new_edges[i] = edges[i];
        }
        delete[] edges;
        edges = new_edges;
        edge_capacity = new_capacity;
    }

    Vertex* FindVertex(int id) const
    {
        for (int i = 0; i < vertex_count; ++i) 
        {
            if (vertices[i]->GetId() == id) 
            {
                return vertices[i];
            }
        }
        return nullptr;
    }

public:
    Graph() : vertices(nullptr), vertex_count(0), vertex_capacity(0),
        edges(nullptr), edge_count(0), edge_capacity(0) {}

    ~Graph() 
    {
        for (int i = 0; i < vertex_count; ++i) 
        {
            delete vertices[i];
        }
        delete[] vertices;

        for (int i = 0; i < edge_count; ++i) 
        {
            delete edges[i];
        }
        delete[] edges;
    }

    void AddVertex(int id) 
    {
        if (vertex_count == vertex_capacity) 
        {
            ResizeVertices();
        }
        vertices[vertex_count++] = new Vertex(id);
    }

    void AddEdge(int from_id, int to_id) 
    {
        Vertex* from_vertex = FindVertex(from_id);
        Vertex* to_vertex = FindVertex(to_id);

        if (from_vertex && to_vertex) {
            Edge* edge = new Edge(from_vertex, to_vertex);
            if (edge_count == edge_capacity) 
            {
                ResizeEdges();
            }
            edges[edge_count++] = edge;
            from_vertex->AddEdge(edge);
        }
        else
        {
            //error
        }
    }
};

