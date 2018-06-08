#ifndef EDGE_H
#define EDGE_H
#include <vector>
#include <string>
#include "Vertex.h"

class Vertex;

//holds Edge Objects, which make up the edges of our group
//contains a movie object and a list of actors that have acted in that movie, stored in a vec
class Edge
{
      public:
        std::vector<Vertex *> Actors;
        std::string movie;
        int year;
        int get_movie_year() const;
        std::string get_movie_name() const;
        std::vector<Vertex *> get_Actors();
        void insertActor(Vertex* actorVertexToAdd);

        
        int getWeight() const;
        //constructor with a movie object and a vertex to pass into its vector of actors
        Edge(std::string movie_name, int movie_year)
        {
                movie = movie_name;
                year = movie_year;
        }
        std::string nameHash();
        ~Edge();
};

#endif