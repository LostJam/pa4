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

class EdgeCompare
{
public:
    bool operator() (Vertex* e1, Vertex* e2)
    {
        return e1->dist < e2->dist;
    }
};

void ActorGraph::spitActors()
{
    int actorCount = 0;
    int movieCount = 0;

    for (auto itr = unique_actors_list.begin(); itr != unique_actors_list.end(); ++itr) 
    {
        auto actor = itr->second;
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

void ActorGraph::addToMovieMap(Edge *movie)
{
    std::string key = movie->movie + std::to_string(movie->year);
    std::pair<std::string, Edge*> newValue(key, movie);
    unique_movies_list.insert(newValue);
}

void ActorGraph::addToActorMap(Vertex* actor)
{
    std::pair<std::string, Vertex*> newValue(actor->actor_name, actor);
    unique_actors_list.insert(newValue);
}

bool ActorGraph::loadFromFile(const char *in_filename, bool use_weighted_edges, const char *pairsName, const char *outfileName)
{
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
    //first element in the vector so there is something to start with

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
                addToMovieMap(movie);
            }

            //then add it
            actor = new Vertex(actor_name);
            actor->insertEdge(movie);
            movie->insertActor(actor);

            addToActorMap(actor);
        }
        else
        {
            Edge *movie = checkIfMovieIsUnique(movie_title, movie_year);
            if (movie == nullptr)
            {
                movie = new Edge(movie_title, movie_year);
                addToMovieMap(movie);
            }
            movie->insertActor(actor);
            actor->insertEdge(movie);
        }

        linesRead++;
    } //endwhile!

    if (!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    std::cout << "finished reading file" << endl;

    return true;
}

Vertex *ActorGraph::checkIfActorIsUnique(std::string actor_name)
{
    std::string key = actor_name;
    auto value = unique_actors_list.find(key);
    
    if (value != unique_actors_list.end())
    {
        return value->second;
    }

    return nullptr;
}

Edge *ActorGraph::checkIfMovieIsUnique(std::string movie_title, int movie_year)
{
    std::string key = movie_title + std::to_string(movie_year);
    auto value = unique_movies_list.find(key);
    
    if (value != unique_movies_list.end())
    {
        return value->second;
    }

    return nullptr;
}

Vertex *ActorGraph::getActor(std::string actor_name)
{
    std::string key = actor_name;
    auto value = unique_actors_list.find(key);
    
    if (value != unique_actors_list.end())
    {
        return value->second;
    }

    std::cout << "ERROR: Couldn't find actor in map!!!" << endl;
    return nullptr;
}

Edge *ActorGraph::getSmallestWeight(Vertex *n, Vertex *currentActorNode)
{
    //loop through all the movies of one
    //then all the movies of the other
    int minWeight = INT_MAX;
    Edge *chosenMovie;

    for (Edge *m2 : currentActorNode->movie_list)
    {
        for (Edge *m1 : n->movie_list)
        {
            std::string movies = currentActorNode->printMovies();

            //then check if theyre equal and get their weight
            if (m1 == m2)
            {
                // if the next one is smaller then update min weight
                if (m1->getWeight() < minWeight)
                {
                    minWeight = m1->getWeight();
                    chosenMovie = m1;
                }
            }
        }
    }

    return chosenMovie;
}

void setActorLinks(Vertex *actor1, Vertex *actor2, Edge *closestMovie)
{
    std::string actorsKey = actor1->actor_name + actor2->actor_name;
    std::pair<std::string, Edge *> mapValue(actorsKey, closestMovie);
    actor1->movieLinks.insert(mapValue);
    actor2->movieLinks.insert(mapValue);
}

void ActorGraph::shortestPathSetup(std::string actorName, std::string actorName2)
{
    std::cout << "attempting to set up graph" << endl;
    std::priority_queue<Vertex *, vector<Vertex*>, EdgeCompare> queue;
    Vertex *currentActorNode;

    Vertex *actor1 = getActor(actorName);
    Vertex *actor2 = getActor(actorName2);

    queue.push(actor1);
    actor1->dist = 0;

    while (queue.empty() != true)
    {
        currentActorNode = queue.top();
        if (currentActorNode != nullptr)
        {
            queue.pop();
            currentActorNode->visited = true;

            // build a list of all actors in all movies this actor is listed in
            vector<Vertex *> neighbors;
            for (Edge *currentMovie : currentActorNode->movie_list)
            {
                for (Vertex *neighbor : currentMovie->Actors)
                {
                    neighbors.push_back(neighbor);
                }
            }

            // Iterate through all neighbors and modify their distances
            for (Vertex *n : neighbors)
            {
                if (n != currentActorNode && n->visited != true)
                {
                    Edge *closestMovie = getSmallestWeight(n, currentActorNode);
                    int weight = closestMovie->getWeight();

                    if (n->dist > currentActorNode->dist + weight)
                    {
                        // set the links
                        setActorLinks(n, currentActorNode, closestMovie);

                        n->dist = currentActorNode->dist + weight;
                        n->prev = currentActorNode;

                        // Check if we found the endpoint.
                        // If we did, there is no need to add any more nodes in this path
                        if (n == actor2)
                            break;

                        queue.push(n);
                    }
                }
            }
        }

        std::cout << "Queue has " << queue.size() << " items remaining" << endl;
    }

    std::cout << "done wit setup" << endl;
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
        Vertex *otherNode;

        if (i < numberOfNodes - 1)
            otherNode = pathNodes[i + 1];
        else
            otherNode = pathNodes[i - 1];

        path += "(" + node->actor_name + ")";

        Edge *movieLink;
        try
        {
            std::string mapKey = otherNode->actor_name + node->actor_name;
            movieLink = node->movieLinks.at(mapKey);
        }
        catch(const std::exception& e)
        {
            std::string mapKey = node->actor_name + otherNode->actor_name;
            movieLink = node->movieLinks.at(mapKey);
        }
        
        if (i < numberOfNodes - 1)
        {
            path += "--[" + movieLink->movie + "#@" + std::to_string(movieLink->year) + "]";
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