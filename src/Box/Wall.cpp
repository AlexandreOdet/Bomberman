#include "Wall.hh"

Wall::Wall(glm::vec3 const &pos)
{
  this->_type = "wall";
  this->_Btype = EMPTY;
  this->_pos = pos;
  this->_breakable = false;
  this->_solid = true;
  this->_obj = new Cube(1, this->_pos, "WALL");
}

Wall::~Wall()
{ }

void		Wall::draw(gdl::AShader &shader,gdl::Clock const &clock)
{
  this->_obj->draw(shader, clock);
}

void		Wall::update(gdl::Clock const &clock, gdl::Input &input)
{
  this->_obj->update(clock, input);
}
