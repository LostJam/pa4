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

void ActorGraph::spitActors()
{
    int actorCount = 0;
    int movieCount = 0;

    for (int i = 0; i < unique_actors_list.size(); i++)
    {
        auto actor = unique_actors_list.at(i);
        cout << actor->get_actor_name() << endl;

        for (Edge *movie : actor->movie_list)
        // for (auto itr = actor->movie_list.begin(); itr != actor->movie_list.end(); itr++)
        {
            cout << " -> " << movie->get_movie_name() << " at: " << movie << endl;
            // cout << " -> " << (*itr)->get_movie_name() <<  " at: " << (*itr) << endl;
            movieCount++;
        }

        actorCount++;
    }

    cout << "Number of actors: " << actorCount << endl;
    cout << "Number of movies: " << movieCount << endl;
}

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char *in_filename, bool use_weighted_edges)
{
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
    //first element in the vector so there is something to start with
    string start = "start";
    Vertex *vertex = new Vertex(start);
    unique_actors_list.push_back(vertex);

    int linesRead = 0;
    // keep reading lines until the end of file is reached
    while (infile)
    {
        string s;

        // get the next line
        if (!getline(infile, s))
            break;

        if (!have_header)
        {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss)
        {
            string next;

            // get the next string before hitting a tab character and put it in 'next'
            if (!getline(ss, next, '\t'))
                break;

            record.push_back(next);
        }

        if (record.size() != 3)
        {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);

        ///make a vector of unique actor objects and add them all///

        //if actors name not already in the vector, create vertex and add it
        Vertex *actor = checkIfActorIsUnique(actor_name);

        if (actor == nullptr)
        {
            //attach edge to previos vertex aka unique actor
            //create an edge with this first actors movie
            Edge *movie = new Edge(movie_title, movie_year);
            //then add it
            Vertex *actor = new Vertex(actor_name);
            actor->insertEdge(movie);
            movie->insertActor(actor);

            unique_actors_list.push_back(actor);
        }
        else
        {
            Edge *edge = new Edge(movie_title, movie_year);
            edge->insertActor(actor);
            actor->insertEdge(edge);
        }

        // std::cout << "added an actor and an edge: actor -> " << actor->get_actor_name() << endl;

        linesRead++;
        std::cout << "Number of lines read: " << linesRead << endl;
    } //endwhile!

    //remove dummy vertex
    unique_actors_list.erase(unique_actors_list.begin());

    if (!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

Vertex *ActorGraph::checkIfActorIsUnique(std::string actor_name)
{
    for (auto itr = unique_actors_list.cbegin(); itr != unique_actors_list.end(); ++itr)
    {
        //if the name is already in the vector set the bool to false
        if (((*itr)->get_actor_name()) == (actor_name))
        {
            return (*itr);
        }
    }

    return nullptr;
}
