#pragma once

using namespace std;

class Vertex {
	float x;
	float y;
	float z;

public:
	Vertex();
	
	Vertex(float x, float y, float z);

	float getX();

	float getY();

	float getZ();

	void setX(float cord);

	void setY(float cord);

	void setZ(float cord);
};