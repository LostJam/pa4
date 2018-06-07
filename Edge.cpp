#include "Vertex.h"
#include "Edge.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//edge contains a movie object and a vertex of actors that have acted in that movie
Edge::string get_movie_name() const {
	return movie;
}

Edge::int get_movie_year() const {
	return year;
}

Edge::vector<Vertex*> get_Actors() {
	return Actors;
}
                
Edge::~Edge() {}
