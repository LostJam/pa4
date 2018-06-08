#include "Edge.h"
#include <string>
#include <iostream>

//edge contains a movie object and a vertex of actors that have acted in that movie
std::string Edge::get_movie_name() const
{
	return movie;
}

int Edge::get_movie_year() const
{
	return year;
}

int Edge::getWeight() const
{
	return 1 + (2015 - year);
}

std::vector<Vertex *> Edge::get_Actors()
{
	return Actors;
}

void Edge::insertActor(Vertex *actorVertexToAdd)
{
	Actors.push_back(actorVertexToAdd);
}

std::string Edge::nameHash()
{
	return movie + std::to_string(year);
}

Edge::~Edge() {}
