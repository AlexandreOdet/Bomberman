//
// Menu.hh for Menu_Bomberman in /home/odet_a/Menu
//
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
//
// Started on  Mon May 11 17:06:58 2015 Alexandre Odet
// Last update Sat Jun 13 11:22:19 2015 bourrel léo
//

#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL.h>

#include <iostream>
#include <list>
#include <dirent.h>
#include <fstream>
#include <map>

#include "MSetting.hh"
#include "Exception.hpp"
#include "MParsing.hh"
#include "MapGenerator.hh"

/*
**
The window size
**
*/

# define WIN_X (800)
# define WIN_Y (600)
# define MIN_W (10)
# define MIN_H (10)

/*
**
Class menu contening all the attributes I need.
There's a lot of SDL_Surface *, to print all the text
TTF for the police
Some int to save values like the number of player, or AI, the current position of the "cursor".
There are private methods, because user don't have to call them. Like "setMap" which fill a list with all the map...
Etc...
**
*/

class	Menu
{
public:
  Menu();
  ~Menu();
  std::list<std::string>	getMapSave() const;
  std::list<int>		getBotsPlayer() const;

private:
  SDL_Window			*_screen;
  SDL_Renderer			*_renderer;

  SDL_Texture			*_logo;
  SDL_Texture			*_Background;
  SDL_Texture			*_play;
  SDL_Texture			*_map;
  SDL_Texture			*_players;
  SDL_Texture			*_save;
  SDL_Texture			*_nbBots;
  SDL_Texture			*_quit;
  SDL_Texture			*_Xrand;
  SDL_Texture			*_Yrand;
  SDL_Texture			*_choosing;
  SDL_Texture			*_gen;
  SDL_Texture			*_them;

  SDL_Rect			_posLogo;
  SDL_Rect			_posBg;
  SDL_Rect			_posTxt;
  SDL_Event			_event;
  TTF_Font			*_police;
  TTF_Font			*_font;
  SDL_Color			_black;
  SDL_Color			_red;

  int				_save_p;
  int				_save_b;
  int				_current_pos;
  int				_map_pos;
  int				_save_pos;
  int				_printable;
  int				_randX;
  int				_randY;
  int				_loop;
  int				_isPressed;
  int				_isInGen;
  int				_posGen;

  std::list<std::string>	_saveList;
  SDL_Texture			*_listSurfaceSave;

  DIR				*_dir;
  struct dirent			*_ent;

  std::list<std::string>	_mapList;
  SDL_Texture			*_surfaceMap;

  std::list<std::string>	_mapAndSave;
  std::list<int>		_botsAndPlayers;
  int				_boolMap;
  int				_boolSave;

  std::list<MSetting *>		_surfaceList;
  std::list<MSetting *>		_surfaceListSave;

  std::string			_mapGaming;
  std::string			_saveGaming;
  std::string			_themeGaming;

  std::list<std::string>::iterator _it;
  std::list<std::string>	_listTheme;

  SDL_Texture	*getTextureFromFile(const std::string &);
  SDL_Texture	*surfaceToTexture(SDL_Surface *);

  void		waitEvent();

  void		draw();

  void		setList();
  void		setMap();
  void		setTheme();
  void		setPlayer();
  void		setBots();
  void		setSurFaceListMap(std::list<std::string> &);
  void		fillSaveSurface(std::list<std::string>  &);
  void		setsurfaceSaveListColor(const int);
  void		setColorMap(const int);

  void		eventRight();
  void		eventLeft();
  void		checkReturn();
  void		printMapMenu();
  void		printSaveMenu();
  void		displayMap();
  void		displaySave();
  void		setRandomMap();
  void		changeTheme();

  void		getSaveInfo(const std::string &);
  void		launchGame();

  void		downCursor();
  void		upCursor();
  void		printHomeMenu();
  void		displayNumber();
  void		setRandMore();
  void		setRandLess();
  void		printNextMap(const int, const int);
  void		displayNext();
};

#endif /* MENU_H */
