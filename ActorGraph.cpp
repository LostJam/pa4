/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"
#include "Vertex.h"
#include "Edge.h"
using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
    //first element in the vector so there is something to start with
    string start = "start";
    vector <Vertex*> actorV;  
    Vertex* vertex = new Vertex(start);
    actorV.push_back(vertex);
 
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;

            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }


        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);

///make a vector of unique actor objects and add them all///
		
	//if actors name not already in the vector, create vertex and add it
	bool isInVec = false;
	//first time through has start in front
	for (auto itr = actorV.cbegin(); itr != actorV.end(); ++itr) {
		//might be at end in final iteration, which is not dereferencable
		//if((itr+1) != actorV.end()){
			//if the name is already in the vector set the bool to false
			if (((*itr)->get_actor_name()) == (actor_name)){	
				isInVec	= true;
				//exit loop
				break;
			}
		//}
	}

	//if the vertex is not already in the vector than we add it to the vecotr
	if (isInVec == false) {
				//then add it
				Vertex* vertex = new Vertex(actor_name);
				actorV.push_back(vertex);
				cout << vertex->get_actor_name() << endl;
				continue;
	}
	

	//Edge::connectEdges(&vertex, movie_title, movie_year);
    //endwhile!
    }

    //remove dummy vertex
    actorV.erase(actorV.begin());

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
