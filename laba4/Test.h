#pragma once
#include "PriorityQueue.h"
#include <assert.h>
#include "DirectedGraph.h"

#include "UnDirectedGraph.h"

void Test_UnDirectedGraph_AddVertex()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    assert(graph.GetVertexCount() == 3);
}

void Test_UnDirectedGraph_AddEdge()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();

    graph.AddEdge(1, 2, 10);
    Vertex<int>* v1 = graph.GetVertex(1);
    Vertex<int>* v2 = graph.GetVertex(2);


    assert(v1->GetOutgoings().GetCount() == 1);
    assert(v1->GetOutgoings().Get(2) == 10);
    assert(v2->GetOutgoings().GetCount() == 1);
    assert(v2->GetOutgoings().Get(1) == 10);
}

void Test_UnDirectedGraph_GetVertex()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    Vertex<int>* vertex = graph.GetVertex(2);
    assert(vertex != nullptr);
    assert(vertex->GetId() == 2);
}

void Test_UnDirectedGraph_GetVertex_Exception()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();

    try
    {
        graph.GetVertex(2);
        assert(false);  
    }
    catch (const char* msg)
    {
        assert(true);   
    }
}

void Test_UnDirectedGraph_ColorGraph()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    graph.AddEdge(1, 2);
    graph.AddEdge(2, 3);

    graph.ColorGraph();


    Vertex<int>* v1 = graph.GetVertex(1);
    Vertex<int>* v2 = graph.GetVertex(2);
    Vertex<int>* v3 = graph.GetVertex(3);

    assert(v1->GetColor() != v2->GetColor());
    assert(v2->GetColor() != v3->GetColor());
    assert(v1->GetColor() != v3->GetColor());
}

void Test_UnDirectedGraph_FindShortestDistance()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    graph.AddEdge(1, 2, 10);
    graph.AddEdge(2, 3, 5);

    int distance = graph.FindShortestDistance(1, 3);
    assert(distance == 15);  
}

void Test_UnDirectedGraph_FindShortestDistance_Exception()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddEdge(1, 2, 10);

    try
    {
        graph.FindShortestDistance(1, 3);
        assert(false);  
    }
    catch (const std::runtime_error& e)
    {
        assert(true);  
    }
}



void Test_DirectedGraph_AddVertex()
{
    DirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    assert(graph.GetVertexCount() == 3);
}

void Test_DirectedGraph_AddEdge()
{
    DirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();

    graph.AddEdge(1, 2, 10);
    Vertex<int>* v1 = graph.GetVertex(1);
    Vertex<int>* v2 = graph.GetVertex(2);

    assert(v1->GetOutgoings().GetCount() == 1);
    assert(v1->GetOutgoings().Get(2) == 10);
    assert(v2->GetOutgoings().GetCount() == 0);
}

void Test_DirectedGraph_GetVertex()
{
    DirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    Vertex<int>* vertex = graph.GetVertex(2);
    assert(vertex != nullptr);
    assert(vertex->GetId() == 2);
}

void Test_DirectedGraph_GetVertex_Exception()
{
    DirectedGraph<int> graph;
    graph.AddVertex();

    try
    {
        graph.GetVertex(2);
        assert(false);  
    }
    catch (const char* msg)
    {
        assert(true);   
    }
}


void Test_DirectedGraph_FindShortestDistance()
{
    DirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    graph.AddEdge(1, 2, 10);
    graph.AddEdge(2, 3, 5);

    int distance = graph.FindShortestDistance(1, 3);
    assert(distance == 15); 
}

void Test_DirectedGraph_FindShortestDistance_Exception()
{
    DirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddEdge(1, 2, 10);

    try
    {
        graph.FindShortestDistance(1, 3);
        assert(false); 
    }
    catch (const std::runtime_error& e)
    {
        assert(true); 
    }
}


void Test_PriorityQueue_EnqueueAndPeek()
{
    PriorityQueue<int, int> pq;

    pq.Enqueue(1, 5);
    pq.Enqueue(2, 2);
    pq.Enqueue(3, 8);


    assert(pq.PeekFirst() == 2);
    assert(pq.PeekLast() == 3);
}

void Test_PriorityQueue_Dequeue()
{
    PriorityQueue<int, int> pq;

    pq.Enqueue(1, 5);
    pq.Enqueue(2, 2);
    pq.Enqueue(3, 8);

    assert(pq.Dequeue() == 2);
    assert(pq.Dequeue() == 1);
    assert(pq.Dequeue() == 3);
}

void Test_PriorityQueue_GetLength()
{
    PriorityQueue<int, int> pq;

    pq.Enqueue(1, 5);
    pq.Enqueue(2, 2);

    assert(pq.GetLength() == 2);

    pq.Dequeue();
    assert(pq.GetLength() == 1);

    pq.Dequeue();
    assert(pq.GetLength() == 0);
}

void Test_PriorityQueue_Contains()
{
    PriorityQueue<int, int> pq;

    pq.Enqueue(1, 5);
    pq.Enqueue(2, 2);

    assert(pq.PeekFirst() == 2);
    assert(pq.PeekLast() == 1);
}


void RunTests()
{
    Test_UnDirectedGraph_AddVertex();
    Test_UnDirectedGraph_AddEdge();
    Test_UnDirectedGraph_GetVertex();
    Test_UnDirectedGraph_GetVertex_Exception();
    Test_UnDirectedGraph_FindShortestDistance();
    Test_UnDirectedGraph_FindShortestDistance_Exception();
}