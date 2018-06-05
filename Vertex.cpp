#include "Vertex.h"
#include <string>
#include <iostream>
using namespace std;

string Vertex::get_actor_name() const {
 
   cout << " in the vertex!!!" << endl;

   if (actor_name == "")
   {

	cout << " empty vertex"; 
      //make sure has a value, and uf not
   }


   return actor_name;
}

//Vertex::~Vertex() {};
