#include "Vertex.h"
#include "Edge.h"
#include <string>
#include <iostream>

string Vertex::get_actor_name() const {
   if (actor_name == "")
   {
	cout << " empty vertex"; 
	  //make sure has a value, and uf not
   }
   return actor_name;
}

Vertex::~Vertex() {};
