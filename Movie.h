#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>
using namespace std;

//holds Movie Objects, which make up the edges of our group
class Movie {
        public:
                string movie_name;
                string movie_year;
                string get_movie_name() const;
                string get_movie_year() const;
                Movie(string name, int year) {
                        movie_name = name; 
			movie_year = year;
                }
                ~Movie();

};



#endif
