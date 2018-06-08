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
        {
            cout << " -> " << movie->get_movie_name() << "(" << movie->get_movie_year() << ") at: " << movie << endl;
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

        //is unique
        if (actor == nullptr)
        {
            //attach edge to previos vertex aka unique actor
            //create an edge with this first actors movie

            Edge *movie = checkIfMovieIsUnique(movie_title, movie_year);
            if (movie == nullptr)
            {
                movie = new Edge(movie_title, movie_year);
                unique_movies_list.push_back(movie);
            }

            //then add it
            actor = new Vertex(actor_name);
            actor->insertEdge(movie);
            movie->insertActor(actor);

            unique_actors_list.push_back(actor);
        }
        else
        {
            Edge *movie = checkIfMovieIsUnique(movie_title, movie_year);
            if (movie == nullptr)
            {
                movie = new Edge(movie_title, movie_year);
                unique_movies_list.push_back(movie);
            }
            movie->insertActor(actor);
            actor->insertEdge(movie);
        }

        linesRead++;
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

Edge *ActorGraph::checkIfMovieIsUnique(std::string movie_title, int movie_year)
{
    for (auto itr = unique_movies_list.cbegin(); itr != unique_movies_list.end(); ++itr)
    {
        //if the name is already in the vector set the bool to false
        auto movie = (*itr);
        if (movie->get_movie_name() == movie_title && movie->get_movie_year() == movie_year)
        {
            return (movie);
        }
    }

    return nullptr;
}

Vertex *ActorGraph::getActor(std::string actor_name)
{
    for (int i = 0; i < unique_actors_list.size(); i++)
    {
        auto actor = unique_actors_list.at(i);
        if (actor->actor_name == actor_name)
            return actor;
    }
}

bool ActorGraph::BFStraverse(Vertex *currentActor, Vertex *endActor, std::queue<Edge *> q, std::map<std::string, Vertex *> visited)
{
    // Check if we found THE END!
    if (currentActor == endActor)
    {
        std::cout << " - - - - - WE FOUND " << endActor->actor_name << endl;
        return true;
    }

    for (int i = 0; i < currentActor->movie_list.size(); i++)
    {
        Edge *movie = currentActor->movie_list.at(i);

        std::cout << "Adding " << movie->movie << " To our queue" << endl;
        q.push(movie);
    }

    Edge *tempMovie = q.front();

    if (tempMovie != nullptr)
    {
        std::cout << "Popping " << tempMovie->movie << " off the queue" << endl;
        q.pop();

        for (int y = 0; y < tempMovie->Actors.size(); y++)
        {
            Vertex *tempActor = tempMovie->Actors.at(y);
            std::cout << "Visiting actor " << tempActor->actor_name << endl;

            // Check if the map of visited vertexes already has this
            // actor we are looking at. If it does not contain it, we
            // will get an iterator pointing to the end of the map
            auto hasValue = visited.find(tempActor->actor_name);

            if (hasValue == visited.end()) // <-- hasValue == visited.end() MEANS unvisited
            {
                std::pair<std::string, Vertex *> value(tempActor->actor_name, tempActor);
                visited.insert(value);

                if (tempActor != currentActor)
                {
                    std::cout << "Beginning traversal at " << tempActor->actor_name << endl;
                    bool foundEnd = ActorGraph::BFStraverse(tempActor, endActor, q, visited);

                    if (foundEnd == true)
                        return true;
                }
                else
                {
                    std::cout << "Decided not to recurse on " << tempActor->actor_name << endl;
                }
            }
            else
            {
                std::cout << "Decided not to recurse on " << tempActor->actor_name << endl;
            }
        }

        return false;
    }

    std::cout << "Finished traversing" << endl;
}

// Should look like
// (<actorname>)--[movietitle#@movieyear]-->(actorname)--.....
std::string ActorGraph::pathBetweenActors(std::string name1, std::string name2)
{
    // traverse until we find the next boob
    Vertex *actor1 = getActor(name1);
    Vertex *actor2 = getActor(name2);

    std::queue<Edge *> q;
    std::map<std::string, Vertex *> map;

    BFStraverse(actor1, actor2, q, map);

    return "";
}