#include "Addlife.hh"
#include <iostream>

Addlife::Addlife(glm::vec3 const &pos)
{
  this->_name = "life";
  this->_pos = pos;
  this->_pos.y = 0.5;
  this->_obj = new Cube(0.5, this->_pos, "BLIFE");
}

Addlife::~Addlife()
{ }
