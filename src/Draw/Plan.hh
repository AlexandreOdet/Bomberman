#ifndef PLAN_HH_
#define PLAN_HH_

#include "AObject.hpp"

class Plan : public AObject
{
public:
  Plan(float const size, glm::vec3 const &pos, std::string const &texture);
  virtual ~Plan() { };

  virtual void	initialize();
  virtual void	setUV();
  virtual void	draw(gdl::AShader &shader,gdl::Clock const &clock);
  void		changeTexture(std::string const &texture);

private:
  gdl::Texture	*_texture;
  static gdl::Geometry	*_geometry;
  static bool		is_init;
  float		_speed;
};

#endif /* PLAN_HH_ */
