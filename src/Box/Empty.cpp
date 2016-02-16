#include "Empty.hh"

Empty::Empty(glm::vec3 const &pos, bool isBonus)
{
  this->_pos = pos;
  this->_type = "empty";
  this->_solid = false;
  this->_breakable = false;
  if (isBonus == true)
    {
      std::map<int, void(Empty::*)()>	_BonusMap;
      void	(Empty::*ptr)();

      _BonusMap[0] = &Empty::BombBonus;
      _BonusMap[1] = &Empty::SpeedBonus;
      _BonusMap[2] = &Empty::RangeBonus;
      _BonusMap[3] = &Empty::LifeBonus;

      if ((ptr = _BonusMap[rand() % 20]))
	(this->*ptr)();
      else
	_Btype = EMPTY;
    }
  else
    _Btype = EMPTY;
  this->_obj = new Plan(1, this->_pos, "GROUND");
}

Empty::Empty(glm::vec3 const &pos, std::string const &b)
{
  this->_pos = pos;
  this->_type = "empty";
  this->_solid = false;
  this->_breakable = false;

  std::map<std::string, void(Empty::*)()>	_BonusMap;
  void	(Empty::*ptr)();

  _BonusMap["bomb"] = &Empty::BombBonus;
  _BonusMap["speed"] = &Empty::SpeedBonus;
  _BonusMap["power"] = &Empty::RangeBonus;
  _BonusMap["life"] = &Empty::LifeBonus;

  if ((ptr = _BonusMap[b]))
    (this->*ptr)();
  else
    _Btype = EMPTY;
  this->_obj = new Plan(1, this->_pos, "GROUND");
}

Empty::~Empty()
{ }

void		Empty::draw(gdl::AShader &shader,gdl::Clock const &clock)
{
  this->_obj->draw(shader, clock);
  if (_Btype != EMPTY)
    _bonus->draw(shader, clock);
}

void		Empty::update(gdl::Clock const &clock, gdl::Input &input)
{
  this->_obj->update(clock, input);
  if (_Btype != EMPTY)
    _bonus->update(clock, input);
}

std::string	Empty::getBonus() const
{
  if (_Btype == EMPTY)
    return "drowmar";
  return _bonus->getType();
}

void		Empty::BombBonus()
{
  _Btype = BOMB;
  this->_bonus = new Addbomb(glm::vec3(this->_pos.x, 1, this->_pos.z));
}

void		Empty::RangeBonus()
{
  _Btype = RANGE;
  this->_bonus = new Addrange(glm::vec3(this->_pos.x, 1, this->_pos.z));
}

void		Empty::SpeedBonus()
{
  _Btype = SPEED;
  this->_bonus = new Addspeed(glm::vec3(this->_pos.x, 1, this->_pos.z));
}

void		Empty::LifeBonus()
{
  _Btype = LIFE;
  this->_bonus = new Addlife(glm::vec3(this->_pos.x, 1, this->_pos.z));
}

void		Empty::DeleteBonus()
{
  _Btype = EMPTY;
  delete _bonus;
}
