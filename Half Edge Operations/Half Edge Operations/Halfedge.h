#pragma once
#include "Vertex.h"

using namespace std;

class Halfedge
{
	Vertex from;
	Vertex to;

public:

	Halfedge();

	Halfedge(Vertex v1, Vertex v2);

	Vertex getFrom();

	Vertex getTo();

	void setFrom(Vertex& v);

	void setTo(Vertex& v);
};

