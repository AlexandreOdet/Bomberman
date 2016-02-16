#ifndef MSETTING_H
#define MSETTING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <SDL/SDL.h>

#include <iostream>
#include <list>
#include <dirent.h>
#include <fstream>
#include <map>

#include "Exception.hpp"
#include "MParsing.hh"

class	MSetting
{
public:
  MSetting(const std::string &, SDL_Texture *);
  ~MSetting();

  SDL_Texture *getSurface() const;
  void		setSurface(SDL_Texture *);

  std::string 	getMap() const;
  void		setMap(std::string const &);

private:
  std::string	_val;
  SDL_Texture	*_p;
};

#endif /* MSETTING_H */
