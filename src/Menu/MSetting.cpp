#include "MSetting.hh"

MSetting::MSetting(const std::string & value, SDL_Texture *ptr)
{
  this->_val = value;
  this->_p = ptr;
}

MSetting::~MSetting()
{
}


SDL_Texture	*MSetting::getSurface() const
{
  return this->_p;
}

void		MSetting::setSurface(SDL_Texture *s)
{
  this->_p = s;
}

std::string	MSetting::getMap() const
{
  return this->_val;
}

void		MSetting::setMap(std::string const & s)
{
  this->_val = s;
}
