#ifndef __MYGAME_HH__
#define __MYGAME_HH__

#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>
#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <vector>
#include <fmod.h>

#include <thread>
#include <chrono>

#include "Pause.hh"
#include "Camera.hh"
#include "AObject.hpp"
#include "Pars.hh"
#include "Player.hh"
#include "Bomb.hh"
#include "Ressource.hh"
#include "Exception.hpp"
#include "Load.hh"
#include "Sound.hh"
#include <fmod.h>

class MyGame : public gdl::Game
{
public:
  MyGame(std::list<int> const &, std::list<std::string> const &);
  ~MyGame();

public:
  bool			initialize();
  bool			update();
  void			draw();
  void			Save() const;
  void			setPlaying();
  std::string		getDate() const;

private:
  void			addPlayers();
  bool			dispGame();
  bool			dispPause();

private:

  int			_nbplayer;
  int			_nbia;
  std::string		_map;
  std::string		_theme;
  Pause			*_pause;
  bool			_playing;
  bool			_load;
  Loader		*_loader;

  std::map<std::string, gdl::Texture>	_textures;

  gdl::SdlContext	_context;
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;
  std::vector<ABox*>	_objects;
  std::vector<Bomb*>	_bomb;
  std::vector<Player*>	_players;

  Pars			_pars;
  Camera		*_camera;
  FMOD_SOUND		*son;
};

#endif
