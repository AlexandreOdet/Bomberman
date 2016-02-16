//
// HUD.cpp for HUD in /home/bourre_l/rendu/cpp_bomberman/Player
//
// Made by bourrel léo
// Login   <bourre_l@epitech.net>
//
// Started on  Fri Jun 05 17:52:11 2015 bourrel léo
// Last update Fri Jun 12 16:29:25 2015 bourrel léo
//

#include "HUD.hh"

HUD::HUD(glm::vec3 const &pos, std::string const &name) : _pos(pos)
{
  int		i = 0;
  double	j = 0.06;

  _pow = 2;
  _bomb = 2;
  _speed = 2;
  _life = 1;
  _s = 0;

  this->_obj = this->addPlan(0.6, glm::vec3(_pos.x + 0.045, _pos.y, _pos.z + 0.04), "HUD");
  this->_player = this->addPlan(0.05, glm::vec3(_pos.x - 0.23, _pos.y, _pos.z - 0.06), name);
  this->_num.push_back(this->addPlan(0.05, glm::vec3(_pos.x - 0.15, _pos.y, _pos.z - 0.08), "2"));
  this->_num.push_back(this->addPlan(0.05, glm::vec3(_pos.x - 0.03, _pos.y, _pos.z - 0.08), "2"));
  this->_num.push_back(this->addPlan(0.05, glm::vec3(_pos.x + 0.08, _pos.y, _pos.z - 0.08), "2"));
  this->_num.push_back(this->addPlan(0.05, glm::vec3(_pos.x + 0.2, _pos.y, _pos.z - 0.08), "1"));

  while (i < 4)
    {
      this->_score.push_back(this->addPlan(0.05, glm::vec3(_pos.x + 0.295, _pos.y, _pos.z + j), "0"));
      j -= 0.03;
      i++;
    }
}

HUD::~HUD()
{
}

Plan	*HUD::addPlan(float const &size, glm::vec3 const &v, std::string const &name) const
{
  Plan	*tmp = new Plan(size, v, name);

  tmp->rotate(glm::vec3(0, 1, 0), 90);
  tmp->rotate(glm::vec3(0, 0, 1), -90);
  return tmp;
}

void	HUD::update(int const bomb, int const life, int const pow, float const speed, int const score)
{
  if (pow != _pow)
    {
      _num[0]->changeTexture(std::to_string(pow));
      _pow = pow;
    }
  if (bomb != _bomb)
    {
      _num[1]->changeTexture(std::to_string(bomb));
      _bomb = bomb;
    }
  if (speed != _speed)
    {
      _num[2]->changeTexture(std::to_string(static_cast<int>(speed)));
      _speed = speed;
    }
  if (life != _life)
    {
      _num[3]->changeTexture(std::to_string(life));
      _life = life;
    }
  if (score != _s)
    {
      std::string	str_score = std::to_string(score);
      str_score = std::string(str_score.rbegin(), str_score.rend());
      std::string	tmp;
      int		i = 0;

      while (i != static_cast<int>(str_score.size()))
	{
	  tmp = str_score[i];
	  _score[i]->changeTexture(std::string(tmp));
	  tmp.clear();
	  i++;
	}
      _s = score;
    }
}

void	HUD::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  int	i = 0;

  _obj->draw(shader, clock);
  _player->draw(shader, clock);
  while (i < 4)
    {
      _num[i]->draw(shader, clock);
      i++;
    }
  i = 0;
  while (i < 4)
    {
      _score[i]->draw(shader, clock);
      i++;
    }
}
