//
// Ressource.hh for Ressource in /home/bourre_l/rendu/cpp_bomberman/Game
//
// Made by bourrel léo
// Login   <bourre_l@epitech.net>
//
// Started on  Fri May 29 16:18:02 2015 bourrel léo
// Last update Sat Jun 13 14:54:08 2015 bourrel léo
//

#ifndef	RESSOURCE_HH
#define	RESSOURCE_HH

#include <iostream>
#include <sstream>
#include <string>
#include <Model.hh>
#include <Texture.hh>

#include <map>
#include <vector>
#include "Exception.hpp"

extern std::map<std::string, gdl::Texture*> Gtexture;

class	Ressource
{
public:
  Ressource(std::string const &theme = "defaut");
  ~Ressource();

private:
  void		setBonus();
  void		setOther();
  void		setNumero();
  void		setPause();

  void		setDefault();
  void		setMinecraft();
  void		setVolcano();
  void		setMarine();

private:
  gdl::Texture  *_ground;
  gdl::Texture	*_fire;
  gdl::Texture	*_box;
  gdl::Texture	*_wall;
  gdl::Texture	*_bomb;

  gdl::Texture	*_Bspeed;
  gdl::Texture	*_Bbomb;
  gdl::Texture	*_Blife;
  gdl::Texture	*_Brange;

  gdl::Texture	*_back;
  gdl::Texture	*_quit;
  gdl::Texture	*_save;
  gdl::Texture	*_back2;
  gdl::Texture	*_quit2;
  gdl::Texture	*_save2;

  gdl::Texture	*_hud;
  gdl::Texture	*_win;
  gdl::Texture	*_loose;

  std::vector<gdl::Texture*>	_num;
};

#endif
