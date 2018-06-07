#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <vector>
#include "Edge.h"

class Edge;

//holds Vertex Objects, which make up the vertices of our group
class Vertex
{

  public:
	std::string actor_name;
	std::vector<Edge *> movie_list;
	std::string get_actor_name() const;

	Vertex(std::string &name)
	{
		actor_name = name;
	}

	void insertEdge(Edge* edge);

	~Vertex();
};

#endif
