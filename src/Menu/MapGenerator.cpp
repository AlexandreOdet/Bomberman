//
// MapGenerator.cpp for MapGenerator in /home/odet_a/MapGenerator
//
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
//
// Started on  Fri May 29 15:27:44 2015 Alexandre Odet
// Last update Fri Jun 12 14:01:33 2015 bourrel léo
//

#include "MapGenerator.hh"

Map::Map(const int width, const int height)
{
  int	i;

  i = 0;

  this->_val = new GenereNumber();
  this->_filename = getDate();
  while (i < height)
    {
      this->addToList(genereLine(width, (i <(height - 1) && i != 0) ? 0 : 1));
      i++;
    }
  this->show();
}

std::string	Map::getDate() const
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];

  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return std::string(buf);
}

std::string	Map::genereLine(const int width, const int isEnd) const
{
  char	str[width];
  int	i;
  int	tmp;

  i = 0;
  if (isEnd == 1)
    {
      while (i < width)
	{
	  str[i] = '2';
	  i++;
	}
      str[i] = 0;
    }
  else
    {
      while (i < width)
	{
	  if ((i > 0 && i < (width - 1)))
	    {
	      tmp = (*this->_val)(0, width) % 6;
		str[i] = (tmp == 4 || tmp == 5) ? '1' : '0';
	    }
	  else
	    str[i] = '2';
	  i++;
	}
      str[i] = 0;
    }
  std::string line(str);
  return line;
}

void	Map::addToList(std::string const & line)
{
  this->_list.push_back(line);
}

std::string Map::getNameMap() const
{
  return this->_filename;
}

void	Map::show() const
{
  std::string complete("map/" + this->_filename + ".map");
  std::ofstream outfile (complete);

  std::list<std::string>::const_iterator it;

  it = this->_list.begin();
  while (it != this->_list.end())
    {
      outfile << (*it) << std::endl;
      ++it;
    }
  outfile.close();
}

Map::~Map()
{}
