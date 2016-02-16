#ifndef __BOMB_HH__
#define __BOMB_HH__

#include "Clock.hh"
#include "Cube.hh"

#include "Empty.hh"
#include "Box.hh"
#include "Wall.hh"
#include "ABonus.hh"
#include "Player.hh"
#include "Sound.hh"

class Bomb
{
public:
  Bomb(glm::vec3 const &pos, int const power, Player *p);
  ~Bomb();

public:
  int		getExplode() const;
  int		getRange() const;
  glm::vec3	getPos() const;
  glm::mat4	getTransformation() const;
  void		draw(gdl::AShader &, gdl::Clock const &, glm::mat4 const &, double);
  int		update(std::vector<ABox*> *, std::vector<Bomb *> const*,
		       std::vector<Player *> *,gdl::Clock const &);

private:
  int		buildFire(std::vector<ABox*> *, float const, char const,
			  std::vector<Bomb *>  const*, std::vector<Player *> *);
  void		activeExplode();

private:
  gdl::Model		*_model;
  glm::vec3		_rotation;
  glm::vec3		_pos;
  glm::vec3		_scale;
  int			_range;
  Player		*_owner;
  int			_explode;
  std::vector<Cube *>	_fs;
  double		_time;
  FMOD_SOUND		*son;
};

#endif
