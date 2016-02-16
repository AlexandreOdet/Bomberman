#include "MyGame.hh"

MyGame::MyGame(std::list<int> const &info, std::list<std::string> const &map)
{
  if (map.size() == 3)
    {
      this->_map = map.back();
      this->_theme = "defaut";
      this->_load = true;
    }
  else
    {
      this->_nbplayer =  info.front();
      this->_nbia = info.back();
      this->_map = "map/" + map.front();
      this->_theme = map.back();
      this->_loader = NULL;
      this->_load = false;
    }
  son = GSound["game"];
}

MyGame::~MyGame()
{
  Plan	*result;

  if (_players.size() < 2 && _players[0]->getName() != "IA")
    result = new Plan(2, glm::vec3(0, 0, 0), "win");
  else
    result = new Plan(2, glm::vec3(0, 0, 0), "loose");
  result->rotate(glm::vec3(0, 1, 0), 90);
  result->rotate(glm::vec3(0, 0, 1), -90);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();

  result->update(_clock, _input);
  this->_camera->drawOrtho();
  result->draw(_shader, _clock);

  Sound::stop(son);
  _context.flush();
  std::this_thread::sleep_for(std::chrono::seconds(2));

  delete result;
  for(size_t i = 0; i < _objects.size(); ++i)
    delete _objects[i];
  for(size_t i = 0; i < _bomb.size(); ++i)
    delete _bomb[i];
  for(size_t i = 0; i < _players.size(); ++i)
    delete _players[i];
  if (_pause)
    delete _pause;
  if (_loader)
    delete _loader;
  if (_camera)
    delete _camera;
}

bool		MyGame::initialize()
{
  if (!_context.start(1920, 1080, "Bomberman"))
    throw GameError("Error while initializing context");
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./lib/LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./lib/LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    throw GameError("Error while initializing shaders");
  glAlphaFunc(GL_GREATER, 0.1f);
  glEnable(GL_ALPHA_TEST);

  new Ressource(_theme);
  srand (time(NULL));
  this->_pause = new Pause(this);

  float z = 10;
  if (!_load)
    {
      this->_pars.start(this->_map);
      this->_objects = this->_pars.getMap();
      this->addPlayers();
      if (this->_pars.getWidth() > this->_pars.getHeight())
	z = this->_pars.getWidth();
      else
	z = this->_pars.getHeight();
    }
  else
    {
      _loader = new Loader(_map);
      this->_objects = this->_loader->getMap();
      this->_players = this->_loader->getPlayers();
      this->_nbplayer = this->_loader->getPlayerNbr();
      this->_nbia = this->_loader->getIANbr();
      if (this->_loader->getWidth() > this->_loader->getHeight())
  	z = this->_loader->getWidth();
      else
  	z = this->_loader->getHeight();
    }
  this->_camera = new Camera(glm::vec3(0, z, -0.01), glm::vec3(0, 0, 0), _shader);
  this->_camera->setZoom(z);
  this->_playing = false;
  Sound::play(son);
  return true;
}

void		MyGame::Save() const
{
  std::ofstream	savefile;
  glm::vec3	tmp;
  int		z = this->_pars.getWidth();
  int		jesus = 1;

  savefile.open (getDate());
  for (size_t i = 0; i < _objects.size(); ++i)
    {
      if (_objects[i]->getType() == "wall")
	savefile << "2";
      if (_objects[i]->getType() == "box")
	savefile << "1";
      if (_objects[i]->getType() == "empty")
	savefile << "0";
      if (jesus == z)
	{
	  jesus = 0;
	  savefile << std::endl;
	}
      jesus += 1;
    }
  for (size_t i = 0; i < _objects.size(); ++i)
    {
      if (_objects[i]->getType() == "empty")
	{
	  tmp = _objects[i]->getPos();
	  Empty *e = dynamic_cast<Empty*>(_objects[i]);
	  if (e->getBonus() == "bomb")
	    savefile << "bomb " << tmp.x <<" "<< tmp.y<<" "<< tmp.z << std::endl;
	  if (e->getBonus() == "life")
	    savefile << "life " << tmp.x <<" "<< tmp.y<<" "<< tmp.z << std::endl;
	  if (e->getBonus() == "power")
	    savefile << "power " << tmp.x <<" "<< tmp.y<<" "<< tmp.z << std::endl;
	  if (e->getBonus() == "speed")
	    savefile << "speed " << tmp.x <<" "<< tmp.y<<" "<< tmp.z << std::endl;
	}
    }
  for (std::vector<Player*>::const_iterator i = _players.begin(); i != _players.end(); ++i)
    {
      savefile << (*i)->getName() << " ";
      tmp = (*i)->getPosition();
      savefile << tmp.x << " " << tmp.y << " " << tmp.z << ", ";
      savefile << (*i)->getLife() << " " << (*i)->getPower() << " " << (*i)->getMaxBomb() << " " << (*i)->getSpeed() << std::endl;
    }
}

std::string	MyGame::getDate() const
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];

  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return ("save/" + std::string(buf));
}

void	MyGame::addPlayers()
{
  int ecart = (_pars.getWidth() * _pars.getHeight()) / (_nbplayer + _nbia + 1);
  size_t i = 0;
  glm::vec3 tmp;

  while (i < _objects.size())
    {
      if (_objects[i]->getSolid() == false)
	{
	  tmp = _objects[i]->getPos();
	  tmp.y = 0;
	  this->_players.push_back(new Player(tmp, "Player1"));
	  i += ecart;
	  break;
	}
      ++i;
    }
  if (_nbplayer == 2)
    {
      while (i < _objects.size())
	{
	  if (_objects[i]->getSolid() == false)
	    {
	      tmp = _objects[i]->getPos();
	      tmp.y = 0;
	      this->_players.push_back(new Player(tmp, "Player2"));
	      i += ecart;
	      break;
	    }
	  ++ i;
	}
    }
  for (int y = 0; y < _nbia; y++)
    {
      while (i < _objects.size())
	{
	  if (_objects[i]->getSolid() == false)
	    {
	      tmp = _objects[i]->getPos();
	      tmp.y = 0;
	      this->_players.push_back(new Player(tmp, "IA"));
	      i += ecart;
	      break;
	    }
	  ++i;
	}
    }
}

void	MyGame::setPlaying()
{
  this->_playing = false;
}

bool	MyGame::update()
{
  _context.updateInputs(_input);
  _context.updateClock(_clock);
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  if (!_playing)
    return dispGame();
  else
    return dispPause();
}

bool	MyGame::dispGame()
{
  if (_input.getKey(SDLK_p))
    _playing = true;
  this->_camera->update(_clock, _input, _players);
  for (std::vector<Bomb *>::iterator i = _bomb.begin(); i != _bomb.end();)
    {
      if ((*i)->update(&_objects, &_bomb, &_players, _clock) == 1)
	{
	  delete (*i);
	  _bomb.erase(i);
	}
      else
	i ++;
    }
  for (std::vector<Player*>::iterator i = _players.begin(); i != _players.end(); ++i)
    (*i)->update(_clock, _input, _objects, &_bomb, &_players);
  if (_players.size() > 1)
    return true;
  return false;
}

bool	MyGame::dispPause()
{
  std::this_thread::sleep_for (std::chrono::milliseconds(100));
  _pause->update(_clock, _input);
  return true;
}

void	MyGame::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  if (!_playing)
    {
      this->_camera->draw();
      for (size_t i = 0; i < _objects.size(); ++i)
	_objects[i]->draw(_shader, _clock);
      for (std::vector<Bomb *>::iterator y = _bomb.begin();  y != _bomb.end(); ++y)
	(*y)->draw(_shader, _clock, (*y)->getTransformation(), _clock.getElapsed());
      for (std::vector<Player*>::iterator i = _players.begin(); i != _players.end(); ++i)
	(*i)->draw(_shader, (*i)->getTransformation(), _clock.getElapsed());
      this->_camera->drawOrtho();
      for (std::vector<Player*>::iterator i = _players.begin(); i != _players.end(); ++i)
	if ((*i)->getName() == "Player1" || (*i)->getName() == "Player2")
	  (*i)->drawHUD(_shader, _clock);
    }
  else
    {
      this->_camera->drawOrtho();
      _pause->draw(_shader, _clock);
    }
  _context.flush();
}
