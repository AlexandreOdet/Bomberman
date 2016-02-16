#ifndef __ABONUS_HH__
#define __ABONUS_HH__

#include <BasicShader.hh>
#include <Clock.hh>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include "AObject.hpp"

enum BONUS{
  EMPTY,
  LIFE,
  BOMB,
  SPEED,
  RANGE
};

class Abonus
{
public:
  virtual ~Abonus() {}

  void		draw(gdl::AShader &shader,gdl::Clock const &clock)
  {
    this->_obj->draw(shader, clock);
  }

  std::string	getType() const
  {
    return (this->_name);
  }

  void		update(gdl::Clock const &clock, gdl::Input &input)
  {
    this->_obj->rotate(glm::vec3(0, 1, 0), 90);
    this->_obj->update(clock, input);
  }

protected:
  std::string	_name;
  glm::vec3	_pos;
  AObject	*_obj;
  BONUS		_type;
};

#endif
