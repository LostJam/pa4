/*
 * ActorGraph.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
#include "Vertex.h"
#include "Edge.h"
#include <map>
#include <iostream>
#include <queue>

// Maybe include some data structures here

using namespace std;

class ActorGraph
{
  private:
    vector<Vertex *> unique_actors_list;
    vector<Edge *> unique_movies_list;

  public:
    ActorGraph(void);

    // Maybe add some more methods here

    /** You can modify this method definition as you wish
         *
         * Load the graph from a tab-delimited file of actor->movie relationships.
         *
         * in_filename - input filename
         * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
         *
         * return true if file was loaded sucessfully, false otherwise
         */
    bool loadFromFile(const char *in_filename, bool use_weighted_edges);
    void spitActors();

    Vertex* getActor(std::string actor_name);
    std::string pathBetweenActors(std::string actor1, std::string actor2);
    Vertex* checkIfActorIsUnique(std::string actor_name);
    Edge* checkIfMovieIsUnique(std::string movie_title, int movie_year);
  
  private:
    void shortestPathSetup(std::string actorName, std::string actorName2);
    std::string getPathFromEnd(std::string endName);
};

#endif // ACTORGRAPH_H
