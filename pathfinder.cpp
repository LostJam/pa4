#include "ActorGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool readPairsFile(const char *in_filename, const char *output_file, ActorGraph graph)
{
    // Initialize the file stream
    ifstream infile(in_filename);

    auto output = ofstream();
    output.open(output_file);

    bool have_header = false;

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

        if (record.size() != 2)
        {
            std::cout << "wrong size" << endl;
            continue;
        }

        string actor1(record[0]);
        string actor2(record[1]);
        std::cout << "Searching for: " << actor1 << " " << actor2 << endl;

        std::string result = graph.pathBetweenActors(actor1, actor2);
        output.write(result.c_str(), sizeof(result));

        linesRead++;
    } //endwhile!

    if (!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    output.close();

    std::cout << "finished reading pairs file" << endl;

    return true;
}

int main(int argc, char *argv[])
{

    //get the first arg as the input file
    bool weighted = false;
    char *infile = argv[1];
    if (argv[2] == "w")
    {
        weighted = true;
    }
    char *pairsFile = argv[3];
    char *outfile = argv[4];

    //make the graph and read the arg file
    ActorGraph graph;
    //load the unweighted graph

    // TODO: load movie list from command line argument
    graph.loadFromFile(infile, weighted);
    // graph.loadFromFile("databases/movie_casts.tsv", weighted);

    readPairsFile(pairsFile, outfile, graph);

    // ---- this is just testing stuff
    // graph.pathBetweenActors("BACON, KEVIN (I)", "KIDMAN, NICOLE");//36
    // graph.spitActors();
    // ----- end testing stuff

    return 0;
}
