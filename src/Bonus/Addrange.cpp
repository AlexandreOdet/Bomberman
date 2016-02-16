#include "Addrange.hh"

Addrange::Addrange(glm::vec3 const &pos)
{
  this->_name = "power";
  this->_pos = pos;
  this->_pos.y = 0.5;
  this->_obj = new Cube(0.5, this->_pos, "BRANGE");
}

Addrange::~Addrange()
{ }
