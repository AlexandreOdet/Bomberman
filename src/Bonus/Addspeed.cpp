#include "Addspeed.hh"

Addspeed::Addspeed(glm::vec3 const &pos)
{
  this->_name = "speed";
  this->_pos = pos;
  this->_pos.y = 0.5;
  this->_obj = new Cube(0.5, this->_pos, "BSPEED");
}

Addspeed::~Addspeed()
{ }
