//
// Loader.cpp for Loader_BOMBERMAN_CODE in /home/odet_a/Loader
//
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
//
// Started on  Fri Jun  5 20:01:42 2015 Alexandre Odet
// Last update Fri Jun 12 18:47:10 2015 bourrel léo
//

#include "Load.hh"

Loader::Loader(const std::string &file)
{
  std::string			filename("save/" + file);
  std::list<std::string>	list;
  std::string			line;
  std::ifstream			myfile;
  int				first = true;
  bool				map = true;

  this->_height = 0;
  myfile.open(filename.c_str());
  if (myfile.is_open())
    {
      while (getline(myfile, line))
	{
	  if (first)
	    {
	      _width = line.length();
	      first = false;
	    }
	  if (map && line[0] == '2')
	    fillMap(line);
	  else
	    parse(line);
	}
      myfile.close();
    }
  else
    throw ParseError("Invalid file", -1);
}

Loader::~Loader()
{}

void	Loader::fillMap(std::string const &line)
{
  if (_width != static_cast<int>(line.length()))
    throw ParseError("Incorrect line length", _height);
  _map.push_back(*(new std::string(line)));
  _height += 1;
}

void	Loader::addPlayer(std::string line, std::string const &who)
{
  glm::vec3	pos;
  std::string	x(""), y("0"), z("");
  int		SSpeed, Slife, SBomb, SPower;

  line.erase(0, who.length() + 1);
  x = line.substr(0, line.find_first_of(" "));
  if (x[x.length() - 1] == ' ')
    x.resize(x.length() - 1);
  line.erase(line.begin(), (line.begin() + line.find_first_of(" ")) + 1);
  line.erase(line.begin(), (line.begin() + line.find_first_of(" ")) + 1);
  z = line.substr(0, line.find_first_of(","));
  line.erase(line.begin(), (line.begin() + line.find_first_of(",")) + 2);
  pos.x = std::atof(x.c_str());
  pos.y = std::atof(y.c_str());
  pos.z = std::atof(z.c_str());
  Slife = std::atoi(line.substr(0, line.find_first_of(" ")).c_str());
  line.erase(0, line.find_first_of(" ") + 1);
  SPower = std::atoi(line.substr(0, line.find_first_of(" ")).c_str());
  line.erase(0, line.find_first_of(" ") + 1);
  SBomb = std::atoi(line.substr(0, line.find_first_of(" ")).c_str());
  line.erase(0, line.find_first_of(" ") + 1);
  SSpeed = std::atoi(line.substr(0, line.find_first_of(" ")).c_str());
  if (Slife == -1 || SPower == -1 || SBomb == -1 || SSpeed == -1)
    throw ParseError("Error happened", -1);
  else
    this->_players.push_back(new Player(pos, who, SPower, SSpeed, Slife, SBomb));
}

void	Loader::addBonus(std::string line, std::string const &who)
{
  glm::vec3	pos;
  std::string	x(""), y("-0.5"), z("");

  line.erase(0, who.length() + 1);
  x = line.substr(0, line.find_first_of(" "));
  if (x[x.length() - 1] == ' ')
    x.resize(x.length() - 1);
  line.erase(line.begin(), (line.begin() + line.find_first_of(" ")) + 1);
  line.erase(line.begin(), (line.begin() + line.find_first_of(" ")) + 1);
  z = line.substr(0, line.find_first_of(","));
  line.erase(line.begin(), (line.begin() + line.find_first_of(",")) + 2);
  pos.x = std::atof(x.c_str());
  pos.y = std::atof(y.c_str());
  pos.z = std::atof(z.c_str());
  this->_bonus.push_back(make_pair(who, pos));
}

void	Loader::parse(const std::string &line)
{
  std::string	who("");

  who = line.substr(0, line.find_first_of(" "));
  if (who == "Player1" || who == "Player2" || who == "IA")
    addPlayer(line, who);
  else if (who == "speed" || who == "bomb" || who == "life" || who == "power")
    addBonus(line, who);
  else
    throw ParseError("Error happened", -1);
}

std::vector<Player*> const	Loader::getPlayers() const
{
  return this->_players;
}

std::vector<ABox*> const	Loader::getMap() const
{
  std::vector<ABox*>	tmp;
  Pars *p = new Pars();

  p->parcours_list(this->_map, this->_height, this->_width);
  tmp = p->getMap();
  for (int i = 0; i < static_cast<int>(tmp.size()); ++i)
    {
      for (int j = 0; j < static_cast<int>(this->_bonus.size()); ++j)
	{
	  if (tmp[i]->getType() == "empty" && _bonus[j].second == tmp[i]->getPos())
	    {
	      glm::vec3	pos;
	      pos = tmp[i]->getPos();
	      tmp[i] = new Empty(pos, _bonus[j].first);
	    }
	}
    }
  delete p;
  return tmp;
}

int	Loader::getWidth() const
{
  return _width;
}

int	Loader::getHeight() const
{
  return _height;
}

int	Loader::getIANbr()
{
  int	ret = 0;

  for (int i = 0; i < static_cast<int>(_players.size()); i++)
    if (_players[i]->getName() == "IA")
      ret++;
  return ret;
}

int	Loader::getPlayerNbr()
{
  int	ret = 0;

  for (int i = 0; i < static_cast<int>(_players.size()); i++)
    if (_players[i]->getName() != "IA")
      ret++;
  return ret;
}
