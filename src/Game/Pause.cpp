//
// Pause.cpp for Pause in /home/bourre_l/rendu/cpp_bomberman/Game
//
// Made by bourrel léo
// Login   <bourre_l@epitech.net>
//
// Started on  Mon Jun 01 08:46:09 2015 bourrel léo
// Last update Fri Jun 12 18:26:25 2015 bourrel léo
//

#include "Pause.hh"
#include "MyGame.hh"

Pause::Pause(MyGame *g)
{
  _curPos = 0;
  _game = g;
  _obj.push_back(new Plan(0.5, glm::vec3(-0.35, 0, 0), "SAVE2"));
  _obj[0]->rotate(glm::vec3(0, 1, 0), 90);
  _obj[0]->rotate(glm::vec3(0, 0, 1), -90);

  _obj.push_back(new Plan(0.5, glm::vec3(0, 0, 0), "BACK"));
  _obj[1]->rotate(glm::vec3(0, 1, 0), 90);
  _obj[1]->rotate(glm::vec3(0, 0, 1), -90);

  _obj.push_back(new Plan(0.5, glm::vec3(0.35, 0, 0), "QUIT"));
  _obj[2]->rotate(glm::vec3(0, 1, 0), 90);
  _obj[2]->rotate(glm::vec3(0, 0, 1), -90);

  _fctList[0] = &Pause::save;
  _fctList[1] = &Pause::back;
  _fctList[2] = &Pause::quit;
}

Pause::~Pause()
{
}

void	Pause::back() const
{
  this->_game->setPlaying();
}

void	Pause::quit() const
{
  exit(0);
}

void	Pause::save() const
{
  this->_game->Save();
}

void    Pause::update(gdl::Clock const &clock, gdl::Input &input)
{
  if (input.getKey(SDLK_DOWN))
    _curPos += 1;
  else if (input.getKey(SDLK_UP))
    _curPos -= 1;
  else if (input.getKey(SDLK_RETURN))
    {
      void	((Pause::*_ptr)() const);

      if ((_ptr = _fctList[_curPos]))
	(this->*_ptr)();
    }

  _curPos = (_curPos < 0) ? 2 : (_curPos > 2) ? 0 : _curPos;
  (_curPos == 0) ? _obj[0]->changeTexture("SAVE2") : _obj[0]->changeTexture("SAVE");
  (_curPos == 1) ? _obj[1]->changeTexture("BACK2") : _obj[1]->changeTexture("BACK");
  (_curPos == 2) ? _obj[2]->changeTexture("QUIT2") : _obj[2]->changeTexture("QUIT");
  for (std::vector<Plan*>::iterator it = _obj.begin(); it != _obj.end(); ++it)
    (*it)->update(clock, input);
}

void    Pause::draw(gdl::AShader &shader,gdl::Clock const &clock)
{
  for (std::vector<Plan*>::iterator it = _obj.begin(); it != _obj.end(); ++it)
    (*it)->draw(shader, clock);
}
