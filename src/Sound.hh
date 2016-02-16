//
// Sound.hh for Sound in /home/bourre_l/rendu/cpp_bomberman
//
// Made by bourrel léo
// Login   <bourre_l@epitech.net>
//
// Started on  Sat Jun 13 11:16:47 2015 bourrel léo
// Last update Sat Jun 13 15:29:23 2015 bourrel léo
//

#ifndef	SOUND_HH
#define	SOUND_HH

#include <iostream>
#include <string>
#include <fmod.h>
#include <map>
#include "Exception.hpp"

extern std::map<std::string, FMOD_SOUND*>	GSound;

class	Sound
{
public:
  Sound();
 ~Sound();

  static void	play(FMOD_SOUND *music);
  static void	stop(FMOD_SOUND *music);

private:
  FMOD_SOUND	*menu;
  FMOD_SOUND	*game;
  FMOD_SOUND	*bomb;


  static FMOD_SYSTEM	*system;
  FMOD_CHANNEL	*channel;
  FMOD_RESULT	resultat;
};

extern  Sound   *son;

#endif
