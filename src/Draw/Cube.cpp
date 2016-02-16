#include "Cube.hh"
#include "MyGame.hh"

gdl::Geometry	*Cube::_geometry = new gdl::Geometry();
bool		Cube::is_init = false;

Cube::Cube(float size, glm::vec3 const &pos, std::string const &texture)
{

  this->_speed = 20.0f;
  setPosition(pos);
  setRotation(glm::vec3(0, 0, 0));
  setScale(glm::vec3(size, size, size));
  this->_texture = Gtexture[texture];
  initialize();
}

void	Cube::initialize()
{
  if (!is_init)
    {
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      setUV();

      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      setUV();

      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
      setUV();

      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      setUV();

      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      setUV();

      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      setUV();

      this->_geometry->build();
      is_init = true;
    }
}

void	Cube::setUV()
{
  this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
}

void	Cube::draw(gdl::AShader &shader,gdl::Clock const &clock)
{
  (void)clock;
  this->_texture->bind();
  this->_geometry->draw(shader, getTransformation(), GL_QUADS);
}
