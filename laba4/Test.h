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


void Test_UnDirectedGraph_FindShortestPath_Simple()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    graph.AddEdge(1, 2, 5);
    graph.AddEdge(2, 3, 3);

    auto result = graph.FindShortestPath(1, 3);
    assert(result.first == 8);
    assert(result.second == std::vector<int>({ 1, 2, 3 }));
}

void Test_UnDirectedGraph_FindShortestPath_MultiplePaths()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    graph.AddEdge(1, 2, 1);
    graph.AddEdge(2, 4, 4);
    graph.AddEdge(1, 3, 2);
    graph.AddEdge(3, 4, 2);

    auto result = graph.FindShortestPath(1, 4);
    assert(result.first == 4);
    assert(result.second == std::vector<int>({ 1, 3, 4 }));
}

void Test_UnDirectedGraph_FindShortestPath_NoPath()
{
    UnDirectedGraph<int> graph;
    graph.AddVertex();
    graph.AddVertex();

    try
    {
        graph.FindShortestPath(1, 2);
        assert(false);
    }
    catch (const std::runtime_error& e)
    {
        assert(std::string(e.what()) == "No path found");
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

void Test_DirectedGraph_FindShortestPath_Simple()
{
    DirectedGraph<int> graph;
    graph.AddVertex(); 
    graph.AddVertex(); 
    graph.AddVertex(); 

    graph.AddEdge(1, 2, 5);
    graph.AddEdge(2, 3, 3);

    auto result = graph.FindShortestPath(1, 3);
    assert(result.first == 8); 
    assert(result.second == std::vector<int>({ 1, 2, 3 })); 
}

void Test_DirectedGraph_FindShortestPath_MultiplePaths()
{
    DirectedGraph<int> graph;
    graph.AddVertex(); 
    graph.AddVertex();
    graph.AddVertex();
    graph.AddVertex();

    graph.AddEdge(1, 2, 1);
    graph.AddEdge(2, 4, 4);
    graph.AddEdge(1, 3, 2);
    graph.AddEdge(3, 4, 2);

    auto result = graph.FindShortestPath(1, 4);
    assert(result.first == 4);
    assert(result.second == std::vector<int>({ 1, 3, 4 })); 
}

void Test_DirectedGraph_FindShortestPath_NoPath()
{
    DirectedGraph<int> graph;
    graph.AddVertex(); 
    graph.AddVertex(); 

    try
    {
        graph.FindShortestPath(1, 2);
        assert(false); 
    }
    catch (const std::runtime_error& e)
    {
        assert(std::string(e.what()) == "No path found");
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
    Test_DirectedGraph_AddVertex();
    Test_DirectedGraph_AddEdge();
    Test_DirectedGraph_GetVertex();
    Test_DirectedGraph_GetVertex_Exception();
    Test_DirectedGraph_FindShortestPath_Simple();
    Test_DirectedGraph_FindShortestPath_MultiplePaths();
    Test_DirectedGraph_FindShortestPath_NoPath();

    Test_UnDirectedGraph_AddVertex();
    Test_UnDirectedGraph_AddEdge();
    Test_UnDirectedGraph_GetVertex();
    Test_UnDirectedGraph_GetVertex_Exception();
    Test_UnDirectedGraph_FindShortestPath_Simple();
    Test_UnDirectedGraph_FindShortestPath_MultiplePaths();
    Test_UnDirectedGraph_FindShortestPath_NoPath();

    Test_PriorityQueue_Contains();
    Test_PriorityQueue_GetLength();
    Test_PriorityQueue_Dequeue();
    Test_PriorityQueue_EnqueueAndPeek();
}