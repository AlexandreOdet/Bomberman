//
// Menu.cpp for Menu in /home/odet_a/Menu
//
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
//
// Started on  Mon May 11 17:06:40 2015 Alexandre Odet
// Last update Fri Jun 12 15:03:54 2015 bourrel léo
//

#include "Menu.hh"
#include <unistd.h>

/*
The constructor of Menu Class inits all the variable, fills all the list
and call two private functions draw and wait_event.
You'll see below what's their utility and why call them.
*/

Menu::Menu()
{
  this->_current_pos = 1;

  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw MenuError(SDL_GetError());
  if (TTF_Init() == -1)
    throw MenuError(TTF_GetError());
  this->_screen = SDL_CreateWindow("Bomberman",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   WIN_X, WIN_Y,
				   SDL_WINDOW_SHOWN);
  if (this->_screen == NULL)
    throw MenuError(SDL_GetError());
  this->_renderer = SDL_CreateRenderer(this->_screen, -1, SDL_RENDERER_ACCELERATED);
  if (this->_renderer == NULL)
    throw MenuError(SDL_GetError());

  SDL_RenderSetLogicalSize(this->_renderer, WIN_X, WIN_Y);

  this->_posLogo.x = WIN_X / 5;
  this->_posLogo.y = 0;
  this->_posLogo.w = 459;
  this->_posLogo.h = 118;

  this->_posBg.x = 0;
  this->_posBg.y = 0;
  this->_Background = this->getTextureFromFile("./ressource/menu/Wallpaper.bmp");
  this->_logo = this->getTextureFromFile("./ressource/menu/Bomberman_Logo.png");

  if (this->_logo == NULL || this->_Background == NULL)
    throw MenuError(SDL_GetError());

  this->_police = TTF_OpenFont("./ressource/menu/bomberman.ttf", 50);
  if (!this->_police)
    throw MenuError(TTF_GetError());
  this->_font = TTF_OpenFont("./ressource/menu/bomberman.ttf", 35);
  if (!this->_font)
    throw MenuError(TTF_GetError());

  this->_posTxt.x = 20;
  this->_posTxt.y = 10;

  this->_save_p = 1;
  this->_save_b = 1;

  this->_boolMap = 1;

  this->setList();
  this->setMap();

  this->_black = {0, 0, 0, 0};
  this->_red = {255, 0, 0, 0};

  this->_printable = 0;
  this->_map_pos = -1;
  this->_save_pos = -1;
  this->_isInGen = 0;
  this->_posGen = 0;

  this->setSurFaceListMap(this->_mapList);
  this->fillSaveSurface(this->_saveList);

  this->_mapGaming = "Random";
  this->_saveGaming = "None";
  this->_themeGaming = "defaut";

  this->_loop = 0;

  this->_surfaceMap = NULL;
  this->_play = NULL;
  this->_map = NULL;
  this->_players = NULL;
  this->_save = NULL;
  this->_nbBots = NULL;
  this->_quit = NULL;
  this->_Xrand = NULL;
  this->_Yrand = NULL;
  this->_choosing = NULL;
  this->_gen = NULL;

  this->_isPressed = 0;

  this->_randX = MIN_W;
  this->_randY = MIN_H;

  this->setTheme();
  this->_it = this->_listTheme.begin();

  this->draw();
  this->waitEvent();
}

void		Menu::setTheme()
{
  this->_listTheme.push_back("defaut");
  this->_listTheme.push_back("marin");
  this->_listTheme.push_back("volcano");
  this->_listTheme.push_back("minecraft");
}

/*
**
This function will returns a texture from a file
**
*/

SDL_Texture	*Menu::getTextureFromFile(const std::string & file)
{
  SDL_Surface	*surface = IMG_Load(file.c_str());

  if (surface == NULL)
    throw MenuError(SDL_GetError());

  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}

/*
**
This function will returns a texture from a SDL_Surface it received.
**
*/

SDL_Texture	*Menu::surfaceToTexture(SDL_Surface *surface)
{
  if (surface == NULL)
    throw MenuError(SDL_GetError());

  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

/*
**
This function returns a list contening the map you choose (or the default one) and the save (if you choose one).
**
*/

std::list<std::string> Menu::getMapSave() const
{
  return (this->_mapAndSave);
}

/*
**
This functions returns a list contening the number of player(s)/AI(s) you choose or the default values.
**
*/

std::list<int> Menu::getBotsPlayer() const
{
  return (this->_botsAndPlayers);
}

/*
**
This function fills a list which contains all the save.
**
*/

void	Menu::setList()
{
  if ((this->_dir = opendir("./save")) == NULL)
    throw MenuError("Cannot access the save directory");
  while ((this->_ent = readdir(this->_dir)) != NULL)
    {
      if (this->_ent->d_name[0] != '.')
	this->_saveList.push_back(this->_ent->d_name);
    }
  closedir (this->_dir);
}

/*
**
This function fills a list which contains all the map.
**
*/

void	Menu::setMap()
{
  if ((this->_dir = opendir("./map")) == NULL)
    throw MenuError("Cannot access the save directory");
  while ((this->_ent = readdir(this->_dir)) != NULL)
    {
      if (this->_ent->d_name[0] != '.')
	this->_mapList.push_back(this->_ent->d_name);
    }
  this->_mapList.push_front("Generate");
  this->_mapList.push_front("Random");
  closedir (this->_dir);
}

/*
**
This function prints the home screen of the menu.
It inits all the TTF it needs and fill them with the good values and print it !
**
*/

void	Menu::printHomeMenu()
{
  std::string tmp1("Players x "), tmp2("Bots x ");
  this->_play = surfaceToTexture(TTF_RenderText_Blended(this->_police,
							"Play",
							(this->_current_pos != 1) ? this->_black :
							this->_red));
  std::string tmp3 = std::to_string(this->_save_p);
  std::string tmp4 = std::to_string(this->_save_b);
  std::string HomeMap("Map : " + this->_mapGaming);
  std::string HomePLayer(tmp1 + tmp3);
  std::string HomeBots(tmp2 + tmp4);
  std::string HomeTheme("Theme : " + this->_themeGaming);

  this->_map = surfaceToTexture(TTF_RenderText_Blended(this->_police,
						       HomeMap.c_str(),
						       (this->_current_pos != 2) ? this->_black :
						       this->_red));

  this->_players = surfaceToTexture(TTF_RenderText_Blended(this->_police,
							   HomePLayer.c_str(),
							   (this->_current_pos != 3) ?
							   this->_black : this->_red));

  this->_nbBots = surfaceToTexture(TTF_RenderText_Blended(this->_police,
							  HomeBots.c_str(),
							  (this->_current_pos != 4) ?
							  this->_black : this->_red));

  this->_save = surfaceToTexture(TTF_RenderText_Blended(this->_police,
							"Load",
							(this->_current_pos != 5) ?
							this->_black : this->_red));


  this->_them = surfaceToTexture(TTF_RenderText_Blended(this->_police,
							HomeTheme.c_str(),
							(this->_current_pos != 6) ?
							this->_black : this->_red));

  this->_quit = surfaceToTexture(TTF_RenderText_Blended(this->_police,
							"Quit",
							(this->_current_pos != 7) ?
							this->_black : this->_red));
  SDL_RenderCopy(this->_renderer, this->_Background, NULL, NULL);
  SDL_RenderCopy(this->_renderer, this->_logo, NULL, &(this->_posLogo));
  this->_posTxt.w = (WIN_X / 5);
  this->_posTxt.h = (WIN_Y / 16);
  SDL_RenderCopy(this->_renderer, this->_play, NULL, &(this->_posTxt));
  this->_posTxt.y += 75;
  this->_posTxt.w += 150;
  SDL_RenderCopy(this->_renderer, this->_map, NULL, &(this->_posTxt));
  this->_posTxt.x += 150;
  if (this->_surfaceMap != NULL)
    SDL_RenderCopy(this->_renderer, this->_surfaceMap, NULL, &(this->_posTxt));
  this->_posTxt.x -= 150;
  this->_posTxt.y += 75;
  SDL_RenderCopy(this->_renderer, this->_players, NULL, &(this->_posTxt));
  this->_posTxt.y += 75;
  SDL_RenderCopy(this->_renderer, this->_nbBots, NULL, &(this->_posTxt));
  this->_posTxt.y += 75;
  this->_posTxt.w -= 150;
  SDL_RenderCopy(this->_renderer, this->_save, NULL, &(this->_posTxt));
  this->_posTxt.y += 75;
  this->_posTxt.w = 30 * HomeTheme.length();
  SDL_RenderCopy(this->_renderer, this->_them, NULL, &(this->_posTxt));
  this->_posTxt.y += 75;
  this->_posTxt.w = 30 * 4;
  SDL_RenderCopy(this->_renderer, this->_quit, NULL, &(this->_posTxt));
  this->_posTxt.x += 175;
  SDL_RenderPresent(this->_renderer);
  this->_posTxt.y = 160;
  this->_posTxt.x -= 175;
}

/*
**
This functions fills a list of "SDL_Texture *" with all the map.
The list just filled will be used later to print another part of the menu !
**
*/

void	Menu::setSurFaceListMap(std::list<std::string> & _mapList)
{
  std::list<std::string>::iterator	mapIt;

  mapIt = _mapList.begin();
  this->_surfaceList.push_front(new MSetting(std::string("Select your map"),
					     this->surfaceToTexture(TTF_RenderText_Blended(this->_police,
											   "Select your map",
											   this->_black))));
  while (mapIt != _mapList.end())
    {
      this->_surfaceList.push_back(new MSetting(std::string(mapIt->c_str()),
						this->surfaceToTexture(TTF_RenderText_Blended(this->_font,
											      mapIt->c_str(),
											      this->_black))));
      ++mapIt;
    }
  this->_surfaceList.push_back(new MSetting(std::string("Return"),
					    this->surfaceToTexture(TTF_RenderText_Blended(this->_police,
											  "Return",
											  this->_black))));
}

/*
**
This function will use the list just filled above and print all the values on the screen.
**
*/

void	Menu::printMapMenu()
{
  std::list<MSetting *>::iterator it;
  SDL_Rect		pos;
  int			haveToPrint = 0;

  SDL_RenderClear(this->_renderer);

  this->setColorMap(this->_map_pos);
  it = this->_surfaceList.begin();

  SDL_RenderCopy(this->_renderer, this->_Background, NULL, NULL);
  SDL_RenderCopy(this->_renderer, this->_logo, NULL, &(this->_posLogo));

  pos.x = 150;
  pos.y = 120;
  pos.w = 250;
  pos.h = 50;

  SDL_RenderCopy(this->_renderer, (*it)->getSurface(), NULL, &pos);

  pos.x = 30;
  pos.y += 75;
  ++it;
  if (this->_map_pos <= 5)
    {
      while (it != this->_surfaceList.end() && !haveToPrint)
	{
	  pos.w = 30 * (*it)->getMap().length();
	  if (pos.y + 75 < WIN_Y)
	    {
	      SDL_RenderCopy(this->_renderer, (*it)->getSurface(), NULL, &pos);
	      pos.y += 75;
	    }
	  else
	    haveToPrint = 1;
	  ++it;
	}
      SDL_RenderPresent(this->_renderer);
    }
  else if (this->_map_pos > 5)
    this->printNextMap(this->_map_pos, this->_map_pos + 5);
}

void	Menu::printNextMap(const int begin, const int end)
{
  std::list<MSetting *>::iterator it;
  SDL_Rect		pos;
  int			tmp = 0, i = 1, _end, _begin;

  _end = end;
  if (end > static_cast<int>(this->_surfaceList.size()))
    _end = static_cast<int>(this->_surfaceList.size());

  this->setColorMap(this->_map_pos);

  it = this->_surfaceList.begin();

  pos.y = 120;
  pos.x = 30;
  pos.h = 50;
  if (begin > 5 && begin < (begin + 5) && begin % 5 != 0)
    _begin = 5;
  else
    _begin = begin;
  while (tmp < _begin)
    {
      tmp++;
      ++it;
    }
  SDL_RenderClear(this->_renderer);

  SDL_RenderCopy(this->_renderer, this->_Background, NULL, NULL);
  SDL_RenderCopy(this->_renderer, this->_logo, NULL, &(this->_posLogo));

  pos.w = 30 *(*it)->getMap().length();

  pos.y += 75;
  while (i < _end && it != this->_surfaceList.end())
    {
      pos.w = 30 * (*it)->getMap().length();
      if (pos.y + 75 < WIN_Y)
	{
	  SDL_RenderCopy(this->_renderer, (*it)->getSurface(), NULL, &pos);
	  pos.y += 75;
	  ++it;
	}
      i++;

    }
  SDL_RenderPresent(this->_renderer);
}

  /*
  **
  This function will display the numbers for the size of the generated map.
  **
  */

void	Menu::displayNumber()
{
  std::string s("Choose size for the map");
  std::string str("Generate");
  std::string re("Return");
  std::string tmp1("Width : "), tmp2("Height : ");

  std::string tmp3 = std::to_string(this->_randX);
  std::string tmp4 = std::to_string(this->_randY);

  std::string sX(tmp1 + tmp3);
  std::string sY(tmp2 + tmp4);

  SDL_Rect	pos;

  pos.x = 50;
  pos.y = 150;

  pos.h = 40;
  pos.w = 30 * s.length();

  SDL_RenderCopy(this->_renderer, this->_Background, NULL, NULL);
  SDL_RenderCopy(this->_renderer, this->_logo, NULL, &(this->_posLogo));

  this->_choosing = this->surfaceToTexture(TTF_RenderText_Blended(this->_police, s.c_str(), this->_black));

  this->_Xrand = this->surfaceToTexture(TTF_RenderText_Blended(this->_police, sX.c_str(),
							       (this->_posGen == 0) ?
							       this->_red : this->_black));

  this->_Yrand = this->surfaceToTexture(TTF_RenderText_Blended(this->_police, sY.c_str(),
							       (this->_posGen == 1) ?
							       this->_red : this->_black));

  this->_gen = this->surfaceToTexture(TTF_RenderText_Blended(this->_police, str.c_str(),
							     (this->_posGen == 2) ?
							     this->_red :
							     this->_black));

  SDL_Texture	*_ret;
  _ret = this->surfaceToTexture(TTF_RenderText_Blended(this->_police, re.c_str(),
						       (this->_posGen == 3) ?
						       this->_red :
						       this->_black));

  SDL_RenderCopy(this->_renderer, this->_choosing, NULL, &pos);

  pos.y += 80;
  pos.w = 30 * sX.length();

  SDL_RenderCopy(this->_renderer, this->_Xrand, NULL, &pos);

  pos.y += 100;
  pos.w = 30 * sY.length();

  SDL_RenderCopy(this->_renderer, this->_Yrand, NULL, &pos);
  pos.w = 30 * str.length();
  pos.y += 100;
  SDL_RenderCopy(this->_renderer, this->_gen, NULL, &pos);
  pos.w = 30 * re.length();
  pos.y += 100;
  SDL_RenderCopy(this->_renderer, _ret, NULL, &pos);
  SDL_RenderPresent(this->_renderer);
  SDL_DestroyTexture(_ret);
}

  /*
  **
  This function will use the savelist and print all the value on the screen.
  **
  */

void	Menu::printSaveMenu()
{
  std::list<MSetting *>::iterator it;
  SDL_Rect		pos;

  SDL_RenderClear(this->_renderer);
  this->setsurfaceSaveListColor(this->_save_pos);
  it = this->_surfaceListSave.begin();

  SDL_RenderCopy(this->_renderer, this->_Background, NULL, NULL);
  SDL_RenderCopy(this->_renderer, this->_logo, NULL, &(this->_posLogo));
  pos.x = 150;
  pos.y = 200;
  pos.w = 150;
  pos.h = 50;
  SDL_RenderCopy(this->_renderer, (*it)->getSurface(), NULL, &pos);
  pos.x = 30;
  pos.y += 75;
  ++it;
  while (it != this->_surfaceListSave.end())
    {
      pos.w = 30 * (*it)->getMap().length();
      SDL_RenderCopy(this->_renderer, (*it)->getSurface(), NULL, &pos);
      ++it;
      pos.y += 75;
    }
  SDL_RenderPresent(this->_renderer);
}

  /*
  **
  This functions serves to choose the good screen to print (Home, map, or save)
  **
  */

void	Menu::draw()
{
  std::map<int, void (Menu::*)()> mapPrint;
  void	(Menu::*ptr)();

  mapPrint[0] = &Menu::printHomeMenu;
  mapPrint[1] = &Menu::printMapMenu;
  mapPrint[2] = &Menu::printSaveMenu;
  mapPrint[3] = &Menu::displayNumber;
  ptr = mapPrint[this->_printable];
  if (ptr)
    (this->*ptr)();
}

  /*
  **
  This function serves to change the color of the map name
  **
  */

void	Menu::setColorMap(const int posToChange)
{
  int	i;

  i = 0;
  std::list<MSetting *>::iterator it;

  it = this->_surfaceList.begin();
  while (it != this->_surfaceList.end())
    {
      (*it)->setSurface(this->surfaceToTexture(TTF_RenderText_Blended(this->_font,
								      (*it)->getMap().c_str(),
								      (i == posToChange) ?
								      this->_red : this->_black)));
      if (i == posToChange)
	{
	  this->_mapGaming = ((*it)->getMap() == "Return") ? "Random" : (*it)->getMap();
	}
      i++;
      ++it;
    }
}

  /*
  **
  This function will incremente the x or y value for the map generation
  **
  */

void	Menu::setRandMore()
{
  if (this->_posGen == 1)
    this->_randY += 1;
  else
    this->_randX += 1;

}

  /*
  **
  This function is here to handle the right arrow of your keyboard.
  **
  */

void	Menu::changeTheme()
{
  if (this->_event.type == SDLK_RIGHT)
    {
      if (this->_it == this->_listTheme.end())
	_it = this->_listTheme.begin();
      else
	++_it;
    }
  else
    {
      if (this->_it == this->_listTheme.begin())
	{
	  _it = this->_listTheme.end();
	  --_it;
	}
      else
	--_it;
    }
  this->_themeGaming = (*_it);
}

void	Menu::eventRight()
{
  switch (this->_current_pos)
    {
    case 2:
      {
	if (this->_isInGen == 1)
	  this->setRandMore();
	break;
      }
    case 3:
      {
	this->setPlayer();
	break;
      }
    case 4:
      {
	this->setBots();
	break;
      }
    case 6:
      {
	this->changeTheme();
	break;
      }
    }
}

  /*
  **
  This function set a variable to tell which screen draw have to display.
  Here it's "1", and the draw function will print the Map Menu.
  **
  */

void	Menu::displayMap()
{
  this->_printable = 1;
  this->_map_pos = 1;
}

  /*
  **
  This function is here to handle the Return key of your keyboard.
  According to the position of your cursor it will call a different function.
  If you're on the first line of the menu, it will launch the game with the parameters you choose.
  If you're on the second line, it will set a variable and that will print the map Menu.
  If you're on the last line, it will set a variable and that will print the Load Menu.
  **
  */

void	Menu::displaySave()
{
  this->_printable = 2;
  this->_save_pos = 1;
}

void	Menu::checkReturn()
{
  switch (this->_current_pos)
    {
    case 1:
      {
	this->launchGame();
	break;
      }
    case 2:
      {
	this->_isPressed++;
	this->displayMap();
	if (this->_isInGen == 1)
	  {
	    if (this->_posGen == 3)
	      {
		this->_printable = 0;
		this->_isPressed = 0;
		this->_isInGen = 0;
		this->_mapGaming = "Random";
	      }
	    if (this->_posGen == 2)
	      {
		Map	*m = new Map(this->_randX, this->_randY);
		this->_mapGaming = m->getNameMap();
		this->_printable = 0;
		this->_isPressed = 0;
		this->_isInGen = 0;
		this->_randX = 10;
		this->_randY = 10;
		delete m;
	      }
	  }
	else
	  if (this->_isPressed == 2)
	    {
	      this->_save_pos = -1;
	      this->_printable = 0;
	      this->_isPressed = 0;
	    }
	break;
      }
    case 5:
      {
	this->_isPressed++;
	this->displaySave();
	if (this->_isPressed == 2)
	  {
	    this->_save_pos = -1;
	    this->_printable = 0;
	    this->_isPressed = 0;
	    if (this->_saveGaming != "Return" && this->_saveGaming != "None")
	      {
		this->getSaveInfo(this->_saveGaming);
		this->launchGame();
	      }
	  }
	break;
      }
    case 7:
      {
	this->_loop = 1;
      }
    }
}

  /*
  **
  This function will get all the informations we need to load
  **
  */

void	Menu::getSaveInfo(const std::string & saveName)
{
  MParsing	*infos = new MParsing(saveName);

  this->_save_b = infos->getNbBots();
  this->_save_p = infos->getNbPlayers();
  this->_mapGaming = infos->getMapName();

  delete infos;
}

  /*
  **
  This function will set a random map
  **
  */

void	Menu::setRandomMap()
{
  int index = 0;
  int tmp = (random() % (this->_mapList.size() - 1) + 1);

  std::list<std::string>::iterator it = this->_mapList.begin();
  while (index < tmp)
    {
      ++it;
      index++;
    }
  if ((*it) == "Generate")
    this->setRandomMap();
  else
    this->_mapGaming = (*it);
}

  /*
  **
  This function will fill two lists that the game engine will use to set all the parameters you choose to enjoy your game ;).
  **
  */

void	Menu::launchGame()
{
  if (this->_mapGaming == "Random")
    this->setRandomMap();
  else if (this->_mapGaming == "Generate")
    {
      this->_isInGen = 1;
      this->_printable = 3;
      this->_current_pos = 2;
    }
  else
    {
      this->_mapAndSave.push_back(this->_mapGaming);
      this->_mapAndSave.push_back(this->_themeGaming);
      if (this->_saveGaming != "None")
	this->_mapAndSave.push_back(this->_saveGaming);
      this->_botsAndPlayers.push_back(this->_save_p);
      this->_botsAndPlayers.push_back(this->_save_b);
      this->_loop = 1;
    }
}

void	Menu::setRandLess()
{
  if (this->_posGen == 1)
    {
      if (this->_randY > 10)
	this->_randY -= 1;
    }
  else
    {
      if (this->_randX > 10)
	this->_randX -= 1;
    }
}

  /*
  **
  This function serves to handle the left arrow of your keyboard.
  **
  */

void	Menu::eventLeft()
{
  switch (this->_current_pos)
    {
    case 2:
      {
	if (this->_isInGen == 1)
	  this->setRandLess();
	break;
      }
    case 3:
      {
	this->setPlayer();
	break;
      }
    case 4:
      {
	this->setBots();
	break;
      }
    case 6:
      {
	this->changeTheme();
	break;
      }
    }
}

  /*
  **
  This function serves to add or sub one to the number of AI you want.
  If you choose 0, there must be two players.
  **
  */

void	Menu::setBots()
{
  if (this->_current_pos == 4
      && this->_event.key.keysym.sym == SDLK_RIGHT)
    this->_save_b = this->_save_b + 1;
  else if (this->_current_pos == 4 && this->_save_b > 0
	   && this->_event.key.keysym.sym == SDLK_LEFT)
    this->_save_b = this->_save_b - 1;

  if (this->_save_b == 0)
    this->_save_p = 2;
}

  /*
  **
  This function serves to add or sub one to the number of player you want.
  The max number is two, so if you try to add one and the number is already two, it will sub one.
  If you try to sub one and you're already on one, it will add one to the numer.
  **
  */

void	Menu::setPlayer()
{
  this->_save_p = (this->_save_p == 1 && this->_current_pos == 3) ? this->_save_p + 1 : this->_save_p - 1;
  if (this->_save_p <= 0)
    this->_save_p = 1;
  if (this->_save_b == 0)
    this->_save_p = 2;
}

  /*
  **
  This function is called when you pressed the up arrow of your keyboard
  to sub one to the position cursor, if you're on the first line, it will go to the end.
  **
  */

void	Menu::upCursor()
{
  if (this->_isInGen == 1)
    {
      if (this->_posGen > 0)
	this->_posGen--;
      else
	this->_posGen = 3;
    }
  else
    {
      if (this->_printable == 1)
	{
	  this->_map_pos = (this->_map_pos > 1) ?
	    this->_map_pos - 1 :
	    this->_surfaceList.size() - 1;
	}
      else if (this->_printable == 2)
	{
	  this->_save_pos = (this->_save_pos > 1) ?
	    this->_save_pos - 1 :
	    this->_surfaceListSave.size() - 1;
	}
      else
	this->_current_pos = (this->_current_pos > 1) ? this->_current_pos - 1 : 7;
    }
}

  /*
  **
  This function is called when you pressed the down arrow of your keyboard
  to add one to the position cursor, if you're on the last line, it will go to the beginning.
  **
  */

void	Menu::downCursor()
{
  if (this->_isInGen == 1)
    {
      if (this->_posGen < 3)
	this->_posGen++;
      else
	this->_posGen = 0;
    }
  else
    {
      if (this->_printable == 1)
	{
	  this->_map_pos = (this->_map_pos == static_cast<int>(this->_surfaceList.size() - 1)) ?
	    1 : this->_map_pos + 1;
	}
      else if (this->_printable == 2)
	{
	  this->_save_pos = (this->_save_pos == (int)this->_surfaceListSave.size() - 1) ?
	    1 : this->_save_pos + 1;
	}
      else
	this->_current_pos = (this->_current_pos < 7) ? this->_current_pos + 1 : 1;
    }
}

  /*
  **
  This function serves to handle all the event I want.
  I use a map which contains a keycode and a function pointer.
  **
  */

void	Menu::waitEvent()
{
  std::map<int, void (Menu::*)()> mapEvent;
  void	(Menu::*ptr)();

  mapEvent[SDLK_UP] = &Menu::upCursor;
  mapEvent[SDLK_RIGHT] = &Menu::eventRight;
  mapEvent[SDLK_LEFT] = &Menu::eventLeft;
  mapEvent[SDLK_DOWN] = &Menu::downCursor;
  mapEvent[SDLK_RETURN] = &Menu::checkReturn;
  while (!this->_loop)
    {
      SDL_WaitEvent(&this->_event);
      if (this->_event.type == SDL_QUIT)
	this->_loop = 1;
      else if (this->_event.type == SDL_KEYDOWN)
	{
	  if (this->_event.key.keysym.sym == SDLK_ESCAPE)
	    this->_loop = 1;
	  else
	    {
	      ptr = mapEvent[this->_event.key.keysym.sym];
	      if (ptr)
		(this->*ptr)();
	    }
	}
      this->draw();
    }
}

  /*
  **
  The Menu Class Destructor will free all the SDL_Surface, and exit the menu properly.
  **
  */

Menu::~Menu()
{
  SDL_DestroyTexture(this->_logo);
  SDL_DestroyTexture(this->_Background);
  if (this->_play != NULL)
    SDL_DestroyTexture(this->_play);
  if (this->_map != NULL)
    SDL_DestroyTexture(this->_map);
  if (this->_players != NULL)
    SDL_DestroyTexture(this->_players);
  if (this->_save != NULL)
    SDL_DestroyTexture(this->_save);
  if (this->_nbBots != NULL)
    SDL_DestroyTexture(this->_nbBots);
  if (this->_quit != NULL)
    SDL_DestroyTexture(this->_quit);
  if (this->_Xrand != NULL)
    SDL_DestroyTexture(this->_Xrand);
  if (this->_Yrand != NULL)
    SDL_DestroyTexture(this->_Yrand);
  if (this->_choosing != NULL)
    SDL_DestroyTexture(this->_choosing);
  if (this->_gen != NULL)
    SDL_DestroyTexture(this->_gen);

  SDL_DestroyRenderer(this->_renderer);
  SDL_DestroyWindow(this->_screen);

  TTF_CloseFont(this->_police);
  TTF_CloseFont(this->_font);
  TTF_Quit();

  SDL_Quit();
}

void	Menu::fillSaveSurface(std::list<std::string> & saveList)
{
  std::list<std::string>::iterator	mapIt;

  mapIt = saveList.begin();
  this->_surfaceListSave.push_front(new MSetting(std::string("Load"), this->surfaceToTexture(TTF_RenderText_Blended(this->_police, "Load", this->_black))));
  while (mapIt != saveList.end())
    {
      this->_surfaceListSave.push_back(new MSetting(std::string(mapIt->c_str()),
						    this->surfaceToTexture(TTF_RenderText_Blended(this->_font, mapIt->c_str(), this->_black))));
      ++mapIt;
    }
  this->_surfaceListSave.push_back(new MSetting(std::string("Return"), this->surfaceToTexture(TTF_RenderText_Blended(this->_police, "Return", this->_black))));
}

void	Menu::setsurfaceSaveListColor(const int posToChange)
{
  int	i;

  i = 0;
  std::list<MSetting *>::iterator it;

  it = this->_surfaceListSave.begin();
  while (it != this->_surfaceListSave.end())
    {
      (*it)->setSurface(this->surfaceToTexture(TTF_RenderText_Blended(this->_font,
								      (*it)->getMap().c_str(), (i == posToChange) ? this->_red : this->_black)));
      if (i == posToChange)
	this->_saveGaming = ((*it)->getMap() == "Return") ? "None" : (*it)->getMap();
      i++;
      ++it;
    }
}
