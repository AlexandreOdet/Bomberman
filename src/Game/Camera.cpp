#include "Camera.hh"

Camera::Camera(glm::vec3 const &pos, glm::vec3 const &lookAt, gdl::BasicShader &shader) : _shader(shader), _pos(pos), _lookAt(lookAt)
{
  this->_speed = 20.0f;
  this->_projection = glm::perspective(60.f, 1920.0f/1080.0f, 0.001f, 10000.0f);
  this->_transformation = glm::lookAt(this->_pos, this->_lookAt, glm::vec3(0, 2, 0));
  this->_shader.bind();
  this->_shader.setUniform("view", this->_transformation);
  this->_shader.setUniform("projection", this->_projection);
  this->_zoom = 20;
  this->_track = false;
}

Camera::~Camera()
{
}

void		Camera::translate(glm::vec3 const &v)
{
  this->_pos += v;
  this->_lookAt += v;
}

void		Camera::setZoom(float const z)
{
  this->_zoom = z;
}

void		Camera::onePlayer(Player const *player)
{
  glm::vec3	tmp = player->getPosition();

  this->_pos = glm::vec3(tmp.x , this->_pos.y, tmp.z - 2);
  this->_lookAt = tmp;
}

void		Camera::update(gdl::Clock const &clock, gdl::Input &input, std::vector<Player*> const &players)
{
  if (input.getKey(SDLK_KP_PLUS) && this->_pos.y > 0.01)
    translate(glm::vec3(0, -1, 0) * static_cast<float>(clock.getElapsed()) * this->_speed);
  if (input.getKey(SDLK_KP_MINUS))
    translate(glm::vec3(0, 1, 0) * static_cast<float>(clock.getElapsed()) * this->_speed);
  if (input.getKey(SDLK_F1))
    {
      this->_track = false;
      this->_pos = glm::vec3(0, this->_zoom, -0.01);
      this->_lookAt = glm::vec3(0, 0, 0);
    }
  if (input.getKey(SDLK_F2))
    {
      this->_track = false;
      this->_pos = glm::vec3(0, this->_zoom, -10);
      this->_lookAt = glm::vec3(0, 0, 0);
    }
  if (input.getKey(SDLK_F3) || _track)
    {
      if ((players[0]->getName() == "Player1" && players[1]->getName() != "Player2")
	  || players[0]->getName() == "Player2")
	{
	  this->_track = true;
	  onePlayer(players[0]);
	}
      else
	{
	  this->_track = false;
	  this->_pos = glm::vec3(0, this->_zoom, -0.01);
	  this->_lookAt = glm::vec3(0, 0, 0);
	}
    }
}

void		Camera::draw()
{
  this->_projection = glm::perspective(60.f, 1920.0f/1080.0f, 0.001f, 10000.0f);
  this->_transformation = glm::lookAt(this->_pos, this->_lookAt, glm::vec3(0, 2, 0));
  this->_shader.bind();
  this->_shader.setUniform("view", this->_transformation);
  this->_shader.setUniform("projection", this->_projection);
}

void		Camera::drawOrtho()
{
  this->_projection = glm::mat4(1);
  this->_transformation = glm::mat4(1);
  this->_shader.bind();
  this->_shader.setUniform("view", this->_transformation);
  this->_shader.setUniform("projection", this->_projection);
}

glm::vec3 const	&Camera::getPos() const
{
  return _pos;
}

void		Camera::setPos(glm::vec3 const &pos)
{
  this->_pos = pos;
}
