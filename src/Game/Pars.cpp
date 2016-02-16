#include "Pars.hh"

Pars::Pars()
{
}

Pars::~Pars()
{
}

void		Pars::addObject(char const &type, int const x, int const z, int const line)
{
  if (type ==  '0')
    {
      _map.push_back(new Empty(glm::vec3(x, -0.5, z), false));
      this->_isEmpty++;
    }
  else if (type ==  '1')
    _map.push_back(new Box(glm::vec3(x, 0, z)));
  else if (type ==  '2')
    _map.push_back(new Wall(glm::vec3(x, 0, z)));
  else
    throw ParseError("Invalid number", line);
}

void		Pars::checkMap()
{
  if (_width < 10 || _height < 10)
    throw ParseError("Map must be at least 10 x 10", -1);
  if (_isEmpty < 10)
    throw ParseError("Map must have at least 10 empty cases", -1);
}

void		Pars::parcours_list(std::list<std::string> const &list)
{
  int		i = list.size();
  int		j;
  int		line = 0;

  this->_isEmpty = 0;
  for (std::list<std::string>::const_iterator l = list.begin(); l != list.end(); l++)
    {
      j = l->length();
      for (std::string::const_iterator s = l->begin(); s != l->end(); s++)
	{
	  addObject(*s, ((_width / 2) - j), (i - (_height / 2)), line);
	  j--;
	}
      line++;
      i--;
    }
  checkMap();
}

void		Pars::parcours_list(std::list<std::string> const &list, int const height, int const width)
{
  int		i = list.size();
  int		j;
  int		line = 0;

  this->_isEmpty = 0;
  this->_width = width;
  this->_height = height;
  for (std::list<std::string>::const_iterator l = list.begin(); l != list.end(); l++)
    {
      j = l->length();
      for (std::string::const_iterator s = l->begin(); s != l->end(); s++)
	{
	  addObject(*s, ((_height / 2) - i), (j - (_width / 2)), line);
	  j--;
	}
      line++;
      i--;
    }
  checkMap();
}

void		Pars::start(std::string const &filename)
{
  std::list<std::string>	list;
  std::string		line;
  std::ifstream		myfile;
  int			first = 1;

  this->_height = 0;
  myfile.open(filename.c_str());
  if (myfile.is_open())
    {
      while (getline(myfile, line))
	{
	  if (first == 1)
	    {
	      _width = line.length();
	      first = 0;
	    }
	  else
	    {
	      if (_width != static_cast<int>(line.length()))
		throw ParseError("Incorrect line length", _height);
	    }
	  list.push_back(*(new std::string(line)));
	  _height += 1;
	}
      myfile.close();
      parcours_list(list);
    }
  else
    throw ParseError("Invalid file", -1);
}

void			Pars::setWidth(int const s)
{
  _width = s;
}

int			Pars::getWidth() const
{
  return _width;
}

void			Pars::setHeight(int const s)
{
  _height = s;
}

int			Pars::getHeight() const
{
  return _height;
}

std::vector<ABox *>	Pars::getMap() const
{
  return _map;
}
