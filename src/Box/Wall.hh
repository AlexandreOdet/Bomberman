#ifndef	WALL_HH_
#define	WALL_HH_

#include "Cube.hh"
#include "ABox.hh"

class Wall : public ABox
{
public:
  Wall(glm::vec3 const &pos);
  ~Wall();

  void	draw(gdl::AShader &shader,gdl::Clock const &clock);
  void	update(gdl::Clock const &clock, gdl::Input &input);
  bool	checkCollide(glm::vec3 const &pos);
};

#endif /* WALL_HH_ */
