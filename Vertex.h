#ifndef VERTEX_H
#define VERTEX_H
#include <string>

//holds Vertex Objects, which make up the vertices of our group
class Vertex
{

  public:
	std::string actor_name;
	std::string get_actor_name() const;

	Vertex(std::string &name)
	{
		actor_name = name;
	}
	~Vertex();
};

#endif
