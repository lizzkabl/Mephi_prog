#pragma once
#include "Vertex.h"
class Vertex;

class Edge
{
public:
    Vertex* from;
    Vertex* to;

    Edge(Vertex* from, Vertex* to) : from(from), to(to) {}
};