/*
MIT License

Copyright (c) 2016 Robert Smith

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Mesh.h"

/*
HalfEdge::HalfEdge(int fromVertex, int toVertex, int fromX, int fromY, int fromZ, int toX, int toY, int toZ) {
	HalfEdge::from = fromVertex;
	HalfEdge::to = toVertex;
	fromCoordinate[0] = fromX;
	fromCoordinate[1] = fromY;
	fromCoordinate[2] = fromZ;
	toCoordinate[0] = toX;
	toCoordinate[1] = toY;
	toCoordinate[2] = toZ;
}
*/
Mesh::Mesh() {
	return;
}


bool Mesh::load_mesh(string path) {
	if (path.substr(path.size() - 4, 4) != ".obj") {
		return false;
	}
	ifstream infile(path);
	string line;
	verticies.clear();
	Vertex empty = Vertex(0.0f, 0.0f, 0.0f);
	verticies.push_back(empty);
	
	while (getline(infile, line)) {
		if (firstToken(line) == "v")
		{
			vector<string> spos;
			Vertex v;
			split(tail(line), spos, " ");

			v.setX(stof(spos[0]));
			v.setY(stof(spos[1]));
			v.setZ(stof(spos[2]));

			verticies.push_back(v);
		}
		if (firstToken(line) == "f") {
			vector<string> verts;
			vector<int> face;
			split(tail(line), verts, " ");
			for (unsigned int i = 0; i < verts.size(); i++) {
				int temp = stoi(firstToken(verts[i]));
				face.push_back(temp);
			}
		}
		else {
			continue;
		}
	}
	//creating next map
	for (unsigned int i = 0; i < faces.size(); i++) {
		for (unsigned int j = 0; j < faces[i].size(); j++) {
			Halfedge curr = Halfedge();
			Halfedge next = Halfedge();
			Halfedge opp = Halfedge();
			if (j + 1 < faces[i].size()) {
				Vertex from = verticies[faces[i][j]];
				Vertex to = verticies[faces[i][0]];
				curr.setFrom(from);
				curr.setTo(to);
				opp.setFrom(to);
				opp.setTo(from);

				Vertex nextFrom = verticies[faces[i][0]];
				Vertex nextTo = verticies[faces[i][1]];
				next.setFrom(nextFrom);
				next.setTo(nextTo);
			}
			else if (j + 2 < faces[i].size()) {
				Vertex from = verticies[faces[i][j]];
				Vertex to = verticies[faces[i][j + 1]];
				curr.setFrom(from);
				curr.setTo(to);
				opp.setFrom(to);
				opp.setTo(from);

				Vertex nextFrom = verticies[faces[i][j + 1]];
				Vertex nextTo = verticies[faces[i][0]];
				next.setFrom(nextFrom);
				next.setTo(nextTo);
			}
			else {
				Vertex from = verticies[faces[i][j]];
				Vertex to = verticies[faces[i][j + 1]];
				curr.setFrom(from);
				curr.setTo(to);
				opp.setFrom(to);
				opp.setTo(from);

				Vertex nextFrom = verticies[faces[i][j + 1]];
				Vertex nextTo = verticies[faces[i][j + 2]];
				next.setFrom(nextFrom);
				next.setTo(nextTo);
			}
			nextEdge.insert(curr, next);
			oppositeEdge.insert(curr, opp);
		}
	}
	for (auto iter : nextEdge) {
		prevEdge.insert(iter.second, iter.first);
	}
	return true;
}


Halfedge Mesh::getNext(Halfedge& curr) {
	return nextEdge.at(curr);
}

Halfedge Mesh::getPrev(Halfedge& curr) {
	return prevEdge.at(curr);
}

Halfedge Mesh::getOpposite(Halfedge& curr) {
	return oppositeEdge.at(curr);
}






void split(const std::string& in,
	std::vector<std::string>& out,
	std::string token)
{
	out.clear();

	std::string temp;

	for (int i = 0; i < int(in.size()); i++)
	{
		std::string test = in.substr(i, token.size());

		if (test == token)
		{
			if (!temp.empty())
			{
				out.push_back(temp);
				temp.clear();
				i += (int)token.size() - 1;
			}
			else
			{
				out.push_back("");
			}
		}
		else if (i + token.size() >= in.size())
		{
			temp += in.substr(i, token.size());
			out.push_back(temp);
			break;
		}
		else
		{
			temp += in[i];
		}
	}
}

std::string tail(const std::string& in)
{
	size_t token_start = in.find_first_not_of(" \t");
	size_t space_start = in.find_first_of(" \t", token_start);
	size_t tail_start = in.find_first_not_of(" \t", space_start);
	size_t tail_end = in.find_last_not_of(" \t");
	if (tail_start != std::string::npos && tail_end != std::string::npos)
	{
		return in.substr(tail_start, tail_end - tail_start + 1);
	}
	else if (tail_start != std::string::npos)
	{
		return in.substr(tail_start);
	}
	return "";
}

std::string firstToken(const std::string& in)
{
	if (!in.empty())
	{
		size_t token_start = in.find_first_not_of(" \t");
		size_t token_end = in.find_first_of(" \t", token_start);
		if (token_start != std::string::npos && token_end != std::string::npos)
		{
			return in.substr(token_start, token_end - token_start);
		}
		else if (token_start != std::string::npos)
		{
			return in.substr(token_start);
		}
	}
	return "";
}
