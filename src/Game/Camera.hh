#ifndef	CAMERA_HH
#define	CAMERA_HH

#include <iostream>
#include <string>
#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>
#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <vector>

#include "Player.hh"

class	Camera
{
public:
  Camera(glm::vec3 const &pos, glm::vec3 const &lookAt, gdl::BasicShader &_shader);
  ~Camera();

public:
  glm::vec3 const	&getPos() const;
  void			setPos(glm::vec3 const &pos);
  void			setZoom(float const z);
  void			update(gdl::Clock const &clock, gdl::Input &input, std::vector<Player*> const &players);
  void			draw();
  void			drawOrtho();

private:
  void			onePlayer(Player const *player);
  void			translate(glm::vec3 const &v);

private:
  gdl::BasicShader	_shader;
  glm::vec3		_pos;
  glm::vec3		_lookAt;
  glm::mat4		_projection;
  glm::mat4		_transformation;

  float			_speed;
  float			_zoom;
  bool			_track;
};

#endif
