#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <iostream>
using namespace std;

//holds Edge Objects, which make up the edges of our group
//contains a movie object and a list of actors that have acted in that movie, stored in a vec
class Edge {
        public:
                Movie movie;
                string get_movie_info() const; 
                string get_actors_vec() const;
                Edge(Movie movie, Vector thisMoviesActors) {
                        movie = movie;
                        these_actors = thisMoviesActors;
                }
                ~Edges();

};



#endif
~           
