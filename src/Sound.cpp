//
// Sound.cpp for Sound in /home/bourre_l/rendu/cpp_bomberman
//
// Made by bourrel léo
// Login   <bourre_l@epitech.net>
//
// Started on  Sat Jun 13 11:16:47 2015 bourrel léo
// Last update Sat Jun 13 15:31:47 2015 bourrel léo
//

#include "Sound.hh"

std::map<std::string, FMOD_SOUND*>	GSound;
FMOD_SYSTEM				*Sound::system;

Sound::Sound()
{
  FMOD_System_Create(&system);
  FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);

  resultat = FMOD_System_CreateSound(system, "ressource/sound/inmenu.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &menu);
  if (resultat != FMOD_OK)
    throw ResError("ressource/sound/inmenu.mp3");

  resultat = FMOD_System_CreateSound(system, "ressource/sound/ingame.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &game);
  if (resultat != FMOD_OK)
    throw ResError("ressource/sound/ingame.mp3");

  resultat = FMOD_System_CreateSound(system, "ressource/sound/bomb.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &bomb);
  if (resultat != FMOD_OK)
    throw ResError("ressource/sound/bomb.mp3");

  GSound["menu"] = menu;
  GSound["game"] = game;
  GSound["bomb"] = bomb;

  FMOD_System_GetChannel(system, 9, &channel);
}

Sound::~Sound()
{
  FMOD_System_Close(system);
  FMOD_System_Release(system);
}

void	Sound::play(FMOD_SOUND *music)
{
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, music, 0, NULL);
}

void	Sound::stop(FMOD_SOUND *music)
{
  FMOD_Sound_Release(music);
}
