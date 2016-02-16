//
// MParsing.hh for MParsing in /home/odet_a/Menu
// 
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
// 
// Started on  Mon May 18 11:06:56 2015 Alexandre Odet
// Last update Fri May 22 12:35:35 2015 Alexandre Odet
//

#ifndef MPARSING_H
#define MPARSING_H

#include <exception>
#include <iostream>
#include <list>
#include <dirent.h>
#include <fstream>
#include <map>
#include <cstdio>

# define PLAYER '4'
# define AI '5'

class	MPError : public std::exception
{
private:
  std::string	s;
public:
  MPError(std::string const & str = "") throw() : s(str) {}
  virtual ~MPError() throw () {}
  virtual const char *what() const throw()
  {
    return s.c_str();
  }
};

class	MParsing
{
public:
  MParsing(const std::string &);
  ~MParsing();

  int			getNbBots() const;
  void			setNbBots(const int);

  std::string const &	getMapName();
  void			setMapName(const std::string &);

  int			getNbPlayers() const;
  void			setNbPlayers(const int);

private:
  std::string	_nameMap;
  int		_nbPlayers;
  int		_nbBots;
  std::list<std::string>	_infoSave;

  void		parse(const std::string &);
  void		handle_line(const std::list<std::string> &);
  int		myStrchr(char, const char *);
};

#endif /* MPARSING_H */
