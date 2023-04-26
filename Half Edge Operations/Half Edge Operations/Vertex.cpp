#include "Vertex.h"

Vertex::Vertex() {
	x = 0;
	y = 0;
	z = 0;
}

Vertex::Vertex(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vertex::getX() {
	return x;
}

float Vertex::getY() {
	return y;
}

float Vertex::getZ() {
	return z;
}

void Vertex::setX(float cord) {
	x = cord;
}

void Vertex::setY(float cord) {
	y = cord;
}

void Vertex::setZ(float cord) {
	z = cord;
}

