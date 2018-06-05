#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <iostream>
using namespace std;

//holds Actor Objects, which make up the vertices of our group
class Vertex {

	public:
		string actor_name;
		string get_actor_name() const;
		//string&
		Vertex(string name) {
			actor_name = name; 
		}
		~Vertex();

};



#endif
