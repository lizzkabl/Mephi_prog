#pragma once
#include "Vertex.h"

template <class T>
class IGraph
{
	virtual void AddVertex() = 0;

	virtual void AddEdge(int from_id, int to_id, T weight ) = 0;

	virtual int GetVertexCount() const = 0;

	virtual Vertex<T>* GetVertex(int id) const = 0;

	virtual void ColorGraph() = 0;

	virtual T FindShortestDistance(int start_id, int end_id) const = 0;
};