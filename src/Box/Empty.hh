#ifndef	EMPTY_HH_
#define	EMPTY_HH_

#include "Cube.hh"
#include "ABox.hh"
#include "Plan.hh"

class Empty : public ABox
{
public:
  Empty(glm::vec3 const &pos, bool isBonus);
  Empty(glm::vec3 const &pos, std::string const &b);
  ~Empty();

  void		draw(gdl::AShader &shader,gdl::Clock const &clock);
  void		update(gdl::Clock const &clock, gdl::Input &input);
  void		BombBonus();
  void		RangeBonus();
  void		SpeedBonus();
  void		LifeBonus();
  void		DeleteBonus();
  std::string	getBonus() const;

private:
  Abonus	*_bonus;
};

#endif /* EMPTY_HH_ */
