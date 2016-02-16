//
// Pause.hh for Pause in /home/bourre_l/rendu/cpp_bomberman/Game
//
// Made by bourrel léo
// Login   <bourre_l@epitech.net>
//
// Started on  Mon Jun 01 08:46:09 2015 bourrel léo
// Last update Sat Jun 13 17:17:27 2015 bourrel léo
//

#ifndef	PAUSE_HH
#define	PAUSE_HH

#include <SdlContext.hh>
#include <Input.hh>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Plan.hh"
#include "Camera.hh"

class MyGame;

class	Pause
{
public:
  Pause(MyGame *);
 ~Pause();

public:
  void		update(gdl::Clock const &clock, gdl::Input &input);
  void		draw(gdl::AShader &shader,gdl::Clock const &clock);

private:
  void		back() const;
  void		quit() const;
  void		save() const;

private:
  std::map<int, void(Pause::*)() const>	_fctList;
  std::vector<Plan*>			_obj;
  int					_curPos;
  MyGame				*_game;
};

#endif
