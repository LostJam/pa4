#ifndef EDGE_H
#define EDGE_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Vertex;
//holds Edge Objects, which make up the edges of our group
//contains a movie object and a list of actors that have acted in that movie, stored in a vec
class Edge {
        public:

		vector<Vertex*> Actors;
		string movie;
		int year;
                int get_movie_year() const; 
                string get_movie_name() const; 
                vector<Vertex*> get_Actors();
		//constructor with a movie object and a vertex to pass into its vector of actors
                Edge(string movie_name, int movie_year, Vertex* actorVertexToAdd) {
                        movie = movie_name;
			year = movie_year;
			Actors.push_back(actorVertexToAdd);
                }
                ~Edge();

};



#endif
~           
