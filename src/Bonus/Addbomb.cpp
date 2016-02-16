#include "Addbomb.hh"
#include <iostream>

Addbomb::Addbomb(glm::vec3 const &pos)
{
  this->_name = "bomb";
  this->_pos = pos;
  this->_pos.y = 0.5;
  this->_obj = new Cube(0.5, this->_pos, "BBOMB");
}

Addbomb::~Addbomb()
{ }
