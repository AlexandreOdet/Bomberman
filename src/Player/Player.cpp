#include "Player.hh"
#include "MyGame.hh"
#include "Bomb.hh"
#include <math.h>

static int	min_x = 0;
static int	min_y = 0;
static int	max_x = 0;
static int	max_y = 0;

Player::Player(glm::vec3 const &pos, std::string const &name)
  : _position(pos),  _rotation(0, 0, 0), _scale(0.002, 0.002, 0.002)
{
  this->_model = new gdl::Model;

  if (!this->_model->load("./ressource/theme/defaut/marvin/marvin.fbx"))
    throw ResError("./ressource/theme/defaut/marvin/marvin.fbx");

  this->_name = name;
  if (name == "Player1")
    _hud = new HUD(glm::vec3(-0.7, 0, -0.7), "1");
  if (name == "Player2")
    _hud = new HUD(glm::vec3(-0.7, 0, 0.9), "2");

  this->_speed = 2.0f;
  this->_currentbomb = 0;
  this->_maxbomb = 2;
  this->_life = 1;
  this->_power = 2;
  this->_score = 0;

  this->_running = false;
  this->_model->createSubAnim(0, "wait", 0 , 0);
  this->_model->createSubAnim(0, "start_run", 1 , 38);
  this->_model->createSubAnim(0, "run", 35 , 53);
  this->_model->createSubAnim(0, "break", 55 , 120);

  this->_bonusMap[LIFE] = &Player::upLife;
  this->_bonusMap[SPEED] = &Player::upMs;
  this->_bonusMap[RANGE] = &Player::upPower;
  this->_bonusMap[BOMB] = &Player::upNumber;
  this->goToX = 2147483647;
  this->goToY = 2147483647;
  this->IA_map = NULL;
}

Player::Player(glm::vec3 const &pos, std::string const &name, int p, int s, int l, int m)
  : _position(pos),  _rotation(0, 0, 0), _scale(0.002, 0.002, 0.002)
{
  this->_model = new gdl::Model;

  if (!this->_model->load("./ressource/theme/defaut/marvin/marvin.fbx"))
    throw ResError("./ressource/theme/defaut/marvin/marvin.fbx");

  this->_name = name;
  if (name == "Player1")
    _hud = new HUD(glm::vec3(-0.7, 0, -0.7), "1");
  if (name == "Player2")
    _hud = new HUD(glm::vec3(-0.7, 0, 0.9), "2");

  this->_speed = static_cast<float>(s);
  this->_currentbomb = 0;
  this->_maxbomb = m;
  this->_life = l;
  this->_power = p;
  this->_score = 0;

  this->_running = false;
  this->_model->createSubAnim(0, "wait", 0 , 0);
  this->_model->createSubAnim(0, "start_run", 1 , 38);
  this->_model->createSubAnim(0, "run", 35 , 53);
  this->_model->createSubAnim(0, "break", 55 , 120);

  this->_bonusMap[LIFE] = &Player::upLife;
  this->_bonusMap[SPEED] = &Player::upMs;
  this->_bonusMap[RANGE] = &Player::upPower;
  this->_bonusMap[BOMB] = &Player::upNumber;
  this->goToX = 2147483647;
  this->goToY = 2147483647;
  this->IA_map = NULL;
}

Player::~Player()
{
}

int	**Player::getMap() const
{
  return (this->IA_map);
}

float		Player::my_round(float nb) const
{
  float		tmp;
  int		mul;

  if (nb < 0)
    {
      mul = -1;
      tmp = -nb;
    }
  else
    {
      mul = 1;
      tmp = nb;
    }
  if (tmp - static_cast<int>(tmp) > 0.5)
    return (static_cast<int>(nb) + mul);
  else
    return static_cast<int>(nb);
}

glm::vec3	Player::getIntPosition() const
{
  glm::vec3	tmp;

  tmp.x = my_round(_position.x);
  tmp.z = my_round(_position.z);
  tmp.y = _position.y;
  return tmp;
}

std::string	Player::getName() const
{
  return this->_name;
}


int		Player::getPower() const
{
  return this->_power;
}

int		Player::getMaxBomb() const
{
 return this->_maxbomb;
}

int		Player::getSpeed() const
{
  return this->_speed;
}

glm::vec3 const	&Player::getPosition() const
{
  return _position;
}

void		Player::addScore(int const &s)
{
  _score += s;
}

int		Player::putBomb(std::vector<Bomb *> *bombig)
{
  if (_currentbomb < _maxbomb)
    {
      glm::vec3	tmp = getIntPosition();
      for (std::vector<Bomb *>::iterator i = bombig->begin(); i != bombig->end(); ++i)
	{
	  if ((*i)->getPos() == tmp)
	    return 1;
	}
      bombig->push_back(new Bomb(tmp, _power, this));
      _currentbomb += 1;
      return 1;
    }
  else
    return 0;
}

void		Player::BonusUpdate(int const b, ABox *box)
{
  void		(Player::*ptr)();

  if ((ptr = this->_bonusMap[b]))
    {
      (this->*ptr)();
      box->DeleteBonus();
    }
}

void		Player::translate(glm::vec3 const &v)
{
  this->_position += v;
}

void		Player::rotate(glm::vec3 const &axis, float angle)
{
  this->_rotation = axis * angle;
}

void		Player::isRunning()
{
  if (this->_running == false)
    {
      this->_model->setCurrentSubAnim("run", true);
      this->_running = true;
    }

}

void		Player::wait()
{
  if (this->_running == true)
    {
      this->_model->setCurrentSubAnim("wait", true);
      this->_running = false;
    }
}

void		Player::moveLeft(gdl::Clock const &clock)
{
  glm::vec3	tmp;

  isRunning();
  this->_rotation = glm::vec3(0, 90, 0);
  tmp = this->_position + glm::vec3(1, 0, 0);
  for (std::vector<ABox*>::iterator it = _listObj.begin(); it != _listObj.end(); ++it)
    {
      if  ((tmp.x > ((*it)->getPos().x + 0.3) && tmp.x < ((*it)->getPos().x + 0.7))
	  && (tmp.z > ((*it)->getPos().z - 0.5) && tmp.z < ((*it)->getPos().z + 0.5)))
	{
	  if ((*it)->getSolid() == true)
	    return;
	  else if ((*it)->getBonusType() != EMPTY)
	    BonusUpdate((*it)->getBonusType(), (*it));
	}
    }
  for (std::vector<Bomb*>::iterator it = _listBomb->begin(); it != _listBomb->end(); ++it)
    {
      if ((tmp.x > ((*it)->getPos().x + 0.2) && tmp.x < ((*it)->getPos().x + 0.8))
	  && (tmp.z > ((*it)->getPos().z - 0.5) && tmp.z < ((*it)->getPos().z + 0.5)))
	return;
    }
  translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * this->_speed);
}

void		Player::moveRight(gdl::Clock const &clock)
{
  glm::vec3	tmp;

  isRunning();
  this->_rotation = glm::vec3(0, -90, 0);
  tmp = this->_position + glm::vec3(-1, 0, 0);
  for (std::vector<ABox*>::iterator it = _listObj.begin(); it != _listObj.end(); ++it)
    {
      if ((tmp.x > ((*it)->getPos().x - 0.7) && tmp.x < ((*it)->getPos().x - 0.3))
	  && (tmp.z > ((*it)->getPos().z - 0.5) && tmp.z < ((*it)->getPos().z + 0.5)))
	{
	  if ((*it)->getSolid() == true)
	    return;
	  else if ((*it)->getBonusType() != EMPTY)
	    BonusUpdate((*it)->getBonusType(), (*it));
	}
    }
  for (std::vector<Bomb*>::iterator it = _listBomb->begin(); it != _listBomb->end(); ++it)
    {
      if ((tmp.x > ((*it)->getPos().x - 0.8) && tmp.x < ((*it)->getPos().x - 0.2))
	  && (tmp.z > ((*it)->getPos().z - 0.5) && tmp.z < ((*it)->getPos().z + 0.5)))
	return;
    }
  translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * this->_speed);
}

void		Player::moveUp(gdl::Clock const &clock)
{
  glm::vec3	tmp;

  isRunning();
  this->_rotation = glm::vec3(0, 0, 0);
  tmp = this->_position + glm::vec3(0, 0, 1);
  for (std::vector<ABox*>::iterator it = _listObj.begin(); it != _listObj.end(); ++it)
    {
      if ((tmp.x > ((*it)->getPos().x - 0.5) && tmp.x < ((*it)->getPos().x + 0.5))
	  && (tmp.z > ((*it)->getPos().z + 0.4) && tmp.z < ((*it)->getPos().z + 1.5)))
	{
	  if ((*it)->getSolid() == true)
	    return;
	  else if ((*it)->getBonusType() != EMPTY)
	    BonusUpdate((*it)->getBonusType(), (*it));
	}
    }
  for (std::vector<Bomb*>::iterator it = _listBomb->begin(); it != _listBomb->end(); ++it)
    {
      if ((tmp.x > ((*it)->getPos().x - 0.5) && tmp.x < ((*it)->getPos().x + 0.5))
	  && (tmp.z > ((*it)->getPos().z + 0.5) && tmp.z < ((*it)->getPos().z + 1.5)))
	{
	  if (_position.z < ((*it)->getPos().z - 0.4))
	    return;
	}
    }
  translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * this->_speed);
}

void		Player::moveDown(gdl::Clock const &clock)
{
  glm::vec3	tmp;

  isRunning();
  _rotation = glm::vec3(0, 180, 0);
  tmp = this->_position + glm::vec3(0, 0, -1);
  for (std::vector<ABox*>::iterator it = _listObj.begin(); it != _listObj.end(); ++it)
    {
      if ((tmp.x > ((*it)->getPos().x - 0.5) && tmp.x < ((*it)->getPos().x + 0.5))
	  && (tmp.z > ((*it)->getPos().z - 1.5) && tmp.z < ((*it)->getPos().z - 0.4)))
	{
	  if ((*it)->getSolid() == true)
	    return;
	  else if ((*it)->getBonusType() != EMPTY)
	    BonusUpdate((*it)->getBonusType(), (*it));
	}
    }
  for (std::vector<Bomb*>::iterator it = _listBomb->begin(); it != _listBomb->end(); ++it)
    {
      if ((tmp.x > ((*it)->getPos().x - 0.5) && tmp.x < ((*it)->getPos().x + 0.5))
	  && (tmp.z > ((*it)->getPos().z - 1.5) && tmp.z < ((*it)->getPos().z - 0.4)))
	{
	  if (_position.z > ((*it)->getPos().z + 0.4))
	    return;
	}
    }
  translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * this->_speed);
}

void		Player::update(gdl::Clock const &clock, gdl::Input &input,
			       std::vector<ABox*> const &listObj,
			       std::vector<Bomb*> *listBomb, std::vector<Player *> *listPlayer)
{
  int ai;

  this->_listObj = listObj;
  this->_listBomb = listBomb;
  if (_name == "Player1")
    {
      if (input.getKey(SDLK_SPACE))
	putBomb(listBomb);
      if (input.getKey(SDLK_z))
	moveUp(clock);
      else if (input.getKey(SDLK_s))
	moveDown(clock);
      else if (input.getKey(SDLK_q))
	moveLeft(clock);
      else if (input.getKey(SDLK_d))
	moveRight(clock);
      else
	wait();
      _hud->update(_maxbomb, _life, _power, _speed, _score);
    }
  if (_name == "Player2")
    {
      if (input.getKey(SDLK_KP_0))
	putBomb(listBomb);
      if (input.getKey(SDLK_UP))
	moveUp(clock);
      else if (input.getKey(SDLK_DOWN))
	moveDown(clock);
      else if (input.getKey(SDLK_LEFT))
	moveLeft(clock);
      else if (input.getKey(SDLK_RIGHT))
	moveRight(clock);
      else
	wait();
      _hud->update(_maxbomb, _life, _power, _speed, _score);
    }
  if (_name == "IA")
    {
      ai = IA(listObj, listBomb, listPlayer);
      if (ai == 1)
	moveUp(clock);
      else if (ai == 2)
	moveDown(clock);
      else if (ai == 3)
	moveLeft(clock);
      else if (ai == 4)
	moveRight(clock);
      else if (ai == 5)
	putBomb(listBomb);
      else
	wait();
    }
}

void	Player::create_map(std::vector<ABox*> const &listObj)
{
  int i = -1;
  std::vector<ABox*>::const_iterator debut = listObj.begin();
  std::vector<ABox*>::const_iterator fin = listObj.end();

  while (debut != fin)
    {
      if ((*debut)->getPos().x > max_x)
      	max_x = (*debut)->getPos().x;
      if ((*debut)->getPos().z > max_y)
      	max_y = (*debut)->getPos().z;
      if ((*debut)->getPos().x < min_x)
      	min_x = (*debut)->getPos().x;
      if ((*debut)->getPos().z < min_y)
      	min_y = (*debut)->getPos().z;
      ++debut;
    }
  this->IA_map = new int*[max_y - min_y - 1];
  while (++i < max_y - min_y - 1)
    this->IA_map[i] = new int[max_x - min_x - 1];
}

void	Player::update_map(std::vector<ABox*> const &listObj, std::vector<Bomb*> *listBomb, std::vector<Player*> *listPlayer)
{
  std::vector<ABox*>::const_iterator debut = listObj.begin();
  std::vector<ABox*>::const_iterator fin = listObj.end();
  std::vector<Bomb*>::iterator debut_bombes = listBomb->begin();
  std::vector<Bomb*>::iterator fin_bombes = listBomb->end();
  std::vector<Player*>::iterator debut_players = listPlayer->begin();
  std::vector<Player*>::iterator fin_players = listPlayer->end();
  int k;

  while (debut != fin)
    {
      if ((*debut)->getPos().x > min_x && (*debut)->getPos().z > min_y && (*debut)->getPos().x < max_x && (*debut)->getPos().z < max_y)
	{
	  if ((*debut)->getBonusType() != EMPTY)
	    this->IA_map[static_cast<int>((*debut)->getPos().z - min_y - 1)][static_cast<int>((*debut)->getPos().x - min_x - 1)] = 3;
	  else if ((*debut)->getSolid() == false)
	    this->IA_map[static_cast<int>((*debut)->getPos().z - min_y - 1)][static_cast<int>((*debut)->getPos().x - min_x - 1)] = 0;
	  else if ((*debut)->getBreakable() == true)
	    this->IA_map[static_cast<int>((*debut)->getPos().z - min_y - 1)][static_cast<int>((*debut)->getPos().x - min_x - 1)] = 2;
	  else
	    this->IA_map[static_cast<int>((*debut)->getPos().z - min_y - 1)][static_cast<int>((*debut)->getPos().x - min_x - 1)] = 1;
	}
      ++debut;
    }
  while (debut_players != fin_players)
    {
      this->IA_map[static_cast<int>((*debut_players)->getPosition().z - min_y - 1)][static_cast<int>((*debut_players)->getPosition().x - min_x - 1)] = 5;
      ++debut_players;
    }
  while (debut_bombes != fin_bombes)
    {
      this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] = 9;
      k = 0;
      while (++k <= (*debut_bombes)->getRange())
	{
	  if ((*debut_bombes)->getPos().z - min_y - 1 + k < max_y - min_y - 1 && (this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1 + k)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] == 0 || this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1 + k)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] == 5 || this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1 + k)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] == 3))
	    this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1 + k)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] = 8;
	  if ((*debut_bombes)->getPos().z - min_y - 1 - k >= 0 && (this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1 - k)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] == 0 || this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1 - k)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] == 3 || this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1 - k)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] == 5))
	    this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1 - k)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1)] = 8;
	  if ((*debut_bombes)->getPos().x - min_x - 1 + k < max_x - min_x - 1 && (this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1 + k)] == 0 || this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1 + k)] == 3 || this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1 + k)] == 5))
	    this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1 + k)] = 8;
	  if ((*debut_bombes)->getPos().x - min_x - 1 - k >= 0 && (this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1 - k)] == 0 || this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1 - k)] == 3 || this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1 - k)] == 5))
	    this->IA_map[static_cast<int>((*debut_bombes)->getPos().z - min_y - 1)][static_cast<int>((*debut_bombes)->getPos().x - min_x - 1 - k)] = 8;
	}
      ++debut_bombes;
    }
  this->IA_map[static_cast<int>(this->getPosition().z - min_y - 1)][static_cast<int>(this->getPosition().x - min_x - 1)] = 6;
}

int		Player::toTarget(float x, float y, float playerX, float playerY)
{
  if (playerX > x && playerX - x > 0.1)
    return (4);
  else if (playerX < x && playerX - x < -0.1)
    return (3);
  else if (playerY > y && playerY - y > 0.1)
    return (2);
  else if (playerY < y && playerY - y < -0.1)
    return (1);
  else
    return (0);
}

bool		Player::is_close(float x, float y)
{
  std::list<Player::Coordinates *>::iterator	debut, fin;

  debut = this->close_list.begin();
  fin = this->close_list.end();
  while (debut != fin)
    {
      if (static_cast<int>((*debut)->x) == static_cast<int>(x) && static_cast<int>((*debut)->y) == static_cast<int>(y))
	return true;
      ++debut;
    }
  return false;
}

bool		Player::is_open(float x, float y)
{
  std::list<Player::Coordinates *>::iterator	debut, fin;

  debut = this->open_list.begin();
  fin = this->open_list.end();
  while (debut != fin)
    {
      if (static_cast<int>((*debut)->x) == static_cast<int>(x) && static_cast<int>((*debut)->y) == static_cast<int>(y))
	return true;
      ++debut;
    }
  return false;
}

int		Player::Astar_aggressif()
{
  int						smallest_H = 2147483647;
  std::list<Player::Coordinates *>::iterator	debut, fin;
  int						tmpx = 0, tmpy = 0;

  debut = this->open_list.begin();
  fin = this->open_list.end();
  if (debut == fin)
    return 0;
  while (debut != fin)
    {
      if ((*debut)->heuristic < smallest_H)
	{
	  smallest_H = (*debut)->heuristic;
	  tmpx = (*debut)->x;
	  tmpy = (*debut)->y;
	}
      ++debut;
    }
  this->open_to_close(tmpx, tmpy, static_cast<int>(this->goToX), static_cast<int>(this->goToY));
  if (this->last_heuristic())
    return (1);
  if (this->addable(tmpx - 1, tmpy) && !(this->is_close(tmpx - 1, tmpy)) && !(this->is_open(tmpx - 1, tmpy)))
    this->open_add(tmpx - 1, tmpy, tmpx, tmpy, this->goToX, this->goToY);
  if (this->addable(tmpx + 1, tmpy) && !(this->is_close(tmpx + 1, tmpy)) && !(this->is_open(tmpx + 1, tmpy)))
    this->open_add(tmpx + 1, tmpy, tmpx, tmpy, this->goToX, this->goToY);
  if (this->addable(tmpx, tmpy - 1) && !(this->is_close(tmpx, tmpy - 1)) && !(this->is_open(tmpx, tmpy - 1)))
    this->open_add(tmpx, tmpy - 1, tmpx, tmpy, this->goToX, this->goToY);
  if (this->addable(tmpx, tmpy + 1) && !(this->is_close(tmpx, tmpy + 1)) && !(this->is_open(tmpx, tmpy + 1)))
    this->open_add(tmpx, tmpy + 1, tmpx, tmpy, this->goToX, this->goToY);
  return (this->Astar_aggressif());
}

void		Player::open_add(float current_x, float current_y, float father_x, float father_y, float X, float Y)
{
  this->open_list.push_back(new Player::Coordinates(current_x, current_y, father_x, father_y, X, Y));
}

bool		Player::addable(float x, float y)
{
  if (y - min_y - 1 < max_y - min_y - 1 && y - min_y - 1 >= 0 && x - min_x - 1 < max_x - min_x - 1 && x - min_x - 1 >= 0)
    return (this->IA_map[static_cast<int>(y - min_y - 1)][static_cast<int>(x - min_x - 1)] == 0 || this->IA_map[static_cast<int>(y - min_y - 1)][static_cast<int>(x - min_x - 1)] == 3 || this->IA_map[static_cast<int>(y - min_y - 1)][static_cast<int>(x - min_x - 1)] == 5);
  return (false);
}

void		Player::open_to_close(float x, float y, float a, float b)
{
  std::list<Player::Coordinates *>::iterator	debut = this->open_list.begin();
  std::list<Player::Coordinates *>::iterator	fin = this->open_list.end();
  int						tmpx, tmpy;
  Player::Coordinates				*tmp;

  while (debut != fin)
    {
      if (static_cast<int>((*debut)->x) == static_cast<int>(x) && static_cast<int>((*debut)->y) == static_cast<int>(y))
	{
	  tmp = *debut;
	  tmpx = (*debut)->parentX;
	  tmpy = (*debut)->parentY;
	  break;
	}
      ++debut;
    }
  this->open_list.erase(debut);
  this->close_list.push_back(new Player::Coordinates(x, y, tmpx, tmpy, a, b));
  delete tmp;
}

int		Player::recalc_path()
{
  while (this->open_list.size() != 0)
    {
      delete *(this->open_list.begin());
      this->open_list.erase(this->open_list.begin());
    }
  while (this->close_list.size() != 0)
    {
      delete *(this->close_list.begin());
      this->close_list.erase(this->close_list.begin());
    }
  this->open_add(this->getPosition().x, this->getPosition().z, this->getPosition().x, this->getPosition().z, this->goToX, this->goToY);
  if (this->addable(this->getPosition().x - 1, this->getPosition().z))
    this->open_add(this->getPosition().x - 1, this->getPosition().z, this->getPosition().x, this->getPosition().z, this->goToX, this->goToY);
  if (this->addable(this->getPosition().x + 1, this->getPosition().z))
    this->open_add(this->getPosition().x + 1, this->getPosition().z, this->getPosition().x, this->getPosition().z, this->goToX, this->goToY);
  if (this->addable(this->getPosition().x, this->getPosition().z - 1))
    this->open_add(this->getPosition().x, this->getPosition().z - 1, this->getPosition().x, this->getPosition().z, this->goToX, this->goToY);
  if (this->addable(this->getPosition().x, this->getPosition().z + 1))
    this->open_add(this->getPosition().x, this->getPosition().z + 1, this->getPosition().x, this->getPosition().z, this->goToX, this->goToY);
  this->open_to_close(this->getPosition().x, this->getPosition().z, this->goToX, this->goToY);
  if (this->last_heuristic())
    return (1);
  return (this->Astar_aggressif());
}

bool		Player::last_heuristic()
{
  std::list<Player::Coordinates *>::iterator fin = this->close_list.end();

  --fin;
  return ((*fin)->heuristic == 0);
}

int		Player::calc_target(std::vector<Player *> *listPlayer)
{
  std::vector<Player *>::iterator debut = listPlayer->begin();

  this->hasChanged = false;
  if (this->goToX == 2147483647 || this->IA_map[static_cast<int>(goToY - min_y - 1)][static_cast<int>(goToX - min_x - 1)] != 5)
    {
      this->goToX = (*debut)->getPosition().x;
      this->goToY = (*debut)->getPosition().z;
      this->hasChanged = true;
    }
  if (this->hasChanged)
    return (this->recalc_path());
  return (1);
}

void		Player::close_del_first()
{
  std::list<Player::Coordinates *>::iterator	debut = this->close_list.begin();
  Player::Coordinates				*tmp;

  tmp = *debut;
  this->close_list.erase(debut);
  delete tmp;
}

int		Player::IA(std::vector<ABox*> const &listObj,  std::vector<Bomb*> *listBomb, std::vector<Player*> *listPlayer)
{
  if (this->IA_map == NULL)
    this->create_map(listObj);
  this->update_map(listObj, listBomb, listPlayer);
  this->calc_target(listPlayer);
  if (this->close_list.size() == 0)
    return (5);
  if (abs(this->getPosition().x - (*(this->close_list.begin()))->x) + abs(this->getPosition().z - (*(this->close_list.begin()))->y) < 0.2)
    this->close_del_first();
  if (this->close_list.size() == 0)
    return (5);
  if (this->calc_target(listPlayer) == 0)
    return (0);
  return (this->toTarget((*(this->close_list.begin()))->x, (*(this->close_list.begin()))->y, this->getPosition().x, this->getPosition().z));
}

void		Player::draw(gdl::AShader &shader, glm::mat4 const &transform,
			     double deltaTime)
{
  if (_name == "Player1")
    shader.setUniform("myColor", glm::vec4(153, 0, 0, 255));
  else if (_name == "Player2")
    shader.setUniform("myColor", glm::vec4(0, 153, 0, 255));
  else
    shader.setUniform("myColor", glm::vec4(0, 0, 0, 255));
  this->_model->draw(shader, transform, deltaTime);
}

void		Player::drawHUD(gdl::AShader &shader, gdl::Clock const &clock)
{
  this->_hud->draw(shader, clock);
}

glm::mat4	Player::getTransformation() const
{
  glm::mat4   transform(1);

  transform = glm::translate(transform, glm::vec3(_position.x, _position.y - 0.5, _position.z));
  transform = glm::rotate(transform, this->_rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, this->_rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, this->_rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, this->_scale);
  return (transform);
}

void		Player::lessBomb()
{
  this->_currentbomb -= 1;
}

void		Player::upLife()
{
  if (_life < 10)
    this->_life += 1;
}

int		Player::getLife() const
{
  return _life;
}

void		Player::lessLife()
{
  this->_life -= 1;
}

void		Player::upMs()
{
  if (this->_speed < 6.0f)
    this->_speed += 1.0f;
}

void		Player::upPower()
{
  if (_power < 10)
    this->_power += 1;
}

void		Player::upNumber()
{
  if (_maxbomb < 10)
    this->_maxbomb += 1;
}
