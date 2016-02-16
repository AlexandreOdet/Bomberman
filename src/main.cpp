
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
#include <vector>
#include <iostream>
#include <fmod.h>

#include "Exception.hpp"
#include "MyGame.hh"
#include "Menu.hh"
#include "Sound.hh"

int	main()
{
  try
    {
      new Sound();

      FMOD_SOUND	*tmp;
      tmp = GSound["menu"];
      Sound::play(tmp);

      Menu	*M = new Menu();

      if (M->getMapSave().size() < 1 || M->getBotsPlayer().size() < 1)
	{
	  delete M;
	  return EXIT_FAILURE;
	}
      else
	{
	  MyGame	*engine = new MyGame(M->getBotsPlayer(), M->getMapSave());

	  delete M;
	  Sound::stop(tmp);
	  if (engine->initialize() == false)
	    return (EXIT_FAILURE);
	  while (engine->update() == true)
	    engine->draw();
	  delete engine;
	  return EXIT_SUCCESS;
	}
    }
  catch (MenuError const &e)
    {
      std::cerr << "Menu Error : " << e.what() << std::endl;
    }
  catch (ParseError const &e)
    {
      int	tmp = e.where();

      std::cerr << "Parsing error : " << e.what();
      if (tmp >= 0)
	std::cerr <<  " on line " << e.where();
      std::cerr << std::endl;
    }
  catch (GameError const &e)
    {
      std::cerr << "Game Error : " << e.what() << std::endl;
    }
  catch (ResError const &e)
    {
      std::cerr << "Error while loading ressource : " << e.what() << std::endl;
    }
  return EXIT_SUCCESS;
}
