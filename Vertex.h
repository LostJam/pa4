#ifndef VERTEX_H
#define VERTEX_H
//#include "Edge.h"
#include <string>
//#include <iostream>
//#include <vector>

//holds Vertex Objects, which make up the vertices of our group
class Vertex {

//using namespace std;
	public:
		std::string actor_name;
		//string get_actor_name() const;
		//string&
		Vertex(std::string& name) {
			actor_name = name; 
		}
		~Vertex();

};



#endif
