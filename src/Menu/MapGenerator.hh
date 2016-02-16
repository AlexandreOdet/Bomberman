//
// MapGenerator.hh for MapGenerator_HEADER in /home/odet_a/MapGenerator
//
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
//
// Started on  Fri May 29 15:28:03 2015 Alexandre Odet
// Last update Mon Jun  1 21:02:59 2015 Alexandre Odet
//

#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <iostream>
#include <list>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include "Generator.hh"
#include <fstream>

class	Map
{
public:
  Map(const int, const int);
  ~Map();
  std::string getNameMap() const;
private:

  std::list<std::string> _list;
  GenereNumber		*_val;
  std::string		_filename;

  std::string getDate() const;
  void	addToList(std::string const &);
  void	show() const;
  std::string genereLine(const int, const int) const;
};

#endif /* MAPGENERATOR_H */
