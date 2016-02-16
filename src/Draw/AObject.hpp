#ifndef AOBJECT_H
#define AOBJECT_H

#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>
#include <OpenGL.hh>

#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class AObject
{
public:
  AObject():
    _position(0, 0, 0),
    _rotation(0, 0, 0),
    _scale(5, 5, 5) {}

  virtual ~AObject(){}

  virtual void	setUV() = 0;
  virtual void	update(__attribute__((unused))gdl::Clock const &clock, __attribute__((unused))gdl::Input &input) { }
  virtual void	draw(gdl::AShader &shader, gdl::Clock const & clock) = 0;

  virtual void	initialize() = 0;

  void		translate(glm::vec3 const &v)
  {
    this->_position += v;
  }

  void		rotate(glm::vec3 const &axis, float angle)
  {
    this->_rotation += axis * angle;
  }

  void		scale(glm::vec3 const &scale)
  {
    this->_scale *= scale;
  }

  glm::mat4	getTransformation()
  {
    glm::mat4	transform(1);

    transform = glm::rotate(transform, this->_rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, this->_rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, this->_rotation.z, glm::vec3(0, 0, 1));
    transform = glm::translate(transform, this->_position);
    transform = glm::scale(transform, this->_scale);
    return (transform);
  }

  void		setPosition(glm::vec3 const &pos)
  {
    this->_position = pos;
  }

  void		setRotation(glm::vec3 const &rot)
  {
    this->_rotation = rot;
  }

  void		setScale(glm::vec3 const &scale)
  {
    this->_scale = scale;
  }

protected:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
};

#endif /* AOBJECT_H */
