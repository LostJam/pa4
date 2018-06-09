#include "Vertex.h"

std::string Vertex::get_actor_name() const
{
  if (actor_name == "")
  {
    std::cout << " empty vertex";

    //make sure has a value, and uf not
  }
  return actor_name;
}

void Vertex::insertEdge(Edge *edge)
{
  movie_list.push_back(edge);
}

std::string Vertex::printMovies()
{
  std::string result = "Size of list: ";
  result += std::to_string(movie_list.size());
  result += " [";

  for (Edge *m : movie_list)
    result += m->movie + ", ";

  result += "]";
  return result;
}

Vertex::~Vertex(){};
