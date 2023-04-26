#include "Halfedge.h"

Halfedge::Halfedge() {
	from = Vertex();
	to = Vertex();
}

Halfedge::Halfedge(Vertex v1, Vertex v2) {
	from = v1;
	to = v2;
}

Vertex Halfedge::getFrom() {
	return from;
}

Vertex Halfedge::getTo() {
	return to;
}

void Halfedge::setFrom(Vertex& v) {
	from = v;
}

void Halfedge::setTo(Vertex& v) {
	to = v;
}