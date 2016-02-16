//
// MParsing.cpp for MParsing in /home/odet_a/Menu
//
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
//
// Started on  Mon May 18 11:05:54 2015 Alexandre Odet
// Last update Fri May 22 12:54:19 2015 Alexandre Odet
//

#include "MParsing.hh"

#include <fstream>

std::string	const & MParsing::getMapName()
{
  return this->_nameMap;
}

void	MParsing::setMapName(const std::string & name)
{
  this->_nameMap = name;
}

void	MParsing::setNbPlayers(const int n)
{
  this->_nbPlayers = n;
}

int	MParsing::getNbPlayers() const
{
  return this->_nbPlayers;
}

void	MParsing::setNbBots(const int n)
{
  this->_nbBots = n;
}

int	MParsing::getNbBots() const
{
  return this->_nbBots;
}

int	MParsing::myStrchr(char c, const char *s)
{
  int	i;
  int	occur;

  i = 0;
  occur = 0;
  while (s[i] != '\0')
    {
      if (s[i] == c)
	occur++;
      i++;
    }
  return (occur);
}

void	MParsing::handle_line(const std::list<std::string> & _infoSave)
{
  std::list<std::string>::const_iterator	listIt;
  int		IA = 0;
  int		gamer = 0;

  listIt = _infoSave.begin();
  this->setMapName(*listIt);
  while (listIt != _infoSave.end())
    {
      IA += this->myStrchr(AI, listIt->c_str());
      gamer += this->myStrchr(PLAYER, listIt->c_str());
      ++listIt;
    }
  this->setNbBots(IA);
  this->setNbPlayers(gamer);
}

void	MParsing::parse(const std::string & nameMap)
{

  std::ifstream	file;
  std::string	tmp;

  std::string completename = std::string("save/" + nameMap);

  file.open(completename.c_str());
  if (file.is_open())
    {
      while (getline(file, tmp))
	this->_infoSave.push_back(tmp);
    }
  this->handle_line(this->_infoSave);
  file.close();
}

MParsing::MParsing(const std::string & nameMap)
{
  this->parse(nameMap);
}

MParsing::~MParsing()
{}
