#include <iostream>
#include <time.h>
#include <unistd.h>

#include "Bomb.hh"

Bomb::Bomb(glm::vec3 const &pos ,int const power, Player  *p)
{
  this->_rotation = glm::vec3(0, 0, 0);
  this->_scale = glm::vec3(0.003, 0.003, 0.003);
  this->_time = 0;
  this->_explode = 0;
  this->_pos = pos;
  this->_owner = p;
  this->_range = power;
  this->_model = new gdl::Model;
  if (!this->_model->load("./ressource/bomb/bob-omb.fbx"))
    throw ResError("./ressource/bomb/bob-omb.fbx");
  this->son = GSound["bomb"];
}

Bomb::~Bomb()
{
  this->_owner->lessBomb();
}

void		Bomb::draw(gdl::AShader &shader, gdl::Clock const &clock,
			   glm::mat4 const &transform, double deltaTime)
{
  if (_explode == 0)
    {
      if (_owner->getName() == "Player1")
	shader.setUniform("myColor", glm::vec4(100, 0, 0, 255));
      else if (_owner->getName() == "Player2")
	shader.setUniform("myColor", glm::vec4(0, 100, 0, 255));
      else
	shader.setUniform("myColor", glm::vec4(0, 0, 0, 255));
      this->_model->draw(shader, transform, deltaTime);
    }
  else
    {
      for (size_t i = 0; i < _fs.size(); ++i)
	_fs[i]->draw(shader, clock);
    }
}

glm::mat4	Bomb::getTransformation() const
{
  glm::mat4   transform(1);

  transform = glm::translate(transform, glm::vec3(_pos.x, _pos.y - 0.5, _pos.z));
  transform = glm::rotate(transform, this->_rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, this->_rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, this->_rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, this->_scale);
  return (transform);
}

glm::vec3	Bomb::getPos() const
{
  return this->_pos;
}

int		Bomb::getRange() const
{
  return this->_range;
}

void		Bomb::activeExplode()
{
  this->_time = 1005;
}

int		Bomb::getExplode() const
{
  return _explode;
}

int		Bomb::buildFire(std::vector<ABox*> *obj, float const direction,
				char const d, std::vector<Bomb *> const *bomb,
				std::vector<Player *> *p)
{
  glm::vec3	tmp = _pos;
  glm::vec3	block;
  glm::vec3	replace;

  for (int i = 0; i < this->_range; ++i)
    {
      if (d == 'x')
	tmp.x += direction;
      if (d == 'z')
	tmp.z += direction;
      for (std::vector<Bomb *>::const_iterator y = bomb->begin(); y != bomb->end(); ++y)
	{
	  block = (*y)->getPos();
	  if ((tmp.x >= block.x - 0.3 && tmp.x <= block.x + 0.3)
	      && (tmp.z > (block.z - 0.5) && tmp.z < (block.z + 0.5))
	      && (*y)->getExplode() == 0)
	    (*y)->activeExplode();
	}
      for (std::vector<Player *>::iterator y = p->begin(); y != p->end();)
       	{
       	  block = (*y)->getIntPosition();
       	  if ((tmp.x >= block.x - 0.3 && tmp.x <= block.x + 0.3)
       	      && (tmp.z > (block.z - 0.5) && tmp.z < (block.z + 0.5)))
       	    {
	      (*y)->lessLife();
	      if ((*y)->getLife() == 0)
		{
		  p->erase(y);
		  _owner->addScore(10);
		}
	      else
		{
		  ++y;
		  _owner->addScore(5);
		}
	    }
	  else
	    ++y;
	}
      for (std::vector<ABox *>::iterator y = obj->begin(); y != obj->end(); ++y)
	{
	  if ((*y)->getSolid() == true)
	    {
	      block = (*y)->getPos();
	      if ((tmp.x >= block.x - 0.3 && tmp.x <= block.x + 0.3)
		  && (tmp.z > (block.z - 0.5) && tmp.z < (block.z + 0.5)))
		{
		  if ((*y)->getBreakable() == true)
		    {
		      replace = (*y)->getPos();
		      replace.y = -0.5;
		      delete (*y);
		      obj->erase(y);
		      obj->insert(y, new Empty(replace, true));
		    }
		  return 1;
		}
	    }
	}
      _fs.push_back(new Cube(1, tmp, "FIRE"));
    }
  return 0;
}

int		Bomb::update(std::vector<ABox*> *obj, std::vector<Bomb *> const *bomb,
			     std::vector<Player*> *p, gdl::Clock const &c)
{
  if (this->_time < 2)
    this->_time += c.getElapsed();
  if (this->_time >= 0.4 && _explode == 1)
    return 1;
  else if ((_time >= 2 && _explode == 0))
    {
      Sound::play(son);
      this->_explode = 1;
      this->_time = 0;
      glm::vec3	block;
      for (std::vector<Player *>:: iterator y = p->begin(); y != p->end();)
       	{
       	  block = (*y)->getIntPosition();
       	  if ((this->_pos.x >= block.x - 0.3 && this->_pos.x <= block.x + 0.3)
       	      && (this->_pos.z > (block.z - 0.5) && this->_pos.z < (block.z + 0.5)))
       	    {
	      (*y)->lessLife();
	      if ((*y)->getLife() == 0)
		{
		  p->erase(y);
		  _owner->addScore(10);
		}
	      else
		{
		  ++y;
		  _owner->addScore(5);
		}
       	    }
	  else
       	    ++y;
       	}
      buildFire(obj, 1, 'x', bomb, p);
      buildFire(obj, -1, 'x', bomb, p);
      buildFire(obj, 1, 'z', bomb, p);
      buildFire(obj, -1, 'z', bomb, p);
      return 2;
    }
  else
    return 0;
}
