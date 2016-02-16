#ifndef __ABOX_HH__
#define __ABOX_HH__

#include <BasicShader.hh>
#include <Clock.hh>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "AObject.hpp"
#include "Addbomb.hh"
#include "Addrange.hh"
#include "Addspeed.hh"
#include "Addlife.hh"

class ABox
{
protected:
  bool		_solid;
  bool		_breakable;
  std::string	_type;
  glm::vec3	_pos;
  AObject	*_obj;
  BONUS		_Btype;

public:
  ABox() {}
  virtual ~ABox() {}


  glm::vec3 const &getPos() const
  {
    return this->_pos;
  }

  std::string	getType() const
  {
    return this->_type;
  }

  bool		getSolid() const
  {
    return this->_solid;
  }

  bool		getBreakable() const
  {
    return this->_breakable;
  }

  AObject	*getObject() const
  {
    return this->_obj;
  }

  BONUS		&getBonusType()
  {
    return this->_Btype;
  }

  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
  virtual void	update(gdl::Clock const &clock, gdl::Input &input) = 0;
  virtual void	DeleteBonus() { }
};

#endif
