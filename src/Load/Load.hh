//
// Loader.hh for Loader_BOMBERMAN in /home/odet_a/cpp_bomberman
// 
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
// 
// Started on  Fri Jun  5 19:51:03 2015 Alexandre Odet
// Last update Fri Jun 12 18:47:08 2015 bourrel léo
//

#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <exception>

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

#include "Exception.hpp"
#include "Pars.hh"
#include "Player.hh"

class	Loader
{
public:
  Loader(const std::string &);
  ~Loader();

  int				getWidth() const;
  int				getHeight() const;
  std::vector<Player*> const	getPlayers() const;
  std::vector<ABox*> const	getMap() const;
  int				getIANbr();
  int				getPlayerNbr();

private:
  void				addPlayer(std::string line, std::string const &who);
  void				addBonus(std::string line, std::string const &who);
  void				parse(const std::string &);
  void				fillMap(std::string const &line);

private:
  std::vector<std::pair<std::string, glm::vec3> >	_bonus;
  std::vector<Player*>		_players;
  std::list<std::string>	_map;
  int				_width;
  int				_height;
};

#endif /* LOADER_H */
