//
// Ressource.cpp for Ressource in /home/bourre_l/rendu/cpp_bomberman/Game
//
// Made by bourrel léo
// Login   <bourre_l@epitech.net>
//
// Started on  Fri May 29 16:18:02 2015 bourrel léo
// Last update Fri Jun 12 17:53:17 2015 bourrel léo
//

#include "Ressource.hh"

std::map<std::string, gdl::Texture*>	Gtexture;

Ressource::Ressource(std::string const &theme)
{
  _ground = new gdl::Texture();
  _fire = new gdl::Texture();
  _box = new gdl::Texture();
  _wall = new gdl::Texture();
  _bomb = new gdl::Texture();

  _Bspeed = new gdl::Texture();
  _Bbomb = new gdl::Texture();
  _Blife = new gdl::Texture();
  _Brange = new gdl::Texture();

  _back = new gdl::Texture();
  _quit = new gdl::Texture();
  _save = new gdl::Texture();
  _back2 = new gdl::Texture();
  _quit2 = new gdl::Texture();
  _save2 = new gdl::Texture();

  _hud = new gdl::Texture();
  _win = new gdl::Texture();
  _loose = new gdl::Texture();

  std::map<std::string, void(Ressource::*)()>	ResMap;
  void		(Ressource::*ptr)();

  ResMap["defaut"] = &Ressource::setDefault;
  ResMap["minecraft"] = &Ressource::setMinecraft;
  ResMap["marin"] = &Ressource::setMarine;
  ResMap["volcano"] = &Ressource::setVolcano;

  if ((ptr = ResMap[theme]))
    (this->*ptr)();
  else
    setDefault();

  setBonus();
  setPause();
  setOther();
  setNumero();

  Gtexture["GROUND"] = _ground;
  Gtexture["FIRE"] = _fire;
  Gtexture["BOX"] = _box;
  Gtexture["WALL"] = _wall;
  Gtexture["BOMB"] = _bomb;

  Gtexture["BSPEED"] = _Bspeed;
  Gtexture["BBOMB"] = _Bbomb;
  Gtexture["BLIFE"] = _Blife;
  Gtexture["BRANGE"] = _Brange;

  Gtexture["QUIT"] = _quit;
  Gtexture["SAVE"] = _save;
  Gtexture["BACK"] = _back;
  Gtexture["QUIT2"] = _quit2;
  Gtexture["SAVE2"] = _save2;
  Gtexture["BACK2"] = _back2;

  Gtexture["HUD"] = _hud;
  Gtexture["win"] = _win;
  Gtexture["loose"] = _loose;
}

Ressource::~Ressource()
{
}

void	Ressource::setBonus()
{
  if (_Bspeed->load("ressource/bonus/speed.tga", true) == false)
    throw ResError("ressource/bonus/speed.tga");
  if (_Bbomb->load("ressource/bonus/bomb.tga", true) == false)
    throw ResError("ressource/bonus/bomb.tga");
  if (_Blife->load("ressource/bonus/life.tga", true) == false)
    throw ResError("ressource/bonus/life.tga");
  if (_Brange->load("ressource/bonus/range.tga", true) == false)
    throw ResError("ressource/bonus/range.tga");
}


void	Ressource::setPause()
{
  if (_quit->load("ressource/pause/Quit.tga", true) == false)
    throw ResError("ressource/pause/Quit.tga");
  if (_back->load("ressource/pause/Back.tga", true) == false)
    throw ResError("ressource/pause/Back.tga");
  if (_save->load("ressource/pause/Save.tga", true) == false)
    throw ResError("ressource/pause/Save.tga");

  if (_quit2->load("ressource/pause/Quit2.tga", true) == false)
    throw ResError("ressource/pause/Quit2.tga");
  if (_back2->load("ressource/pause/Back2.tga", true) == false)
    throw ResError("ressource/pause/Back2.tga");
  if (_save2->load("ressource/pause/Save2.tga", true) == false)
    throw ResError("ressource/pause/Save2.tga");
}

void	Ressource::setOther()
{
  if (_hud->load("ressource/hud.tga", true) == false)
    throw ResError("ressource/hud.tga");
  if (_fire->load("ressource/theme/fire.tga", true) == false)
    throw ResError("ressource/theme/fire.tga");

  if (_win->load("ressource/win.tga", true) == false)
    throw ResError("ressource/win.tga");
  if (_loose->load("ressource/loose.tga", true) == false)
    throw ResError("ressource/loose.tga");
}

void	Ressource::setNumero()
{
  int	i = 0;
  std::stringstream	ss;

  while (i < 10)
    {
      _num.push_back(new gdl::Texture);
      ss << "ressource/number/" << i << ".tga";
      if (_num[i]->load(ss.str(), true) == false)
	throw ResError(ss.str());
      ss.str("");
      ss << i;
      Gtexture[ss.str()] = _num[i];
      ss.str("");
      i++;
    }
}

void	Ressource::setDefault()
{
  if (_ground->load("ressource/theme/defaut/floor.tga", true) == false)
    throw ResError("ressource/theme/defaut/floor.tga");
  if (_box->load("ressource/theme/defaut/wood_box.tga", true) == false)
    throw ResError("ressource/theme/defaut/wood_box.tga");
  if (_wall->load("ressource/theme/defaut/rock_texture.tga", true) == false)
    throw ResError("ressource/theme/defaut/rock_texture.tga");
  if (_bomb->load("ressource/theme/defaut/bomb.tga", true) == false)
    throw ResError("ressource/theme/defaut/bomb.tga");
}

void	Ressource::setMinecraft()
{
  if (_ground->load("ressource/theme/minecraft/grass.tga", true) == false)
    throw ResError("ressource/theme/minecraft/grass.tga");
  if (_box->load("ressource/theme/minecraft/wood.tga", true) == false)
    throw ResError("ressource/theme/minecraft/wood.tga");
  if (_wall->load("ressource/theme/minecraft/cobleston.tga", true) == false)
    throw ResError("ressource/theme/minecraft/cobleston.tga");
  if (_bomb->load("ressource/theme/minecraft/bomb.tga", true) == false)
    throw ResError("ressource/theme/minecraft/bomb.tga");
}

void	Ressource::setVolcano()
{
  if (_ground->load("ressource/theme/Volcano/ground.tga", true) == false)
    throw ResError("ressource/theme/Volcano/ground.tga");
  if (_box->load("ressource/theme/Volcano/box.tga", true) == false)
    throw ResError("ressource/theme/Volcano/box.tga");
  if (_wall->load("ressource/theme/Volcano/rock.tga", true) == false)
    throw ResError("ressource/theme/Volcano/rock.tga");
  if (_bomb->load("ressource/theme/defaut/bomb.tga", true) == false)
    throw ResError("ressource/theme/defaut/bomb.tga");
}

void	Ressource::setMarine()
{
  if (_ground->load("ressource/theme/marine/water.tga", true) == false)
    throw ResError("ressource/theme/marine/water.tga");
  if (_box->load("ressource/theme/marine/box.tga", true) == false)
    throw ResError("ressource/theme/marine/box.tga");
  if (_wall->load("ressource/theme/marine/ice.tga", true) == false)
    throw ResError("ressource/theme/marine/ice.tga");
  if (_bomb->load("ressource/theme/defaut/bomb.tga", true) == false)
    throw ResError("ressource/theme/defaut/bomb.tga");
}
