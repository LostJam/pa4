#include Movie.h
#include Vertex.h
#include<iostream>

using namespace std;

string Movie::get_movie_name() const { 
    return movie_name;
}

int Movie::get_year() const{
    return movie_year; 
}

Movie::~Movie() {};
