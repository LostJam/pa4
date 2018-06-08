#include "ActorGraph.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

//get the first arg as the input file
    char* infile = argv[1];

//make the graph and read the arg file
    ActorGraph graph;
//load the unweighted graph

    // TODO: load movie list from command line argument
    // graph.loadFromFile(infile, false);  
    graph.loadFromFile("databases/movie_casts.short.tsv", false);  

    // TODO: don't hardcode this
    graph.pathBetweenActors("actor1", "actor15");
    // graph.spitActors();   

    return 0;
}
