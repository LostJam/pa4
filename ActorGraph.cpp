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
        cout << actor->get_actor_name() << " distance: " << actor->dist << endl;

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

int ActorGraph::getSmallestWeight(Vertex *n, Vertex *currentActorNode)
{
    //loop through all the movies of one
    //then all the movies of the other
    int minWeight = INT_MAX;
    for (Edge *m1 : n->movie_list)
    {
        for (Edge *m2 : currentActorNode->movie_list)
        {
            //then check if theyre equal and get their weight
            if (m1 == m2)
            {
                // if the next one is smaller then update min weight
                if (m1->getWeight() < minWeight)
                {
                    minWeight = m1->getWeight();
                }
            }
        }
    }
    return minWeight;
}

void ActorGraph::shortestPathSetup(std::string actorName, std::string actorName2)
{
    std::queue<Vertex *> q;
    Vertex *currentActorNode;

    Vertex *actor1 = getActor(actorName);
    Vertex *actor2 = getActor(actorName2);

    q.push(actor1);
    actor1->dist = 0;

    while (q.empty() != true)
    {
        currentActorNode = q.front();
        if (currentActorNode != nullptr)
        {
            q.pop();
            currentActorNode->visited = true;

            std::cout << "Looking at Node: " << currentActorNode->actor_name << endl;

            // build a list of all actors in all movies this actor is listed in
            vector<Vertex *> neighbors;
            for (Edge *currentMovie : currentActorNode->movie_list)
            {
                std::cout << "Actor " << currentActorNode->actor_name << "Has been in " << currentMovie->movie << endl;

                for (Vertex *neighbor : currentMovie->Actors)
                {
                    std::cout << "Adding neighbor " << neighbor->actor_name << " to " << currentActorNode->actor_name << endl;

                    neighbor->movieLink = currentMovie;
                    neighbors.push_back(neighbor);
                }
            }

            // Iterate through all neighbors and modify their distances
            for (Vertex *n : neighbors)
            {
                if (n != currentActorNode && n->visited != true)
                {
                    int weight = getSmallestWeight(n, currentActorNode);

                    if (n->dist > currentActorNode->dist + weight)
                    {
                        //add
                        n->dist = currentActorNode->dist + weight;
                        n->prev = currentActorNode;

                        // Check if we found the endpoint.
                        // If we did, there is no need to add any more nodes in this path
                        if (n == actor2)
                            break;

                        std::cout << "Found unvisited node " << n->actor_name << ": adding to queue" << endl;

                        q.push(n);
                    }
                }
            }
        }
    }
}

std::string ActorGraph::getPathFromEnd(std::string endName)
{
    std::cout << "Printing final path..." << endl;

    // To get the shortest path, we just need to find our end node
    // and move backwards toward the beginning
    Vertex *endActor = getActor(endName);
    Vertex *currentNode = endActor;

    // This vector is going to keep track of all nodes in the path
    // so we can iterate through it when printing
    vector<Vertex *> pathNodes;

    while (currentNode != nullptr)
    {
        // Adding to front of vector to reverse the order
        pathNodes.insert(pathNodes.begin(), currentNode);
        currentNode = currentNode->prev;
    }

    std::string path = "";
    int numberOfNodes = pathNodes.size();
    for (int i = 0; i < numberOfNodes; i++)
    {
        Vertex *node = pathNodes[i];

        path += "(" + node->actor_name + ")";

        if (i < numberOfNodes - 1)
        {
            path += "--[" + node->movieLink->movie + "#@" + std::to_string(node->movieLink->year) + "]";
            path += "-->";
        }
        else
            path += "\n";
    }

    return path;
}

std::string ActorGraph::pathBetweenActors(std::string name1, std::string name2)
{
    // Set up our graph by changing all the distances in the nodes
    shortestPathSetup(name1, name2);

    // Print out the path to our endpoint. Should be formatted as:
    // (<actorname>)--[movietitle#@movieyear]-->(actorname)--.....
    std::string finalPath = getPathFromEnd(name2);

    std::cout << finalPath << endl;

    return finalPath;
}