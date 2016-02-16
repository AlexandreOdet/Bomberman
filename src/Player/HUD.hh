//
// HUD.hh for HUD in /home/bourre_l/rendu/cpp_bomberman/Player
//
// Made by bourrel léo
// Login   <bourre_l@epitech.net>
//
// Started on  Fri Jun 05 17:52:11 2015 bourrel léo
// Last update Tue Jun  9 18:10:29 2015 bourrel léo
//

#ifndef	HUD_HH
#define	HUD_HH

#include <iostream>
#include <string>
#include "Plan.hh"

class	HUD
{
public:
  HUD(glm::vec3 const &, std::string const &);
  ~HUD();

  void		draw(gdl::AShader &, gdl::Clock const &);
  void		update(int const, int const, int const, float const, int const);
  Plan		*addPlan(float const &, glm::vec3 const &, std::string const &) const;

private:
  Plan			*_obj;
  Plan			*_player;
  std::vector<Plan*>	_num;

  std::vector<Plan*>	_score;
  glm::vec3		_pos;

  int			_s;
  int			_bomb;
  int			_life;
  int			_pow;
  float			_speed;
};

#endif
