#ifndef CUBE_HH_
#define CUBE_HH_

#include "AObject.hpp"

class Cube : public AObject
{
public:
  Cube(float size, glm::vec3 const &pos, std::string const &texture);
  virtual ~Cube() { }

  virtual void	initialize();
  virtual void	setUV();
  virtual void	draw(gdl::AShader &shader,gdl::Clock const &clock);

private:
  gdl::Texture		*_texture;
  static gdl::Geometry	*_geometry;
  static bool		is_init;
  float			_speed;
};

#endif /* CUBE_HH_ */
