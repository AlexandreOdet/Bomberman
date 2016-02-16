#include "Box.hh"

Box::Box(glm::vec3 const &pos)
{
  this->_Btype = EMPTY;
  this->_pos = pos;
  this->_type = "box";
  this->_breakable = true;
  this->_solid = true;
  this->_obj = new Cube(1, this->_pos, "BOX");
}

Box::~Box()
{ }

void		Box::draw(gdl::AShader &shader,gdl::Clock const &clock)
{
  this->_obj->draw(shader, clock);
}

void		Box::update(gdl::Clock const &clock, gdl::Input &input)
{
  this->_obj->update(clock, input);
}
