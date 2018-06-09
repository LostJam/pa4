#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "Edge.h"

class Edge;

//holds Vertex Objects, which make up the vertices of our group
class Vertex
{

  public:
	std::string actor_name;
	int dist;
	bool visited;
	Vertex *prev;
	std::map<std::string, Edge *> movieLinks;
	std::vector<Edge *> movie_list;
	std::string get_actor_name() const;
	std::string printMovies();

	Vertex(std::string &name)
	{
		//set dist to almsot infinity
		prev = nullptr;
		visited = false;
		dist = INT_MAX;
		actor_name = name;
	}

	void insertEdge(Edge *edge);

	~Vertex();
};

#endif
