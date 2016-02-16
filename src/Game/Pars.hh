#ifndef __PARS_HH__
#define __PARS_HH__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

#include "Box.hh"
#include "Empty.hh"
#include "Wall.hh"
#include "ABonus.hh"
#include "Exception.hpp"

class Pars
{
public:
  Pars();
  ~Pars();

  void			addObject(char const &type, int const x, int const z,
				  int const line);
  void			start(std::string const &f);
  std::vector<ABox *>	getMap() const;
  void			setWidth(int const s);
  int			getWidth() const;
  void			setHeight(int const s);
  int			getHeight() const;
  void			parcours_list(std::list<std::string> const &list, int const height, int const width);

private:
  void			parcours_list(std::list<std::string> const &list);
  void			checkMap();

private:
  std::vector<ABox *>	_map;
  int			_isEmpty;
  int			_width;
  int			_height;
};

#endif
