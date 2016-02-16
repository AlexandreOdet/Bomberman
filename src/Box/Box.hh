#ifndef	BOX_HH_
#define	BOX_HH_

#include "Cube.hh"
#include "ABox.hh"

class Box : public ABox
{
public:
  Box(glm::vec3 const &pos);
  ~Box();

  void	draw(gdl::AShader &shader,gdl::Clock const &clock);
  void	update(gdl::Clock const &clock, gdl::Input &input);
};

#endif /* BOX_HH_ */
